#include "minikv/thread/ThreadPool.h"

ThreadPool::ThreadPool(std::size_t thread_num)
{
    if (thread_num == 0)
    {
        thread_num = 1;
    }

    workers_.reserve(thread_num);

    for (
        std::size_t i = 0;
        i < thread_num;
        ++i
    )
    {
        workers_.emplace_back(
            [this]()
            {
                std::function<void()> task;

                while (queue_.pop(task))
                {
                    task();
                }
            }
        );
    }
}

ThreadPool::~ThreadPool()
{
    queue_.shutdown();

    for (auto& worker : workers_)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}