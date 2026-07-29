#pragma once
#include <iostream>
#include <syncstream> // Required for std::osyncstream
#include <thread>
#include <vector>
#include <sstream>

namespace SyncStreams_Basic
{
    /**
     * @brief Utility class to demonstrate C++20 synchronized streams.
     */
    class SyncStreamsBasic
    {
    public:
        SyncStreamsBasic() = default;

        /**
         * @brief Task run by multiple threads without stream synchronization.
         * Expected result: Output lines may be interleaved or corrupted.
         * @param threadId Identifier for the thread.
         * @param os Target stream (e.g., std::cout or std::stringstream).
         */
        void unsafePrintTask(int threadId, std::ostream& os) const
        {
            // Unsafe: Multiple threads writing directly to 'os' without explicit synchronization.
            os << "Thread " << threadId << ": Start printing message." << std::endl;
        }

        /**
         * @brief Task run by multiple threads using std::osyncstream for synchronization.
         * Expected result: Each thread's entire message is printed as an atomic block.
         * @param threadId Identifier for the thread.
         * @param os Target stream (e.g., std::cout or std::stringstream).
         */
        void safePrintTask(int threadId, std::ostream& os) const
        {
            // Safe: std::osyncstream creates a synchronized buffer tied to 'os'.
            // The buffer's content is guaranteed to be atomically flushed upon destruction (end of scope).
            std::osyncstream sync_os(os);

            sync_os << "Thread " << threadId << ": Safely printed message." << std::endl;
        }

        /**
         * @brief Runs multiple threads with synchronized streams to capture the output.
         * @param numThreads The number of threads to run.
         * @return The resulting synchronized output string.
         */
        std::string runSafeSynchronization(int numThreads)
        {
            std::stringstream ss;
            std::vector<std::thread> threads;

            for (int i = 0; i < numThreads; ++i)
            {
                // Pass ss by reference to capture the output.
                threads.emplace_back(&SyncStreamsBasic::safePrintTask, this, i + 1, std::ref(ss));
            }

            for (auto& t : threads)
            {
                t.join();
            }
            return ss.str();
        }
    };
}

