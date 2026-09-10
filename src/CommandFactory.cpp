#include "CommandFactory.h"


#include "SetCommand.h"
#include "GetCommand.h"
#include "DelCommand.h"



std::unique_ptr<Command>
CommandFactory::create(
    const ParsedCommand& cmd
)
{

    switch(cmd.type)
    {

    case CommandType::SET:

        return std::make_unique<SetCommand>(
            cmd.args[0],
            cmd.args[1]
        );


    case CommandType::GET:

        return std::make_unique<GetCommand>(
            cmd.args[0]
        );


    case CommandType::DEL:

        return std::make_unique<DelCommand>(
            cmd.args[0]
        );


    default:

        return nullptr;

    }

}