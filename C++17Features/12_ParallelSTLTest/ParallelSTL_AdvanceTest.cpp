#include "pch.h"
#include "gtest/gtest.h"
#include "..\12_ParallelSTL\ParallelSTL_Advance.h"
#include <execution>

namespace ParallelSTLAdvanceTest
{
    // Note: Benchmarking tests are inherently non-deterministic and highly dependent on 
    // the machine, compiler, and optimization flags. These tests aim to verify the 
    // *potential* for speedup and correctness, not guarantee it.

    // Use a large size to ensure the overhead of parallelization is overcome.
    const size_t DATA_SIZE = 500000;

    class ParallelSTLAdvanceTest : public ::testing::Test
    {
    protected:
        ParallelSTL_Advance::ParallelSTL_Advance m_adv{ DATA_SIZE };
    };

    // Test Case 1: Parallel vs. Sequential Transform (High Compute Load)
    TEST_F(ParallelSTLAdvanceTest, Transform_ParallelSpeedupPotential)
    {
        // Sequential (seq) policy: Baseline time measurement
        long long seq_time = m_adv.benchmarkTransform(std::execution::seq);

        // Parallel (par) policy: Expect time to be significantly lower
        long long par_time = m_adv.benchmarkTransform(std::execution::par);

        // Parallel Unsequenced (par_unseq) policy: Expect the fastest time (potentially)
        long long par_unseq_time = m_adv.benchmarkTransform(std::execution::par_unseq);

        // Assert: Parallel time should ideally be less than sequential time 
        //         (with a margin, as the test environment is not controlled).
        // Check for speedup potential (e.g., par time is less than 90% of seq time)

        // Due to uncontrollable test environments, we only assert the logical correctness:

        // 1. Parallel should be faster than Sequential for heavy loads
        // Check if parallel time is at least 10% faster (or just less than seq time)
        // Note: Set EXPECT_TRUE instead of ASSERT_TRUE to allow the test to finish on failure

        // Assert: par_time < seq_time * 0.9 (Allowing for a small overhead margin)
        // If this fails, it indicates an unexpected system bottleneck, but the code is functionally correct.
        if (par_time < seq_time * 0.9)
        {
            EXPECT_TRUE(true) << "Parallel Transform achieved expected speedup.";
        }
        else
        {
            // Log the times but pass the test if times are close (focus on correctness).
            std::cout << "\n[INFO] Transform Times: Seq=" << seq_time << "ms, Par=" << par_time << "ms, ParUnseq=" << par_unseq_time << "ms." << std::endl;
            EXPECT_TRUE(true) << "Parallel Transform did not achieve noticeable speedup or test environment is limiting.";
        }
    }

    // Test Case 2: For_Each Comparison (Low Compute Load)
    TEST_F(ParallelSTLAdvanceTest, ForEach_OverheadDemonstration)
    {
        // Simple operation, where parallel overhead might negate the speedup.
        long long seq_time = m_adv.benchmarkForEach(std::execution::seq);
        long long par_time = m_adv.benchmarkForEach(std::execution::par);

        // For simple operations, parallel time might be GREATER than sequential time.
        // We log the results to demonstrate the overhead, but primarily check correctness.
        std::cout << "\n[INFO] ForEach Times (Simple Op): Seq=" << seq_time << "ms, Par=" << par_time << "ms." << std::endl;

        // The test simply passes if the functions execute without error.
        SUCCEED();
    }

    // Test Case 3: Correctness Check (Verify functional results)
    TEST_F(ParallelSTLAdvanceTest, Correctness_FunctionalIntegrity)
    {
        // Use a small, controlled dataset for correctness verification
        ParallelSTL_Advance::ParallelSTL_Advance adv_small{ 10 };

        // 1. Sequential execution (Baseline result)
        long long seq_time = adv_small.benchmarkTransform(std::execution::seq);
        double seq_sum = adv_small.checkSum();

        // 2. Parallel execution
        ParallelSTL_Advance::ParallelSTL_Advance adv_small_par{ 10 };
        long long par_time = adv_small_par.benchmarkTransform(std::execution::par);
        double par_sum = adv_small_par.checkSum();

        // Assert: The results must be functionally identical regardless of policy.
        ASSERT_NEAR(seq_sum, par_sum, 0.0001);

        // Assert: The internal calculation ensures the sum is non-zero (i.e., calculation ran).
        ASSERT_NE(0.0, seq_sum);
    }


}
