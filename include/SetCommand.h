#pragma once

#include "Command.h"


class SetCommand : public Command
{

private:

    std::string key_;

    std::string value_;


public:

    SetCommand(
        std::string key,
        std::string value
    );


    std::string execute(
        KVStore& store
    ) override;

};