#include <iostream>
#include "KVStore.h"
#include "Buffer.h"
#include <utility>
#include "SetCommand.h"

int main()
{
    KVStore store(10);


    SetCommand cmd(
        "name",
        "Alice"
    );


    std::cout
        << cmd.execute(store)
        << std::endl;


    auto value=store.get("name");


    if(value)
    {
        std::cout
            << *value
            << std::endl;
    }
}
