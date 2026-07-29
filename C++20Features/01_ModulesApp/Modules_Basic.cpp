#include "pch.h"
#include "Modules_Basic.h"

import FinancialUtils;

namespace Modules_Basic
{
    // The class uses the imported module functions/classes.
    double ModulesBasic::runSimpleInterestCalculation(double p, double r, int y)
    {
        // The imported module's content is available under the module name
        // (FinancialUtils) and its exported namespace (Modules_Basic).
        return calculationSimpleInterest(p, r, y);
    }

    double ModulesBasic::runBudgetTrackerOperations(const std::string& accountName, double initialBalance, double depositAmount, double withdorawAmount) const
    {
        BudgetTracker tracker(accountName, initialBalance);
        tracker.deposit(depositAmount);
        tracker.withdraw(withdorawAmount);
        return tracker.getBalance();
    }
    // Note: If we tried to access FinancialUtils::Modules_Basic::internalLogging(), 
    // the compiler would issue an error because it was not 'export'ed.
}
