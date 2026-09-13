#pragma once


#include <string>

#include "minikv/command/ParsedCommand.h"



class CommandParser
{

public:

    ParsedCommand parse(
        const std::string& input
    );


};