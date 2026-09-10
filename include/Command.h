#pragma once

#include <string>

class KVStore;


class Command
{

public:

    virtual ~Command() = default;


    virtual std::string execute(
        KVStore& store
    ) = 0;

};