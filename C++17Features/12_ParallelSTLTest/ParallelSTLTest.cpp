#include "pch.h"
#include "../12_ParallelSTL/ParallelSTL_Basic.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <chrono>

namespace ParallelSTLTest
{
    // Use a large size for noticeable performance difference
    constexpr size_t TEST_VECTOR_SIZE = 1000000; // 1 million elements

    class ParallelSTLTest : public ::testing::Test
    {
    protected:
        PARALLELSTL_Basic::ParallelSTL_Basic m_pstl;
    };

    // Test Case 1 & 2: Performance comparison and correctness check for std::sort
    TEST_F(ParallelSTLTest, SortPerformance_And_Correctness)
    {
        // 1. Generate random data
        std::vector<long> vec_seq = m_pstl.generateLargeVector(TEST_VECTOR_SIZE);
        std::vector<long> vec_par = vec_seq;

        // 2. Execute sequential sort
        double seq_duration = m_pstl.sortSequential(vec_seq);

        // 3. Execute parallel sort
        double par_duration = m_pstl.sortParallel(vec_par);

        // Correctness check: both should be sorted
        ASSERT_TRUE(std::is_sorted(vec_seq.begin(), vec_seq.end()));
        ASSERT_TRUE(std::is_sorted(vec_par.begin(), vec_par.end()));

        // Correctness check: both results must be identical
        ASSERT_EQ(vec_seq, vec_par);

        // Performance output (Informative)
        std::cout << "\n--- Sort Performance (" << TEST_VECTOR_SIZE << " elements) ---" << std::endl;
        std::cout << "  Sequential: " << seq_duration << " ms" << std::endl;
        std::cout << "  Parallel:   " << par_duration << " ms" << std::endl;
        // Expected: par_duration < seq_duration
        EXPECT_GT(seq_duration, par_duration);
    }

    // Test Case 3 & 4: Correctness check for std::for_each
    TEST_F(ParallelSTLTest, ForEach_ParallelExecutionIsCorrect)
    {
        // Initial values (squares of integers for simple math validation)
        std::vector<long> vec_seq = { 4, 9, 16, 25, 36 };
        std::vector<long> vec_par = vec_seq;

        // Expected result: complex_calc returns the value to its original state (4, 9, ...)
        std::vector<long> expected = { 4, 9, 16, 25, 36 };

        // --- Execute sequential process ---
        m_pstl.processSequentially(vec_seq);
        // --- Execute parallel process ---
        m_pstl.processInParallel(vec_par);

        // Correctness check
        ASSERT_EQ(expected, vec_seq);
        ASSERT_EQ(expected, vec_par);

        // Check that both results are identical
        ASSERT_EQ(vec_par, vec_seq);
    }

}
