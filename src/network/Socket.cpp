#include "minikv/network/Socket.h"

// 主要是为了使用close()，还有很多Linux的系统调用都在这里声明，比如read()，write()
#include <unistd.h>

Socket::Socket(int fd) noexcept
    : fd_(fd) // fd_: 成员变量，fd: 函数参数
{
}

Socket::~Socket()
{
    if (fd_ >= 0)
    {
        ::close(fd_);
    }
}

Socket::Socket(Socket&& other) noexcept
    : fd_(other.fd_)
{
    other.fd_ = -1;
}

Socket& Socket::operator=(Socket&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    if (fd_ >= 0)
    {
        ::close(fd_);
    }

    fd_ = other.fd_;
    other.fd_ = -1;
    return *this;
}

int Socket::fd() const noexcept
{
    return fd_;
}

bool Socket::valid() const noexcept
{
    return fd_ >= 0;
}

int Socket::release() noexcept
{
    int old_fd = fd_;
    fd_ = -1;
    return old_fd;
}

void Socket::reset(int new_fd) noexcept
{
    if (fd_ >= 0)
    {
        ::close(fd_);
    }
    fd_ = new_fd;
}