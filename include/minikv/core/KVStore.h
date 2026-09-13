#pragma once

#include <unordered_map>
#include <string>
#include <optional>
#include <shared_mutex>
#include <cstddef>

class KVStore 
{

private:
    // 对象应该自己管理自己的数据
    std::unordered_map<std::string, std::string> data_;
    size_t capacity_;

    // const成员函数也需要加锁，所以必须mutable
    mutable std::shared_mutex mutex_;

public:
    explicit KVStore(std::size_t capacity);
    // 这里用&是因为如果不用的话调用set会发生字符串复制，性能更好
    // const表示这个函数不能修改
    bool set(
        const std::string& key,
        const std::string& value
    );

    std::optional<std::string> get(
        const std::string& key
    ) const;

    bool del(
        const std::string& key
    );

    bool exists(
        const std::string& key
    ) const;

    // 后面加个const相当于告诉编译器这个函数不能修改对象
    size_t size() const;
};