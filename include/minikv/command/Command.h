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
    // 这里virtual表示子类可以重写
    // =0表示Command只是接口，不能被实例化，必须由子类实现execute方法

};