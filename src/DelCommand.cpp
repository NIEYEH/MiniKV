#include "DelCommand.h"

#include "KVStore.h"



DelCommand::DelCommand(
    std::string key
)
    :
    key_(std::move(key))
{

}



std::string DelCommand::execute(
    KVStore& store
)
{

    bool result =
        store.del(key_);


    if(result)
    {
        return "OK";
    }


    return "NOT FOUND";

}