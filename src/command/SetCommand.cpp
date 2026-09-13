#include "minikv/command/SetCommand.h"

#include "minikv/core/KVStore.h"



SetCommand::SetCommand(
    std::string key,
    std::string value
)
    :
    key_(std::move(key)),
    value_(std::move(value))
{

}



std::string SetCommand::execute(
    KVStore& store
)
{

    bool result=
        store.set(key_,value_);


    if(result)
    {
        return "OK";
    }


    return "FAIL";

}