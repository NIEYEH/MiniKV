#pragma once

#include "minikv/command/Command.h"


class DelCommand : public Command
{

private:

    std::string key_;


public:

    DelCommand(
        std::string key
    );


    std::string execute(
        KVStore& store
    ) override;

};