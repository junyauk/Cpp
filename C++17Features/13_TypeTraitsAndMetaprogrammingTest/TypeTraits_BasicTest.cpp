#include "pch.h"
#include "gtest/gtest.h"
#include "..\13_TypeTraitsAndMetaprogramming\TypeTraits_Basic.h"
#include <sstream>
#include <string>
#include <type_traits>
#include <functional>
#include <iostream>

namespace TypeTraitsBasicTest
{
    // Helper to capture cout output
    std::string capture_output(std::function<void()> func)
    {
        std::stringstream ss;
        std::streambuf* old_cout = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        func();

        std::cout.rdbuf(old_cout);
        return ss.str();
    }

    class TypeTraitsBasicTest : public ::testing::Test
    {
    protected:
        // No members needed
    };

    // Test Case 1: std::is_integral_v Check
    TEST_F(TypeTraitsBasicTest, IsIntegral_Check)
    {
        // Check for known integral types
        ASSERT_TRUE(std::is_integral_v<int>);
        ASSERT_TRUE(std::is_integral_v<char>);

        // Check for known non-integral types
        ASSERT_FALSE(std::is_integral_v<double>);
        ASSERT_FALSE(std::is_integral_v<std::string>);

        // Check output demonstration function
        std::string output = capture_output([]()
            {
                TypeTraits_Basic::TypeTraits_Basic::demoIntegralCheck();
            });

        // The output string should contain the expected results (checking for success)
        ASSERT_NE(std::string::npos, output.find("Type int is an integral type.")); // 'i' is often the mangled name for int
        ASSERT_NE(std::string::npos, output.find("Type double is NOT an integral type.")); // 'd' is often the mangled name for double
    }

    // Test Case 2: std::is_same_v Check
    TEST_F(TypeTraitsBasicTest, IsSame_Check)
    {
        // Same types
        ASSERT_TRUE((std::is_same_v<int, int>));

        // Different types (non-const vs const)
        ASSERT_FALSE((std::is_same_v<int, const int>));

        // Different types (reference vs value)
        ASSERT_FALSE((std::is_same_v<int, int&>));
    }

    // Test Case 3: decltype Application
    TEST_F(TypeTraitsBasicTest, Decltype_LambdaReturnType)
    {
        // Create the lambda
        auto lambda = TypeTraits_Basic::TypeTraits_Basic::createLambda();

        // Use decltype to deduce the return type of the lambda's operator()
        using LambdaReturnType = decltype(lambda(0,0.0));

        // Verify the deduced type is int, as specified in the lambda's -> int
        ASSERT_TRUE((std::is_same_v<LambdaReturnType, int>));

        // Verify the lambda's functionality
        ASSERT_EQ(6, lambda(3, 2.3));   // 3 * 2.3 = 6.9 -> 6
    }

}

