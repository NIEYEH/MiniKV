#pragma once

#include <cstdint>
#include <string>

#include "minikv/network/Socket.h"

class TcpClient
{
private:
    Socket socket_;

    std::string recv_buffer_;

    bool sendLine(
        const std::string& line
    );

    bool receiveLine(
        std::string& line
    );

public:
    void connectTo(
        const std::string& ip,
        std::uint16_t port
    );

    void runInteractive();
};