#pragma once

#include <vector>
#include <string>

#include "minikv/command/CommandType.h"


struct ParsedCommand
{

    CommandType type;


    std::vector<std::string> args;

};