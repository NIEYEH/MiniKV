#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "minikv/core/KVStore.h"
#include "minikv/thread/ThreadPool.h"
#include "minikv/command/CommandParser.h"
#include "minikv/network/Socket.h"

class TcpServer
{
private:
    std::uint16_t port_;

    KVStore store_;

    ThreadPool pool_;

    CommandParser parser_;

    Socket listen_socket_;

    std::string executeLine(
        const std::string& line
    );

    void handleClient(
        int client_fd
    );

public:
    TcpServer(
        std::uint16_t port,
        std::size_t capacity,
        std::size_t worker_num
    );
    void run();
};