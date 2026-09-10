#include <iostream>
#include "KVStore.h"

int main()
{
    KVStore store;

    store.set(
        "name",
        "Alice"
    );
    // v 0.1.0
    // std::cout << store.get("name") << std::endl;

    // store.del("name");

    // std::cout << store.exists("name") << std::endl;
    auto result = store.get("age");

    if(result.has_value())
    {
        std::cout << result.value() << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }

    return 0;
}