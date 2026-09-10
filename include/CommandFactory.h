#pragma once


#include <memory>

#include "Command.h"

#include "ParsedCommand.h"



class CommandFactory
{

public:


    static std::unique_ptr<Command> create(
        const ParsedCommand& cmd
    );


};