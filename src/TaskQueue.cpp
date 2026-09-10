#include "TaskQueue.h"


void TaskQueue::push(
    std::function<void()> task
)
{

    {
        // 进入临界区，保证线程安全，自动加锁，离开自动解锁
        std::lock_guard<std::mutex> lock(mutex_);


        tasks_.push(
            std::move(task)
        );

    }


    cond_.notify_one();

}

std::function<void()> TaskQueue::pop()
{

    std::unique_lock<std::mutex> lock(mutex_);


    cond_.wait(
        lock,
        [this]()
        {
            return !tasks_.empty();
        }
    );


    auto task =
        std::move(tasks_.front());


    tasks_.pop();


    return task;

}