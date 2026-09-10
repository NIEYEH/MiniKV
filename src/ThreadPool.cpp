#include "ThreadPool.h"



ThreadPool::ThreadPool(
    size_t num
)
    :
    stop_(false)
{

    for(size_t i=0;i<num;i++)
    {

        workers_.emplace_back(

            [this]()
            {

                while(!stop_)
                {

                    auto task =
                        queue_.pop();

                    task();

                }

            }

        );

    }

}

void ThreadPool::submit(
    std::function<void()> task
)
{

    queue_.push(
        std::move(task)
    );

}

ThreadPool::~ThreadPool()
{

    stop_=true;


    for(auto& worker:workers_)
    {

        if(worker.joinable())
        {
            worker.join();
        }

    }

}