#pragma once

class Socket
{
private:
    int fd_ = -1;

public:
    Socket() = default;

    // explicit避免发生隐式类型转换
    // 比如如果写Socket(int fd);那么C++可能会允许Socket s = 5;编译器会偷偷转换成Socket s(5);
    explicit Socket(int fd) noexcept;

    ~Socket();

    Socket(const Socket&) = delete;

    Socket& operator=(const Socket&) = delete;

    // noexcept表示这个函数承诺不会抛出异常
    Socket(Socket&& other) noexcept;

    Socket& operator=(Socket&& other) noexcept;

    int fd() const noexcept;

    bool valid() const noexcept;

    int release() noexcept;

    void reset(int new_fd = -1) noexcept;
};
/*
一个Socket对象可以理解成：
Socket对象
│
├── fd_          保存 socket fd
│
├── fd()         获取 fd
├── valid()      fd 是否有效
├── release()    放弃 fd 所有权
├── reset()      替换 fd
└── ~Socket()    自动关闭 fd
*/