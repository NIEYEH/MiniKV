#pragma once

#include <string>
#include <cstddef>

#include "minikv/core/KVStore.h"
#include "minikv/thread/ThreadPool.h"
#include "minikv/command/CommandParser.h"

class Server
{
private:
    KVStore store_;

    ThreadPool pool_;

    CommandParser parser_;

    std::string executeLine(
        const std::string& input
    );

public:
    Server(
        std::size_t capacity,
        std::size_t worker_num
    );

    void run();
};