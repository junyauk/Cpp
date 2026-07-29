#pragma once
#include <atomic>
#include <thread>
#include <chrono>
#include <string>

namespace AtomicWait_Basic
{
    /**
     * @brief Utility class to demonstrate C++20 atomic wait/notify features.
     */
    class AtomicWaitBasic
    {
    private:
        // Shared atomic counter used for synchronization.
        std::atomic<int> m_sharedCounter{ 0 };
    public:
        AtomicWaitBasic() = default;

        /**
         * @brief Consumer thread function: waits for the counter to reach the expected value.
         * The thread blocks efficiently until the atomic variable changes.
         * @param expectedValue The value to wait for.
         */
        void consumerTask(int expectedValue)
        {
            // The wait() call efficiently blocks the thread until m_sharedCounter 
            // is NOT equal to 0 (its current value). 
            // If the value is already different from 0, it returns immediately (no wait).
            m_sharedCounter.wait(0);

            // After waking up, the counter must be the expected value (or higher).
            if (m_sharedCounter.load() >= expectedValue)
            {
                // Task succeeded
            }
            else
            {
                // Handle spurious wake-up (though less common with atomic::wait)
            }
        }

        /**
            * @brief Producer thread function: updates the counter and notifies the waiting thread.
            * @param setValue The value to set the counter to.
            */
        void producerTask(int setValue)
        {
            // Simulate some preparation work
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            // 1. Update the shared atomic variable.
            m_sharedCounter.store(setValue);

            // 2. Notify one waiting thread.
            // This wakes up the thread blocked on m_sharedCounter.wait().
            m_sharedCounter.notify_one();
        }

        /**
         * @brief Runs the producer and consumer threads to demonstrate synchronization.
         * @param expectedValue The value the consumer should wait for.
         * @return The final value of the shared counter.
         */
        int runWaitNotify(int expectedValue)
        {
            // Reset counter
            m_sharedCounter.store(0);

            // Start Consumer (waiter)
            std::thread consumer(&AtomicWaitBasic::consumerTask, this, expectedValue);

            // Start Producer (notifier)
            std::thread producer(&AtomicWaitBasic::producerTask, this, expectedValue);

            consumer.join();
            producer.join();
            return m_sharedCounter.load();
        }
    };
}

