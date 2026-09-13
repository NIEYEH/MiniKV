#pragma once

#include "minikv/command/Command.h"


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

    // 这里覆盖父类函数
    std::string execute(
        KVStore& store
    ) override;


};