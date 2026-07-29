#include "pch.h"
#include "gtest/gtest.h"
#include <type_traits>
#include "..\09_TemplateDeduction\CTAD_Advance.h"


namespace CTADAdvanceTest
{
	class CTADAdvanceTest : public ::testing::Test
	{
	protected:
	};

	// Test Case 1: User-Defined Class (MyVector) with Deduction Guides
	TEST_F(CTADAdvanceTest, CustomVector_DeductionFromInitializerList)
	{
		// MyVector vec = {1, 2, 3}; // Requires explicit deduction guide for C++17/20
		CTAD_Advance::MyVector vec = { 1,2,3 };

		// Verify the type was correctly deduced to MyVector<int>
		static_assert(std::is_same_v<decltype(vec), CTAD_Advance::MyVector<int>>);

		// Verify contents
		ASSERT_EQ(3, vec.size());
		ASSERT_EQ(2, vec.get(1));
	}

	TEST_F(CTADAdvanceTest, CustomVector_DeductionFromPointer)
	{
		int arr[] = { 100, 200 };
		// MyVector vec(arr, 2); // Uses the explicit deduction guide
		CTAD_Advance::MyVector vec(arr, 2);

		// Verify the type was correctly deduced to MyVector<int>
		static_assert(std::is_same_v<decltype(vec), CTAD_Advance::MyVector<int>>);

		// Verify contents
		ASSERT_EQ(2, vec.size());
		ASSERT_EQ(200, vec.get(1));
	}

	// Test Case 2: Standard Library Containers (std::map)
	TEST_F(CTADAdvanceTest, StandardMap_Deduction)
	{
		// CTAD on std::map
		std::map m = CTAD_Advance::CTAD_Advance::createStandardMap();

		// Verify the deduced type (std::map<int, std::string>)
		static_assert(std::is_same_v<decltype(m), std::map<int, std::string>>);

		// Verify contents
		ASSERT_EQ(2, m.size());
		ASSERT_EQ("Date", m[4]);
	}

	// Test Case 3: Constraints and Limits (Checking failure cases)
	TEST_F(CTADAdvanceTest, Deduction_FailureCases)
	{
		// NG case 1: std::vector that template args pack is empty
		// std::vector v; // In the case of C++17, it's error, can't deduct.

		// NG case 2: Type info is mixed (C++17/20)
		// std::pair p = {1, 2.5}; // std::pair can have different types, but container will fail

		// MyVector vec = {1, 2.5}; // different types are mixed, can't deduct T
		// NOTE: This will fail compilation and cannot be tested with ASSERT_THROW.
		// The test serves as a documentation of the limitation.

		// To verify CTAD behavior is to verify successful deduction.
		// If CTAD fails, the code will not compile.

		// Successful case: Deduction Guide for nested types (std::map)
		std::map<int, std::string> source_map = { {10, "Ten"}, {20, "Twenty"} };
		// Uses the explicit deduction guide: MyVector(const std::map<Key, Value>&) -> MyVector<std::pair<const Key, Value>>
		CTAD_Advance::MyVector map_vec(source_map.begin(), source_map.end());
		// The deduced type should be MyVector<std::pair<const int, std::string>>
		// The static_assert is correct and should now pass.
		static_assert(std::is_same_v<decltype(map_vec),
			CTAD_Advance::MyVector<std::pair<const int, std::string>>>);

		ASSERT_EQ(2, map_vec.size());
	}
}

