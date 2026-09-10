#include "KVStore.h"

// ::强调这是KVStore的set函数
bool KVStore::set(
    const std::string& key,
    const std::string& value
)
{
    auto it = data_.find(key);

    if (it != data_.end())
    {
        it->second = value;
        return true;
    }
    if (data_.size() >= capacity_)
    {
        return false;
    }
    data_[key] = value;
    return true;
}
// v0.1.0
// std::string KVStore::get(
//     const std::string& key
// )
// {
//     auto it = data_.find(key);
//     if (it != data_.end())
//     {
//         return it->second;
//     }
//     return "";
// }
std::optional<std::string>
KVStore::get(
    const std::string& key
) const
{
    auto it = data_.find(key);
    if (it != data_.end())
    {
        return it->second;
    }
    return std::nullopt;
}

bool KVStore::del(
    const std::string& key
)
{
    return data_.erase(key) > 0;
}

bool KVStore::exists(
    const std::string& key
) const
{
    return data_.find(key) != data_.end();
}

size_t KVStore::size() const
{
    return data_.size();
}
// 成员初始化列表,因为const成员无法被赋值,只能在初始化列表中初始化
// 引用成员也必须初始化列表
// 没有默认构造函数的对象成员也必须在初始化列表中初始化
// C++永远按照成员变量声明顺序初始化
KVStore::KVStore(size_t capacity): capacity_(capacity)
{
    
}