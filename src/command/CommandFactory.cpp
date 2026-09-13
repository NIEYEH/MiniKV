#include "minikv/command/CommandFactory.h"

#include "minikv/command/SetCommand.h"
#include "minikv/command/GetCommand.h"
#include "minikv/command/DelCommand.h"

std::unique_ptr<Command>
CommandFactory::create(
    const ParsedCommand& cmd
)
{
    switch (cmd.type)
    {
        case CommandType::SET:
        {
            if (cmd.args.size() != 2)
            {
                return nullptr;
            }

            return std::make_unique<SetCommand>(
                cmd.args[0],
                cmd.args[1]
            );
        }

        case CommandType::GET:
        {
            if (cmd.args.size() != 1)
            {
                return nullptr;
            }

            return std::make_unique<GetCommand>(
                cmd.args[0]
            );
        }

        case CommandType::DEL:
        {
            if (cmd.args.size() != 1)
            {
                return nullptr;
            }

            return std::make_unique<DelCommand>(
                cmd.args[0]
            );
        }

        default:
            return nullptr;
    }
}