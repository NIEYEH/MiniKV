#include "GetCommand.h"

#include "KVStore.h"



GetCommand::GetCommand(
    std::string key
)
    :
    key_(std::move(key))
{

}



std::string GetCommand::execute(
    KVStore& store
)
{

    auto value =
        store.get(key_);


    if(value)
    {
        return *value;
    }


    return "(nil)";

}