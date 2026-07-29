module;

#include <cmath> // Include is fine in implementation units

module FinancialUtils; // Associates this implementation with the module

namespace Modules_Basic
{
    // Implementation for exported function
    double calculationSimpleInterest(double principal, double rate, int years)
    {
        // Interest = Principal * Rate * Time
        return principal * rate * static_cast<double>(years);
    }

    // Implementation for exported class methods
    void BudgetTracker::deposit(double amount)
    {
        if (amount > 0)
        {
            m_balance += amount;
        }
        // internalLogging("Deposit made: " + std::to_string(amount)); 
    }

    bool BudgetTracker::withdraw(double amount)
    {
        if (amount > 0 && m_balance >= amount)
        {
            m_balance -= amount;
            return true;
        }
        return false;
    }

    // A non-exported helper class implementation can also go here
}
