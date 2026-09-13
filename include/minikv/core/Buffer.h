#pragma once

#include <cstddef>


class Buffer
{

private:
    char* data_;
    size_t size_;

public:

    // 构造函数
    Buffer(size_t size);


    // 析构函数
    ~Buffer();


    // 拷贝构造
    Buffer(const Buffer& other);


    // 拷贝赋值
    Buffer& operator=(const Buffer& other);


    // 移动构造
    Buffer(Buffer&& other) noexcept;


    // 移动赋值
    Buffer& operator=(Buffer&& other) noexcept;

    char* data() const;

    size_t size() const;

};