#pragma once

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>


class TaskQueue
{

private:
    // 这里的队列去容纳多种函数统一包装，比如void func()，lambda表达式，std::bind绑定的函数等
    std::queue<std::function<void()>> tasks_;


    std::mutex mutex_;


    std::condition_variable cond_;


public:

    void push(
        std::function<void()> task
    );


    std::function<void()> pop();

};