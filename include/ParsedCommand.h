#pragma once

#include <vector>
#include <string>

#include "CommandType.h"


struct ParsedCommand
{

    CommandType type;


    std::vector<std::string> args;

};