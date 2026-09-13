#pragma once


#include <memory>

#include "minikv/command/Command.h"

#include "minikv/command/ParsedCommand.h"



class CommandFactory
{

public:

    // unique_ptr
    static std::unique_ptr<Command> create(
        const ParsedCommand& cmd
    );


};