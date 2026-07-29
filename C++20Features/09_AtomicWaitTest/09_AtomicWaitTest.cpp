#include "pch.h"
#include "../09_AtomicWait/AtomicWait_Basic.h"
#include <thread>
#include <chrono>

using AtomicWait_Basic::AtomicWaitBasic;

namespace AtomicWait_Basic_Test
{
	class AtomicWaitTest : public ::testing::Test
	{
	protected:
		AtomicWaitBasic m_atomicBasic;
	};

	// Test case to verify the consumer waits for the producer's notification
	TEST_F(AtomicWaitTest, WaitNotify_Synchronization)
	{
		int targetValue = 42;

		// The consumer starts and immediately waits (since counter=0).
		// The producer updates the counter to 42 and notifies, allowing the consumer to exit.
		int finalCount = m_atomicBasic.runWaitNotify(targetValue);

		// Final count must be the value set by the producer.
		EXPECT_EQ(targetValue, finalCount);
	}

	// Test case to verify the basic atomic operation safety
	TEST_F(AtomicWaitTest, AtomicOperationSafety)
	{
		int targetValue = 100;
		int finalCount = m_atomicBasic.runWaitNotify(targetValue);

		EXPECT_EQ(100, finalCount);
	}
}
