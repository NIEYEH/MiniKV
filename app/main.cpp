#include "minikv/server/Server.h"

int main()
{
    Server server(
        100,
        4
    );

    server.run();

    return 0;
}