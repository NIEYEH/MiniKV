#include <iostream>
#include "KVStore.h"

int main()
{
    KVStore store(2);

    std::cout
        << store.set("name","Alice")
        << std::endl;


    std::cout
        << store.set("age","24")
        << std::endl;


    std::cout
        << store.set("city","Shanghai")
        << std::endl;


    std::cout
        << store.size()
        << std::endl;


    return 0;
}