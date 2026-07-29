#include "pch.h"
#include "..\04_Concurrency\Concurrency_Basic.h"

using namespace Concurrency_Basic;

namespace Concurrency_Basic_Test
{
	class ConcurrencyBasicTest : public ::testing::Test
	{
	protected:
		ConcurrencyBasic m_concurrencyBasic;
	};

    // Test case to verify jthread starts, runs, and stops gracefully via stop_token
	TEST_F(ConcurrencyBasicTest, JThread_StopToken_GracefulStop)
	{
		// Wait duration (ms). The thread task takes 10ms per loop.
		int waitDuration = 50;
		int finalCount = m_concurrencyBasic.runAndStopThread(waitDuration);

		// The thread should have executed at least a few times (e.g., 2 to 7 times).
		// Since timing is unreliable, we only check for a positive count.
		EXPECT_GT(finalCount, 0);

		// The count should not be excessively large (e.g., less than 100)
		// This confirms the stop request was honored.
		EXPECT_LT(finalCount, 100);
	}

	// Test case to verify that jthread automatically joins when scope ends
	TEST_F(ConcurrencyBasicTest, JThread_AutoJoin_NoTerminate)
	{
		// This test primarily ensures no std::terminate is called due to forgotten join().
		// The function runAndStopThread() itself ensures the jthread is safely joined.
		int waitDuration = 10;

		// If the thread was not auto-joined, the test environment would likely crash 
		// or print an error when the worker goes out of scope.
		int finalCount = m_concurrencyBasic.runAndStopThread(waitDuration);

		EXPECT_GT(finalCount, 0);
	}

	// ------------------------------------------------------------------------
	// std::latch

	// Test case to verify synchronization using std::latch
	TEST_F(ConcurrencyBasicTest, LatchSynchronization_Arrival)
	{
		int numWorkers = 5;

		// Expected result: Sum of IDs from 1 to 5 (1+2+3+4+5 = 15)
		int expectedSum = 15;

		int result = m_concurrencyBasic.runLatchSynchronization(numWorkers);

		// Verifies that the synchronization worked and all threads completed their final task.
		EXPECT_EQ(expectedSum, result);
	}

	// Test case for a different number of workers
	TEST_F(ConcurrencyBasicTest, LatchSynchronization_DifferentCount)
	{
		int numWorkers = 3;

		// Expected result: Sum of IDs from 1 to 3 (1+2+3 = 6)
		int expectedSum = 6;

		int result = m_concurrencyBasic.runLatchSynchronization(numWorkers);

		EXPECT_EQ(expectedSum, result);
	}

	// ------------------------------------------------------------------------
	// std::barrier
	// Test case to verify multi-phase synchronization using std::barrier
	TEST_F(ConcurrencyBasicTest, BarrierSynchronization_MultiPhase)
	{
		int numWorkers = 4;

		// Expected result: Sum of (ID * 10) for IDs 1 to 4
		// (1*10) + (2*10) + (3*10) + (4*10) = 10 + 20 + 30 + 40 = 100
		int expectedSum = 100;

		int result = m_concurrencyBasic.runBarrierSynchronization(numWorkers);

		// Verifies that both phases were completed and the final result aggregated correctly.
		EXPECT_EQ(expectedSum, result);
	}

	// Test case for a smaller number of workers
	TEST_F(ConcurrencyBasicTest, BarrierSynchronization_SmallCount)
	{
		int numWorkers = 2;

		// Expected result: Sum of (ID * 10) for IDs 1 to 2
		// (1*10) + (2*10) = 30
		int expectedSum = 30;

		int result = m_concurrencyBasic.runBarrierSynchronization(numWorkers);

		EXPECT_EQ(expectedSum, result);
	}
}
