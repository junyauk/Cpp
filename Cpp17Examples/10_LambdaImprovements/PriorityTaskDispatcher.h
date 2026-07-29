#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <vector>
#include <iostream>
#include <atomic>

namespace LambdaImprovements
{
	enum class TaskPriority
	{
		High = 0,
		Normal = 1,
		Low = 2
	};

    class PriorityTaskDispatcher
    {
    public:
        explicit PriorityTaskDispatcher(size_t threadCount = std::thread::hardware_concurrency())
            : m_stop(false)
        {
            for (size_t i = 0; i < threadCount; ++i)
            {
                m_workers.emplace_back([this] { this->workerLoop(); });
            }
        }

        ~PriorityTaskDispatcher()
        {
            {
                std::lock_guard lock(m_mutex);
                m_stop = true;
            }
            m_cv.notify_all();

            for (auto& worker : m_workers)
                worker.join();
        }

        template <typename F, typename... Args>
        auto enqueue(TaskPriority priority, F&& func, Args&&... args)
            -> std::future<std::invoke_result_t<F, Args...>>
        {
            using RetType = std::invoke_result_t<F, Args...>;

            auto task = std::make_shared<std::packaged_task<RetType()>>(
                std::bind(std::forward<F>(func), std::forward<Args>(args)...)
            );

            {
                std::lock_guard lock(m_mutex);
                m_tasks.emplace(priority, [task]() { (*task)(); });
            }

            m_cv.notify_one();
            return task->get_future();
        }

    private:
        void workerLoop()
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock lock(m_mutex);
                    m_cv.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

                    if (m_stop && m_tasks.empty())
                        return;

                    auto item = m_tasks.top();
                    m_tasks.pop();
                    task = std::move(item.func);
                }
                task();
            }
        }

        struct TaskItem
        {
            TaskPriority priority;
            std::function<void()> func;
            TaskItem(TaskPriority p, std::function<void()> f)
                : priority(p), func(f) {}

            bool operator<(const TaskItem& other) const
            {
                // priority‚ª¬‚³‚¢•ûiHighj‚ªæ‚ÉŽÀs‚³‚ê‚é‚æ‚¤‚É‹t‡
                return static_cast<int>(priority) > static_cast<int>(other.priority);
            }
        };

        std::priority_queue<TaskItem> m_tasks;
        std::vector<std::thread> m_workers;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::atomic<bool> m_stop;
    };
}

