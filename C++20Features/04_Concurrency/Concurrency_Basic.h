#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <sstream>
#include <stop_token>
#include <latch>
#include <barrier>

namespace Concurrency_Basic
{
    /**
     * @brief Utility class to demonstrate C++20 concurrency features (jthread and stop_token).
     */
    class ConcurrencyBasic
    {
    private:
        // Atomic counter to track how many times the thread ran before stopping
        std::atomic<int> m_executionCount{ 0 };
    public:
        ConcurrencyBasic() = default;

        /**
         * @brief The thread function that checks for a stop request and increments a counter.
         * std::jthread automatically passes a std::stop_token as the first argument.
         * @param token The token used to check for stop requests.
         */
        void longRunningTask(std::stop_token token)
        {
            // The thread runs until a stop request is made.
            while (!token.stop_requested())
            {
                m_executionCount++;

                // Simulate work (e.g., waiting for I/O)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            // The thread exits gracefully after a stop request.
        }

        /**
         * @brief Starts the jthread and requests it to stop after a short duration.
         * @param durationMs Duration in milliseconds to wait before requesting stop.
         * @return The final execution count from the stopped thread.
         */
        int runAndStopThread(int durationMs)
        {
            m_executionCount = 0;   // Reset counter for the run

            // 1. std::jthread is used (RAII thread)
            // It automatically starts the thread and passes a stop_token to longRunningTask.
            std::jthread worker([this](std::stop_token token)
                {
                    this->longRunningTask(token);
                });

            // 2. Main thread waits for a short duration
            std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));

            // 3. Request the worker thread to stop
            // This sets the stop state on the stop_source linked to the jthread.
            worker.request_stop();

            // The worker will exit the 'while' loop and finish its execution.
            // When 'worker' goes out of scope, its destructor automatically calls join().
            return m_executionCount.load();
        }

        // ------------------------------------------------------------------------
        // std::latch
            
        /**
         * @brief A worker task that waits for a latch countdown before proceeding.
         * @param l The latch object, passed by reference.
         * @param id The ID of the worker.
         * @param result The shared atomic variable to sum up results.
         */
        void barrierTask(std::latch& l, int id, std::atomic<int>& result)
        {
            // Simulate preparation work
            std::this_thread::sleep_for(std::chrono::milliseconds(5 + id * 2));

            // 1. Thread signals it has arrived at the barrier point (decrements the latch count)
            l.count_down();

            // 2. Thread waits until the latch count reaches zero (all threads have arrived).
            // This call blocks the thread until the main thread signals completion.
            l.wait();

            // 3. All threads proceed together to the final stage
            result.fetch_add(id);
        }

        /**
         * @brief Demonstrates using std::latch to synchronize multiple worker threads.
         * @param numWorkers The number of threads to synchronize.
         * @return The sum of all worker IDs after synchronization.
         */
        int runLatchSynchronization(int numWorkers)
        {
            // 1. Initialize latch with the number of expected threads (workers + main thread)
            // Latch count = number of workers expected to signal arrival.
            std::latch start_barrier(numWorkers);
            std::atomic<int> finalResult{ 0 };
            std::vector<std::jthread> workers;

            // 2. Launch workers (using std::jthread for automatic join)
            for (auto i = 1; i <= numWorkers; ++i)
            {
                // Pass l by reference. jthread's constructor supports passing references.
                workers.emplace_back([this, &start_barrier, i, &finalResult]()
                    {
                        this->barrierTask(start_barrier, i, finalResult);
                    });
            }

            // 3. Main thread waits until all workers signal arrival (count_down)
            // This is the simplest use case: main waits for all workers to be ready.
            start_barrier.wait();

            // At this point, all workers have arrived at the barrier and are now waiting 
            // *inside* barrierTask on their own 'l.wait()' call.

            // 4. (Optional) Simulate main thread initiating the final action
            // In this specific implementation, all workers are waiting on the *same* latch.
            // Since the main thread has waited for the workers to arrive, 
            // the workers themselves can proceed once the latch count reaches zero 
            // (which happens inside the workers' count_down()). 
            // The wait() call inside barrierTask ensures they proceed together.

            // The workers will automatically join when the 'workers' vector is destroyed.

            // Wait a short time for the workers to complete the final addition
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            return finalResult.load();
        }

        // ------------------------------------------------------------------------
        // std::barrier

        /**
         * @brief A worker task that synchronizes using a barrier across multiple phases.
         * @param b The barrier object, passed by reference.
         * @param id The ID of the worker.
         * @param result The shared atomic variable to sum up results.
         */
        void barrierPhaseTask(std::barrier<>& b, int id, std::atomic<int>& result)
        {
            // --- PHASE 1: Initial Calculation ---

            // Simulate initial complex calculation
            int phase1_val = id * 10;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            // Wait for all threads to finish Phase 1. 
            // The call to arrive_and_wait() blocks until all threads arrive.
            // When all threads arrive, the barrier is reset for the next phase.
            b.arrive_and_wait();

            // --- PHASE 2: Final Aggregation ---

            // Simulate shared resource update based on Phase 1 results
            result.fetch_add(phase1_val);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            // Wait for all threads to finish Phase 2 before the function exits.
            b.arrive_and_wait();
        }

        /**
         * @brief Demonstrates using std::barrier for multi-phase synchronization.
         * @param numWorkers The number of threads to synchronize.
         * @return The final aggregated sum of all worker results.
         */
        int runBarrierSynchronization(int numWorkers)
        {
            // 1. Initialize barrier with the number of expected threads (workers only)
            // The number of expected threads is 2 * numWorkers (due to 2 phases)
            // But we initialize with numWorkers, as each thread calls arrive_and_wait() twice.
            std::barrier phase_barrier(numWorkers);
            std::atomic<int> finalResult{ 0 };
            std::vector<std::jthread> workers;

            // 2. Launch workers (using std::jthread for automatic join)
            for (auto i = 1; i <= numWorkers; ++i)
            {
                workers.emplace_back([this, &phase_barrier, i, &finalResult]()
                    {
                        // Pass b by reference.
                        this->barrierPhaseTask(phase_barrier, i, finalResult);
                    });
            }

            // The main thread waits for the workers to complete their task entirely.
            // Since jthread is used, we just let the workers vector go out of scope 
            // to ensure all threads finish and join correctly.

            // Wait a moment for the threads to complete both phases
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // The worker threads are joined here as 'workers' is about to be destroyed.
            return finalResult.load();
        }
    };
}

