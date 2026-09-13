#include "minikv/server/Server.h"

#include <iostream>
#include <utility>

#include "minikv/command/CommandFactory.h"

Server::Server(
    std::size_t capacity,
    std::size_t worker_num
)
    :
    store_(capacity),
    pool_(worker_num)
{
}

std::string Server::executeLine(
    const std::string& input
)
{
    ParsedCommand parsed =
        parser_.parse(input);

    auto command =
        CommandFactory::create(parsed);

    if (!command)
    {
        return "ERR invalid command or arguments";
    }

    auto future =
        pool_.submit(
            // lambda捕获，this让lambda可以访问store_
            [
                this,
                // comman...把unique_ptr<command>的所有权移动进lambda
                command = std::move(command)
            // 默认lambda的operator()是const，加mutable之后允许修改捕获进去的值
            ]() mutable
            {
                return command->execute(store_);
            }
        );

    return future.get();
}

void Server::run()
{
    std::cout
        << "MiniKV V0.3 started"
        << std::endl;

    std::cout
        << "Type QUIT to exit"
        << std::endl;


    std::string input;

    while (true)
    {
        std::cout
            << "MiniKV> "
            << std::flush;

        if (!std::getline(std::cin, input))
        {
            break;
        }

        if (input.empty())
        {
            continue;
        }

        if (
            input == "QUIT" ||
            input == "EXIT"
        )
        {
            break;
        }

        std::string response =
            executeLine(input);

        std::cout
            << response
            << std::endl;
    }

    std::cout
        << "MiniKV stopped"
        << std::endl;
}