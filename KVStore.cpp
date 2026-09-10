#include "KVStore.h"

// ::强调这是KVStore的set函数
void KVStore::set(
    const std::string& key,
    const std::string& value
)
{
    data_[key] = value;
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