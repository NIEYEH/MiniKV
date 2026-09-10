#include <iostream>
#include "KVStore.h"
#include "Buffer.h"
#include <utility>

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

    Buffer a(1024);
    std::cout 
        << "a address: "
        << &a
        << std::endl;

    std::cout
        << "a data: "
        << static_cast<void*>(a.data())
        << std::endl;
    // 这里是创建新对象b，所以a和b各自有独立的内存，互不影响
    Buffer b=a;
    std::cout
        << "\nAfter copy constructor\n";

    std::cout
        << "b address: "
        << &b
        << std::endl;

    std::cout
        << "b data: "
        << static_cast<void*>(b.data())
        << std::endl;

    Buffer c(2048);
    std::cout
        << "\nBefore copy assignment\n";


    std::cout
        << "c data: "
        << static_cast<void*>(c.data())
        << std::endl;
    // 这里是将对象b的内容赋值给c，所以c和b共享同一块内存，互相影响
    c=b;
    std::cout
        << "\nAfter copy assignment\n";

    std::cout
        << "c data: "
        << static_cast<void*>(c.data())
        << std::endl;

    Buffer d = std::move(a);
    std::cout
        << "\nAfter move constructor\n";

    std::cout
        << "d data: "
        << static_cast<void*>(d.data())
        << std::endl;

    std::cout
        << "a data: "
        << static_cast<void*>(a.data())
        << std::endl;
    return 0;
}
/*
a address: 0x7ffe54766b20
a data: 0x563c3925f7f0

After copy constructor
b address: 0x7ffe54766b30
b data: 0x563c3925fc00

Before copy assignment
c data: 0x563c39260010

After copy assignment
c data: 0x563c39260010

After move constructor
d data: 0x563c3925f7f0
a data: 0
*/