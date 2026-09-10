#pragma once

#include <unordered_map>
#include <string>

class KVStore 
{

private:
    // 对象应该自己管理自己的数据
    std::unordered_map<std::string, std::string> data_;
    size_t capacity_;

public:
    KVStore(size_t capacity);
    // 这里用&是因为如果不用的话调用set会发生字符串复制，性能更好
    // const表示这个函数不能修改
    void set(
        const std::string& key,
        const std::string& value
    );
    // v0.1.0
    // std::string get(
    //     const std::string& key
    // );
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