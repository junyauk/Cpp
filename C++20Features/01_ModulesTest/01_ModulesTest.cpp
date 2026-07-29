#include "pch.h"
#include "..\01_ModulesApp\Modules_Basic.h"

using Modules_Basic::ModulesBasic;

namespace Modules_Basic_Test
{
	class ModulesBasicTest : public ::testing::Test
	{
	protected:
		ModulesBasic m_moduleBasic;
	};

	// Test case for simple interest calculation
	TEST_F(ModulesBasicTest, SimpleInterestCalculation)
	{
		double principal = 1000.0;
		double rate = 0.05;
		int years = 2;

		// Interest = 1000 * 0.05 * 2 = 100.0
		double expectedInterest = 100.0;

		double result = m_moduleBasic.runSimpleInterestCalculation(principal, rate, years);
		// EXPECT_NEAR is used for floating point comparisons
		EXPECT_NEAR(expectedInterest, result, 0.001);
	}

	// Test case for budget tracker operations
	TEST_F(ModulesBasicTest, BudgetTrackerOperations)
	{
		std::string account = "Savings";
		double initial = 500.0f;
		double deposit = 200.0f;
		double withdrawal = 150.0f;

		// Final Balance = 500.0 (initial) + 200.0 (deposit) - 150.0 (withdrawal) = 550.0
		double expectedBalance = 550.0f;
		double result = m_moduleBasic.runBudgetTrackerOperations(account, initial, deposit, withdrawal);
		EXPECT_NEAR(expectedBalance, result, 0.001);
	}
}
