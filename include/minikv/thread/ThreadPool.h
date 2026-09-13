#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdexcept>
#include <cstddef>

#include "minikv/thread/TaskQueue.h"

class ThreadPool
{
private:
    std::vector<std::thread> workers_;
    TaskQueue queue_;

public:
    explicit ThreadPool(std::size_t thread_num);

    ~ThreadPool();

    // 线程池本身不允许复制
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    // Aegs：可变参数模板,表示参数数量不确定
    template <typename F, typename... Args>
    // F&& Args&&...是forwarding reference，配合std::forward实现完美转发，也就是尽可能保留调用者传入参数原本的左值/右值属性
    auto submit(
        F&& f,
        Args&&... args
    ) -> std::future<std::invoke_result_t<F, Args...>>
    {
        using ReturnType = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(
                std::forward<F>(f),
                std::forward<Args>(args)...
            )
        );
        std::future<ReturnType> future = task -> get_future();

        bool success = queue_.push(
            [task]()
            {
                (*task)();
            }
        );
        if (!success)
        {
            throw std::runtime_error(
                "ThreadPool has stopped"
            );
        }
        return future;
    }
};