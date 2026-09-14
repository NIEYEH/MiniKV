#include "minikv/network/TcpClient.h"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

bool TcpClient::sendLine(
    const std::string& line
)
{
    std::string data =
        line + "\n";

    std::size_t sent = 0;

    while (sent < data.size())
    {
        ssize_t n =
            ::send(
                socket_.fd(),
                data.data() + sent,
                data.size() - sent,
                MSG_NOSIGNAL
            );

        if (n < 0)
        {
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

        sent +=
            static_cast<std::size_t>(n);
    }

    return true;
}


bool TcpClient::receiveLine(
    std::string& line
)
{
    while (true)
    {
        std::size_t pos =
            recv_buffer_.find('\n');

        if (
            pos != std::string::npos
        )
        {
            line =
                recv_buffer_.substr(
                    0,
                    pos
                );

            recv_buffer_.erase(
                0,
                pos + 1
            );

            if (
                !line.empty() &&
                line.back() == '\r'
            )
            {
                line.pop_back();
            }

            return true;
        }


        char buffer[4096];

        ssize_t n =
            ::recv(
                socket_.fd(),
                buffer,
                sizeof(buffer),
                0
            );

        if (n == 0)
        {
            return false;
        }

        if (n < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }

            return false;
        }


        recv_buffer_.append(
            buffer,
            static_cast<std::size_t>(n)
        );
    }
}


void TcpClient::connectTo(
    const std::string& ip,
    std::uint16_t port
)
{
    Socket new_socket(
        ::socket(
            AF_INET,
            SOCK_STREAM,
            0
        )
    );

    if (!new_socket.valid())
    {
        throw std::runtime_error(
            std::string("socket failed: ")
            + std::strerror(errno)
        );
    }


    sockaddr_in address{};

    address.sin_family =
        AF_INET;

    address.sin_port =
        htons(port);


    int result =
        ::inet_pton(
            AF_INET,
            ip.c_str(),
            &address.sin_addr
        );


    if (result != 1)
    {
        throw std::runtime_error(
            "invalid IPv4 address"
        );
    }


    if (
        ::connect(
            new_socket.fd(),
            reinterpret_cast<sockaddr*>(
                &address
            ),
            sizeof(address)
        ) < 0
    )
    {
        throw std::runtime_error(
            std::string("connect failed: ")
            + std::strerror(errno)
        );
    }


    socket_ =
        std::move(new_socket);
}


void TcpClient::runInteractive()
{
    std::string input;

    while (true)
    {
        std::cout
            << "MiniKV> "
            << std::flush;


        if (
            !std::getline(
                std::cin,
                input
            )
        )
        {
            break;
        }


        if (input.empty())
        {
            continue;
        }


        if (!sendLine(input))
        {
            std::cout
                << "Server disconnected"
                << std::endl;

            break;
        }


        std::string response;


        if (!receiveLine(response))
        {
            std::cout
                << "Server disconnected"
                << std::endl;

            break;
        }


        std::cout
            << response
            << std::endl;


        if (
            input == "QUIT" ||
            input == "EXIT"
        )
        {
            break;
        }
    }
}