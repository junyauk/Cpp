#include "pch.h"
#include "gtest/gtest.h"
#include "..\01_StructuredBinding\StructuredBindings_Advance.h"

// Define the test fixture class
namespace StructuredBindingsAdvanceTest
{
    class BindingsAdvanceTest : public ::testing::Test
    {
    protected:
        STRUCTUREDBINDINGS_Advance::MapDemo m_mapDemo;
        STRUCTUREDBINDINGS_Advance::Bindings_Advance m_bindingsAdvance;
    };

    // Test Case 1: Application of reference binding for update (using map::insert return)
    TEST_F(BindingsAdvanceTest, UpdateExisting_ReferenceBinding)
    {
        // Key 2 already exists -> Expect UPDATED, and value changes to "Modified Two"
        std::string result = m_mapDemo.updateExisting(2, "Modified Two");
        ASSERT_EQ("UPDATED: Key 2 modified.", result);

        // Key 3 does not exist -> Expect INSERTED
        result = m_mapDemo.updateExisting(3, "Three");
        ASSERT_EQ("INSERTED: New key 3 added.", result);

        // Verify the map contents
        auto contents = m_mapDemo.listMapContents();
        ASSERT_EQ(3, contents.size());
        // Verify Key 2 was updated
        ASSERT_EQ("Modified Two", contents.at(1).second);
        ASSERT_EQ("Modified Two", contents[1].second);
        // Verify Key 3 was inserted
        ASSERT_EQ("Three", contents.at(2).second);
        ASSERT_EQ("Three", contents[2].second);
    }

    // Test Case 2: Application in iteration (Range-based for loop)
    TEST_F(BindingsAdvanceTest, ListMapContents_IterationBinding)
    {
        // MapDemo::listMapContents() uses range-based for loop with structured binding
        auto contents = m_mapDemo.listMapContents();

        ASSERT_EQ(2, contents.size());
        ASSERT_EQ(1, contents[0].first);
        ASSERT_EQ("One", contents[0].second);
        ASSERT_EQ(2, contents[1].first);
        ASSERT_EQ("Two", contents[1].second);

        ASSERT_EQ(1, contents.at(0).first);
        ASSERT_EQ("One", contents.at(0).second);
        ASSERT_EQ(2, contents.at(1).first);
        ASSERT_EQ("Two", contents.at(1).second);
    }

    // Test Case 3: Reference binding on a tuple-like type (std::array) for modification
    TEST_F(BindingsAdvanceTest, ModifyArrayElement_ReferenceBinding)
    {
        std::array<int, 2> arr{ 10,20 };

        // The function modifies an element of 'arr' via reference binding.
        m_bindingsAdvance.modifyArrayElements(arr, 99);

        // Verify the second element has been changed
        ASSERT_EQ(10, arr[0]);
        ASSERT_EQ(10, arr.at(0));
        ASSERT_EQ(99, arr[1]);
        ASSERT_EQ(99, arr.at(1));

        // Also verify direct reference binding within the test scope
        auto& [a, b] = arr;
        a = 5;
        ASSERT_EQ(5, arr[0]);
        ASSERT_EQ(5, arr.at(0));
    }

    // Test Case 4: Reference Binding Lifetime (Conceptual Check)
    TEST(BindingsAdvanceConcept, Lifetime_AvoidDangling)
    {
        // C++17 ensures safety: The lifetime of the temporary object (PairStruct{1, 2}) 
        // is extended to the scope of the structured binding ([a, b]).
        struct PairStruct { int a; int b; };

        const auto [a, b] = PairStruct{ 1,2 };
        ASSERT_EQ(1, a);
        ASSERT_EQ(2, b);
    }
}
