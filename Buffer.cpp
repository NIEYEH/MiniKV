#include "Buffer.h"
#include <cstring>

Buffer::Buffer(size_t size): size_(size)
{
    data_ = new char[size];
}

Buffer::~Buffer()
{
    delete[] data_;
}

// 拷贝构造
Buffer::Buffer(const Buffer& other): size_(other.size_)
{
    data_ = new char[size_];

    memcpy(data_, other.data_, size_);
}
// 拷贝复制
Buffer& Buffer::operator=(
    const Buffer& other
)
{
    if(this == &other)
    {
        return *this;
    }

    delete[] data_;
    size_ = other.size_;
    data_ = new char[size_];
    memcpy(data_, other.data_, size_);
    return *this;
}
// 移动语义，将原来的对象置为无效状态
Buffer::Buffer(Buffer&& other) noexcept
{
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
}

char* Buffer::data() const
{
    return data_;
}

size_t Buffer::size() const
{
    return size_;
}