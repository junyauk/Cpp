#include "pch.h"
#include "gtest/gtest.h"
#include <sstream>
#include <functional>
#include "..\13_TypeTraitsAndMetaprogramming\TypeTraits_Advance.h"

namespace TypeTraitsAdvanceTest
{
    // Helper to capture cout output
    std::string capture_output(std::function<void()> func)
    {
        std::stringstream ss;
        // Redirect cout to ss
        std::streambuf* old_out = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        func();

        // Restore cout
        std::cout.rdbuf(old_out);
        return ss.str();
    }

    class TypeTraitsAdvanceTest : public ::testing::Test
    {
    protected:
    };

    // Test Case 1: Type Normalization (std::decay_t)
    TEST_F(TypeTraitsAdvanceTest, DecayType_Normalization)
    {
        int x = 5;
        const int& ref_x = x;

        // Input: const int& (T&& resolves to const int&)
        std::string output = capture_output([&]()
            {
                TypeTraits_Advance::print_decayed_type_info(ref_x);
            });
        // Expected output: Original type is a reference, Decayed type is int (i on Unix/GCC, int on MSVC)
        ASSERT_TRUE(output.find("L-value reference") != std::string::npos);

        // Input: int&& (T&& resolves to int&&)
        output = capture_output([&]()
            {
                TypeTraits_Advance::print_decayed_type_info(std::move(x));
            });

        // Expected output: Original type is an r-value reference
        ASSERT_TRUE(output.find("R-value reference") != std::string::npos);
    }

    // Test Case 2a: Conditional Compilation (Arithmetic Type)
    TEST_F(TypeTraitsAdvanceTest, ConditionalCompilation_Arithmetic)
    {
        TypeTraits_Advance::Calculator<double> calc{ 10.0 };

        // double is arithmetic, so add_and_double should exist
        double result = calc.add_and_double(5.0);

        // (10.0 + 5.0) * 2 = 30.0
        ASSERT_NEAR(30.0, result, 0.001);
    }

    // Test Case 2b: Conditional Compilation (Pointer Type)
    TEST_F(TypeTraitsAdvanceTest, ConditionalCompilation_Pointer)
    {
        // Use a safe pointer value for demonstration
        int* ptr = reinterpret_cast<int*>(0x1000);
        TypeTraits_Advance::Calculator<int*> calc{ ptr };

        // int* is a pointer, so increment_pointer should exist
        int* result_ptr = calc.increment_pointer();

        // Should increment by sizeof(int)
        ASSERT_EQ(reinterpret_cast<long>(ptr) + sizeof(int), reinterpret_cast<long>(result_ptr));

        // Note: The failure check (e.g., calling add_and_double on calc<int*>) 
        // is a compile-time SFINAE test, not a runtime test.
        SUCCEED();
    }

    // Test Case 3: Perfect Forwarding Verification
    TEST_F(TypeTraitsAdvanceTest, PerfectForwarding_Verification)
    {
        int a = 10;

        // Forwarding L-value: T is deduced as int&
        std::string lvalue_result = TypeTraits_Advance::ForwardingTester::forward_and_check(a);

        // Forwarding R-value: T is deduced as int (with T&& forming an r-value reference)
        std::string rvalue_result = TypeTraits_Advance::ForwardingTester::forward_and_check(std::move(a));

        // L-value should be detected as L-value reference
        ASSERT_TRUE(lvalue_result.find("L-value") != std::string::npos);

        // R-value should be detected as R-value 
        ASSERT_TRUE(rvalue_result.find("R-value") != std::string::npos);
    }
}
