#include "minikv/thread/TaskQueue.h"
#include <utility>

bool TaskQueue::push(
    std::function<void()> task
)
{
    {
        // 进入临界区，保证线程安全，自动加锁，离开自动解锁
        std::lock_guard<std::mutex> lock(mutex_);
        if (closed_)
        {
            return false;
        }
        tasks_.push(std::move(task));
    }
    cond_.notify_one();
    return true;
}

bool TaskQueue::pop(
    std::function<void()>& task
)
{
    std::unique_lock<std::mutex> lock(mutex_);

    cond_.wait(
        lock,
        [this]()
        {
            return !tasks_.empty();
        }
    );

    // 队列关闭，并且所有任务已经处理完
    if (tasks_.empty())
    {
        return false;
    }
    task = std::move(tasks_.front());

    tasks_.pop();

    return true;

}
void TaskQueue::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        closed_ = true;
    }

    cond_.notify_all();
}