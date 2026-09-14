#include "minikv/network/TcpClient.h"

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
        std::string ip =
            "127.0.0.1";

        std::uint16_t port =
            9000;


        if (argc >= 2)
        {
            ip = argv[1];
        }


        if (argc >= 3)
        {
            port =
                static_cast<std::uint16_t>(
                    std::stoi(argv[2])
                );
        }


        TcpClient client;


        client.connectTo(
            ip,
            port
        );


        client.runInteractive();
    }
    catch (
        const std::exception& e
    )
    {
        std::cerr
            << "Client error: "
            << e.what()
            << std::endl;

        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}