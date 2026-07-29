export module FinancialUtils; // Declares the module name

import <string>;
/**
 * @brief Module containing basic financial utility functions.
 * Only definitions prefixed with 'export' are visible outside this module.
 */

namespace Modules_Basic
{
    // The 'export' keyword makes this function visible to importers.
    export double calculationSimpleInterest(double principal, double rate, int years);

    // The 'export' keyword makes this class visible to importers.
    export class BudgetTracker
    {
    private:
        std::string m_accountName;
        double m_balance;

    public:
        BudgetTracker(std::string name, double initialBalance)
            : m_accountName(std::move(name)), m_balance(initialBalance) {}

        double getBalance() const { return m_balance; }
        void deposit(double amount);
        bool withdraw(double amount);
    };

    // This function is NOT exported, making it private to the module.
    std::string internalLogging(const std::string& message)
    {
        return "[LOG] " + message;
    }
}
