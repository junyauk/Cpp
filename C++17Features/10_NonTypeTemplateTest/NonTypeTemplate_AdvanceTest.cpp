#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_NonTypeTemplate\NonTypeTemplate_Advance.h"

namespace NonTypeTemplateAdvanceTest
{
    // C++17 requires that non-type template arguments of pointer/reference type 
    // must refer to an entity with external linkage. We define them here.
    static constexpr char KEY_USER[] = "User";
    static constexpr char KEY_ADMIN[] = "Admin";
    static constexpr char KEY_CONFIG[] = "ConfigKey";

    class NonTypeTemplateAdvanceTest : public ::testing::Test
    {
    protected:
        // No members needed
    };

    // Test Case 1a: Compile-Time Hashing Check - Different Keys
    TEST_F(NonTypeTemplateAdvanceTest, ConstexprHash_DifferentKeys)
    {
        // Use the defined static constexpr variables and their size for C++17 compatibility.
        uint32_t hash1 = NonTypeTemplate_Advance::ConstexprHash<KEY_USER, sizeof(KEY_USER) - 1>::value;
        uint32_t hash2 = NonTypeTemplate_Advance::ConstexprHash<KEY_ADMIN, sizeof(KEY_ADMIN) - 1>::value;

        // Verify that hash values are computed at compile time and are different
        ASSERT_NE(hash1, hash2);

        // Verify consistency with the runtime hash function
        ASSERT_EQ(NonTypeTemplate_Advance::NonTypeTemplate_Advance::getHashValue("User"), hash1);
        ASSERT_EQ(NonTypeTemplate_Advance::NonTypeTemplate_Advance::getHashValue("Admin"), hash2);
    }

    // Test Case 1b: Compile-Time Hashing Check - Same Keys
    TEST_F(NonTypeTemplateAdvanceTest, ConstexprHash_SameKeys)
    {
        // Use the defined static constexpr variable
        uint32_t hashA = NonTypeTemplate_Advance::ConstexprHash<KEY_CONFIG, sizeof(KEY_CONFIG) - 1>::value;
        uint32_t hashB = NonTypeTemplate_Advance::ConstexprHash<KEY_CONFIG, sizeof(KEY_CONFIG) - 1>::value;

        // Verify hash values are identical
        ASSERT_EQ(hashA, hashB);
    }

    // Test Case 2: std::array Type Deduction
    TEST_F(NonTypeTemplateAdvanceTest, SizedArray_TypeDeduction)
    {
        // Pass a constexpr size value to the template function
        constexpr size_t array_size = 5;
        auto arr = NonTypeTemplate_Advance::NonTypeTemplate_Advance::createSizeArray<array_size>();

        // Verify the array size was correctly deduced
        ASSERT_EQ(array_size, arr.size());

        // Statically verify the deduced type
        static_assert(std::is_same_v<decltype(arr), std::array<int,5>>,
            "Array type must be deduced correctly.");
    }

    // Test Case 3a: Unifying Heterogeneous Data Structures (int range)
    TEST_F(NonTypeTemplateAdvanceTest, Range_Int)
    {
        // Range<int, int> is generated from auto S=10, auto E=20
        auto range = NonTypeTemplate_Advance::NonTypeTemplate_Advance::createRange<10, 20>();

        ASSERT_EQ(10, range.size());
        ASSERT_NE(std::string::npos, range.getInfo().find("Range: [10 to 20]"));

        // Verify the deduced ValueType is int
        static_assert(std::is_same_v<decltype(range)::ValueType, int>,
            "ValueType must be int.");
    }

    // Test Case 3b: Unifying Heterogeneous Data Structures (char range)
    TEST_F(NonTypeTemplateAdvanceTest, Range_Char)
    {
        // Range<char, char> is generated from auto S='a', auto E='z'
        auto range = NonTypeTemplate_Advance::NonTypeTemplate_Advance::createRange<'a', 'z'>();

        // 'z' - 'a' = 25
        ASSERT_EQ(25, range.size());
        ASSERT_NE(std::string::npos, range.getInfo().find("Range: [97 to 122]"));

        // Verify the deduced ValueType is char
        static_assert(std::is_same_v<decltype(range)::ValueType, char>,
            "ValueType must be char.");
    }
}
