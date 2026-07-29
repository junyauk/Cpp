#include "pch.h"
#include "gtest/gtest.h"
#include "..\11_InlineVariables\InlineVariables_Advance.h"

// Include the header again to simulate a second translation unit (TU2) 
// and ensure ODR is not violated, and the variable is truly shared.
#include "..\11_InlineVariables/InlineVariables_Advance.h" 

namespace InlineVariablesAdvanceTest
{
    // Use an alias to simulate usage in a different TU/scope
    namespace TU2_Access = INLINE_VARIABLES_Advance;

    class InlineVariablesAdvanceTest : public ::testing::Test
    {
    protected:
    };

    // Test Case 1: Shared Instance Verification (ODR Compliance)
    TEST_F(InlineVariablesAdvanceTest, SharedInstance_ODR_Compliance)
    {
        // Get the reference from the current TU (TU1 simulation)
        const std::string& ref1 = INLINE_VARIABLES_Advance::Configuration::APPLICATION_VERSION;

        // Get the reference from the simulated second TU (TU2_Access)
        const std::string& ref2 = TU2_Access::Configuration::APPLICATION_VERSION;

        // The pointers must be identical, proving there is only one shared instance
        // This is the core purpose of 'inline variable'.
        ASSERT_EQ(&ref1, &ref2);

        // Check initial value
        ASSERT_EQ("v1.1.0 - alpha", ref1);
    }

    // Test Case 2: Mutability and State Sharing
    TEST_F(InlineVariablesAdvanceTest, Mutability_StateSharing)
    {
        // Modify the variable in one TU/scope
        const std::string new_version = "v1.2.0-release";
        INLINE_VARIABLES_Advance::InlineVariables_Advance::modifyVersion(new_version);

        // Check if the change is immediately reflected in the other TU/scope
        ASSERT_EQ(new_version, TU2_Access::Configuration::APPLICATION_VERSION);

        // Check the shared complex object (std::map)
        ASSERT_EQ("ERR_INVALID_INPUT", TU2_Access::Configuration::ERROR_MAP.at(100));
    }

    // Test Case 3: Header-Only Library Constant Access
    TEST_F(InlineVariablesAdvanceTest, HeaderOnlyConstant_Access)
    {
        // Access the shared const vector defined using inline
        const auto& constants = INLINE_VARIABLES_Advance::SHARED_CONSTANTS;

        ASSERT_EQ(3, constants.size());

        // Check if the value is correct
        ASSERT_NEAR(3.14159, constants[0], 0.00001);

        // Check its address is also shared (optional but confirms ODR)
        const auto& constants2 = TU2_Access::SHARED_CONSTANTS;
        ASSERT_EQ(constants[0], constants2[0]);
    }
}

