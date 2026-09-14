#include "minikv/network/TcpServer.h"

#include <cstdlib>
#include <exception>
#include <iostream>

int main(
    int argc,
    char* argv[]
)
{
    try
    {
        std::uint16_t port = 9000;

        if (argc >= 2)
        {
            port =
                static_cast<std::uint16_t>(
                    std::stoi(argv[1])
                );
        }


        TcpServer server(
            port,
            10000,
            4
        );


        server.run();
    }
    catch (
        const std::exception& e
    )
    {
        std::cerr
            << "Server error: "
            << e.what()
            << std::endl;

        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}