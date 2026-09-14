#include "minikv/network/TcpServer.h"

#include "minikv/command/CommandFactory.h"

// 提供网络地址相关函数
#include <arpa/inet.h>
// 提供系统调用失败分析函数
#include <cerrno>
// 把错误码转换成人能看懂的字符串
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
// 提供socket编程最核心的一批函数
#include <sys/socket.h>
// close()
#include <unistd.h>

// 匿名命名空间 Anonymous Namespace，让这个空间里的函数只给当前这个.cpp使用，不希望其他.cpp文件访问
namespace
{

// 确保一整个字符串全部发送出去
bool sendAll(
    int fd,
    const std::string& data
)
{   
    // 记录当前已经成功发送多少字节
    std::size_t sent = 0;

    while (sent < data.size())
    {   
        // 哪个socket从什么位置发送多少字节的数据以及标志是什么
        // size_t 无符号整数，ssize_t 有符号整数
        ssize_t n = ::send(
            fd,
            data.data() + sent,
            data.size() - sent,
            MSG_NOSIGNAL // 连接状态标志，避免连接中断仍继续发送
        );

        if (n < 0)
        {   
            // EINTR表示系统调用被信号打断了，此时重新send()即可
            if (errno == EINTR)
            {
                continue;
            }

            return false;
        }

        if (n == 0)
        {
            return false;
        }
        // 更新发送进度
        sent += static_cast<std::size_t>(n);
    }

    return true;
}

} // namespace


TcpServer::TcpServer(
    std::uint16_t port,
    std::size_t capacity,
    std::size_t worker_num
)
    :
    port_(port),
    store_(capacity),
    pool_(worker_num)
{
}


std::string TcpServer::executeLine(
    const std::string& line
)
{
    auto parsed =
        parser_.parse(line);

    auto command =
        CommandFactory::create(parsed);

    if (!command)
    {
        return "ERR invalid command or arguments";
    }

    return command->execute(store_);
}


void TcpServer::handleClient(
    int client_fd
)
{   
    // 表示由client这个RAII对象负责client_fd
    Socket client(client_fd);
    // 接收缓冲区
    constexpr std::size_t BUFFER_SIZE = 4096;

    constexpr std::size_t MAX_PENDING = 64 * 1024;

    char buffer[BUFFER_SIZE];
    // TCP没有消息边界，即不同数据可能不按顺序到达，所以需要拼接
    std::string pending;

    while (true)
    {   
        // 从client socket读取最多4096个字节并放入buffer
        ssize_t n =
            ::recv(
                client.fd(),
                buffer,
                sizeof(buffer),
                0
            );

        if (n == 0)
        {
            // 对端正常关闭连接
            return;
        }

        if (n < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }

            return;
        }
        // 收到数据之后从开头取n字节
        pending.append(
            buffer,
            static_cast<std::size_t>(n)
        );
        // 防止pending无限增长，把服务器内存吃光
        if (pending.size() > MAX_PENDING)
        {
            sendAll(
                client.fd(),
                "ERR command too long\n"
            );

            return;
        }

        std::size_t pos;
        // pending里只要还有完整的一行，就继续处理
        while (
            (pos = pending.find('\n'))
            != std::string::npos
        )
        {
            std::string line =
                pending.substr(0, pos);

            pending.erase(
                0,
                pos + 1
            );
            // Linux常见换行\n，Windows/一些网络客户端常见\r\n。
            // 兼容\r\n
            if (
                !line.empty() &&
                line.back() == '\r'
            )
            {
                line.pop_back();
            }

            if (line.empty())
            {
                continue;
            }

            if (
                line == "QUIT" ||
                line == "EXIT"
            )
            {
                sendAll(
                    client.fd(),
                    "BYE\n"
                );

                return;
            }

            std::string response =
                executeLine(line);
            // 服务器可能返回OK，拼接成OK\n，让客户端判断一条服务器响应结束了。
            response.push_back('\n');

            if (
                !sendAll(
                    client.fd(),
                    response
                )
            )
            {
                return;
            }
        }
    }
}


void TcpServer::run()
{   
    // 可以理解为创建一个IPv4 TCP socket。
    int fd =
        ::socket(
            AF_INET, // ipv4
            SOCK_STREAM, // 字节流socket，也就是TCP
            0
        );

    if (fd < 0)
    {
        throw std::runtime_error(
            std::string("socket failed: ")
            + std::strerror(errno)
        );
    }

    listen_socket_.reset(fd);

    int reuse = 1;

    if (
        ::setsockopt(
            listen_socket_.fd(),
            SOL_SOCKET,
            SO_REUSEADDR, // SO_REUSEADDR 让服务器重启以后更容易重新绑定原来的端口
            &reuse,
            sizeof(reuse)
        ) < 0
    )
    {
        throw std::runtime_error(
            std::string("setsockopt failed: ")
            + std::strerror(errno)
        );
    }

    // IPv4地址结构体，包括地址协议(sin_family) + IP地址(sin_addr) + 端口(sin_port)
    sockaddr_in address{};

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = htonl(INADDR_ANY);

    address.sin_port = htons(port_);

    if (
        ::bind(
            listen_socket_.fd(),
            reinterpret_cast<sockaddr*>(
                &address
            ),
            sizeof(address)
        ) < 0
    )
    {
        throw std::runtime_error(
            std::string("bind failed: ")
            + std::strerror(errno)
        );
    }


    if (
        ::listen(
            listen_socket_.fd(),
            SOMAXCONN
        ) < 0
    )
    {
        throw std::runtime_error(
            std::string("listen failed: ")
            + std::strerror(errno)
        );
    }


    std::cout
        << "MiniKV V0.4 TCP Server started\n"
        << "Listening on 0.0.0.0:"
        << port_
        << std::endl;


    while (true)
    {
        sockaddr_in client_address{};

        socklen_t client_length =
            sizeof(client_address);


        int client_fd =
            ::accept(
                listen_socket_.fd(),
                reinterpret_cast<sockaddr*>(
                    &client_address
                ),
                &client_length
            );


        if (client_fd < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }

            std::cerr
                << "accept failed: "
                << std::strerror(errno)
                << std::endl;

            continue;
        }


        char ip[
            INET_ADDRSTRLEN
        ]{};

        ::inet_ntop(
            AF_INET,
            &client_address.sin_addr,
            ip,
            sizeof(ip)
        );


        std::cout
            << "Client connected: "
            << ip
            << ":"
            << ntohs(
                client_address.sin_port
            )
            << std::endl;


        try
        {
            pool_.submit(
                [
                    this,
                    client_fd
                ]()
                {
                    handleClient(
                        client_fd
                    );
                }
            );
        }
        catch (...)
        {
            ::close(client_fd);

            throw;
        }
    }
}