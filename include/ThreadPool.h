#pragma once

#include <vector>
#include <thread>

#include "TaskQueue.h"


class ThreadPool
{

private:

    std::vector<std::thread> workers_;


    TaskQueue queue_;


    bool stop_;


public:

    ThreadPool(
        size_t num
    );


    ~ThreadPool();


    void submit(
        std::function<void()> task
    );


};