#pragma once

#include "minikv/command/Command.h"


class GetCommand : public Command
{

private:

    std::string key_;


public:

    GetCommand(
        std::string key
    );


    std::string execute(
        KVStore& store
    ) override;

};