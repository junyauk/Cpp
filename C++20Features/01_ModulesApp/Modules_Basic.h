#pragma once

#include <string>

namespace Modules_Basic
{
    /**
     * @brief Utility class that demonstrates the usage of the FinancialUtils module.
     * This class acts as the consumer of the C++20 Module.
     */
    class ModulesBasic
    {
    public:
        ModulesBasic() = default;

        /**
         * @brief Calculates simple interest using the imported module function.
         * @param p Principal amount.
         * @param r Annual interest rate (as a fraction, e.g., 0.05 for 5%).
         * @param y Number of years.
         * @return The simple interest amount.
         */
        double runSimpleInterestCalculation(double p, double r, int y);

        /**
         * @brief Performs deposit and withdrawal operations using the imported module class.
         * @param accountName The name of the account.
         * @param initialBalance The starting balance.
         * @param depositAmount The amount to deposit.
         * @param withdrawalAmount The amount to withdraw.
         * @return The final balance after operations.
         */
        double runBudgetTrackerOperations(const std::string& accountName, double initialBalance, double depositAmount, double withdorawAmount) const;
    };

}