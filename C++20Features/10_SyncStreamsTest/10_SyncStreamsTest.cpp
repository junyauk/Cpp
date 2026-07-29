#include "pch.h"
#include "../10_SyncStreams/SyncStreams_Basic.h"
#include <thread>
#include <sstream>
#include <algorithm>

using SyncStreams_Basic::SyncStreamsBasic;

namespace SyncStreams_Basic_Test
{
    class SyncStreamsTest : public ::testing::Test
    {
    protected:
        SyncStreamsBasic m_syncBasic;
    };

    // Helper function to count occurrences of a substring
    size_t countSubstring(const std::string& str, const std::string& sub)
    {
        size_t count = 0;
        size_t pos = str.find(sub, 0);
        while (pos != std::string::npos)
        {
            count++;
            pos = str.find(sub, pos + 1);
        }
        return count;
    }

    // Test case 1: Verify that all synchronized messages are present (implies successful atomic flushing)
    TEST_F(SyncStreamsTest, Synchronization_Integrity)
    {
        constexpr int NUM_THREADS = 5;
        std::string output = m_syncBasic.runSafeSynchronization(NUM_THREADS);

        // Check if the total number of "Safely printed message" matches the number of threads.
        // This implicitly confirms that no output was lost or corrupted during the atomic flush.
        EXPECT_EQ(NUM_THREADS, countSubstring(output, "Safely printed message."));
    }

    // Test case 2: Verify the output format (less prone to corruption)
    // NOTE: It is hard to test *lack* of interleaving, so we focus on integrity.
    TEST_F(SyncStreamsTest, Synchronization_Format)
    {
        std::stringstream ss_safe;
        std::thread t1(&SyncStreamsBasic::safePrintTask, m_syncBasic, 1, std::ref(ss_safe));
        std::thread t2(&SyncStreamsBasic::safePrintTask, m_syncBasic, 2, std::ref(ss_safe));

        t1.join();
        t2.join();

        std::string output = ss_safe.str();

        // Output must contain both messages fully (e.g., "...message.\nThread 2:...")
        EXPECT_NE(std::string::npos, output.find("Thread 1: Safely printed message."));
        EXPECT_NE(std::string::npos, output.find("Thread 2: Safely printed message."));
    }

    // Conceptual Test: Interleaving Demonstration (Optional, shows the problem SyncStreams solves)
    TEST_F(SyncStreamsTest, Conceptual_UnsafeInterleaving)
    {
        std::stringstream ss_unsafe;

        // Run many threads without synchronization
        std::vector<std::thread> threads;
        for (int i = 0; i < 2; ++i)
        {
            threads.emplace_back(&SyncStreamsBasic::unsafePrintTask, m_syncBasic, i + 10, std::ref(ss_unsafe));
        }
        for (auto& t : threads)
        {
            t.join();
        }

        std::string output = ss_unsafe.str();

        // We cannot reliably assert corruption, but we assert the need for SyncStreams.
        // If the output were to std::cout, interleaving would be visible to the user.
        SUCCEED() << "Unsafe output (demonstrated internally) usually leads to interleaving like:\n" << output;
    }



}
