#include "pch.h"
#include "gtest/gtest.h"
#include "..\01_ConceptsAndRanges\Combined_Processor.h"

using namespace Combined_learning;

namespace Combined_Learning_Test
{
	std::vector<DataEntry> create_test_data()
	{
		return
		{
			{1, 10.5, "A"},
			{2, 5.0,  "B"},
			{3, 20.0, "C"},
			{4, 15.5, "D"},
			{5, 3.0,  "E"}
		};
	}

	// Helper to run the test for any IProcessor implementation
	void run_processor_test(const IProcessor& processor)
	{
		std::cout << "\n--- Testing Style: " << processor.get_style() << " ---" << std::endl;
		auto data = create_test_data();

		// Threshold = 10.0
		// Expected results: 10.5, 20.0, 15.5
		// Expected Sum: 10.5 + 20.0 + 15.5 = 46.0
		double threshold = 10.0;
		double result = processor.process_and_sum(data, threshold);

		std::cout << "  Threshold: " << threshold << std::endl;
		std::cout << "  Result Sum: " << result << std::endl;

		// Use EXPECT_NEAR for floating point comparison
		EXPECT_NEAR(result, 46.0, 1e-9);

		// Test case 2: Higher threshold (only 20.0 and 15.5 pass)
		threshold = 15.0;
		result = processor.process_and_sum(data, threshold);

		// Expected Sum: 20.0 + 15.5 = 35.5
		EXPECT_NEAR(result, 35.5, 1e-9);
	}

	TEST(CombinedProcessorTest, ComparisonTest)
	{
		Cpp17Processor p17;
		run_processor_test(p17);

		Cpp20Processor p20;
		run_processor_test(p20);

		// Example Concepts failure check (will not be run by gtest, but proves concept works)
		// p20.compute_average(data); // Fails compilation because DataEntry is not arithmetic

		// p20.compute_average({1, 2, 3}); // Compiles successfully because it's a NumericRange
	}

	std::vector<DataEntry> create_unique_test_data()
	{
		return {
			{1, 10.0, "A"},
			{2, 5.0,  "B"},
			{1, 10.0, "A"}, // Duplicate of 1
			{3, 20.0, "C"},
			{2, 5.0,  "B"}, // Duplicate of 2
			{4, 15.0, "D"}
		};
		// Expected unique, sorted array (by default <=> on ID then Value):
		// {1, 10.0}, {2, 5.0}, {3, 20.0}, {4, 15.0}
		// Expected unique reverse sum (15.0 + 20.0 + 5.0 + 10.0) = 50.0
	}

	TEST(CombinedProcessorTest, ConceptsAppliedUniqueCount)
	{
		Cpp20Processor p20;
		auto data_with_duplicates = create_unique_test_data();

		// Original: {1, 10.0, "A"}, {2, 5.0,  "B"}, {1, 10.0, "A"}, {3, 20.0, "C"}, {2, 5.0,  "B"}, {4, 15.0, "D"}
		// Unique Count: ({1, 10.0}, {2, 5.0}, {3, 20.0}, {4, 15.0})

		// Concepts (SortableRange)
		size_t unique_count = p20.count_unique_elements(data_with_duplicates);

		EXPECT_EQ(unique_count, 4);

		// Concepts Check:
		std::vector<int> numbers = { 3, 1, 3, 2, 1 }; // Unique count: 3
		size_t unique_num_count = p20.count_unique_elements(numbers);
		EXPECT_EQ(unique_num_count, 3);
	}

	TEST(CombinedProcessorTest, ConceptsAppliedMovableAndSizedRange)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		auto data1 = create_unique_test_data();
		size_t expected_size_half = data1.size() / 2; // 6 / 2 = 3

		// 1. C++17 style
		size_t result17 = p17.process_and_check_size(data1);

		// 2. C++20 style
		// Copy data2 for moving
		auto data2 = create_unique_test_data();
		size_t result20 = p20.process_and_check_size(data2);

		std::cout << "\n--- Testing Movable & Sized Range Check ---" << std::endl;
		std::cout << "  Original Size: " << create_unique_test_data().size() << std::endl;
		std::cout << "  C++17 Result (Half Size): " << result17 << std::endl;
		std::cout << "  C++20 Result (Half Size): " << result20 << std::endl;

		EXPECT_EQ(result17, expected_size_half);
		EXPECT_EQ(result20, expected_size_half);

		// Concepts Check (Compile time)
		// std::vector is sized_range and forward_range and DataEntry is movable, so it can be compiled without error.
		// If compiled without errors. It proved concepts passed.
	}


	TEST(CombinedProcessorTest, ConceptsAppliedFilterAndOutput)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		std::vector<DataEntry> data = create_test_data();

		// Data: {10.5, "A"}, {5.0, "B"}, {20.0, "C"}, {15.5, "D"}, {3.0, "E"}

		// Filter targets: Only one element containing "C"
		size_t result17 = p17.filter_and_output(data, "C");
		size_t result20 = p20.filter_and_output(data, "C");

		std::cout << "\n--- Testing Filter and Output (Concepts/Requires) ---" << std::endl;
		std::cout << "  Filter Tag: C" << std::endl;
		std::cout << "  C++17 Result (Count): " << result17 << std::endl;
		std::cout << "  C++20 Result (Count): " << result20 << std::endl;

		EXPECT_EQ(result17, 1);
		EXPECT_EQ(result20, 1);

		// Filter target: "Z" which doesn't exist
		EXPECT_EQ(p20.filter_and_output(data, "Z"), 0);

		// Concepts/Requires:
		// Cpp20Processor::filter_to_container definition
		// If the input_range hasn't got operator==,
		// or the output container doesn't contain DataEntry,
		// It will cause compile errors.
		// This will be checked when compiling time.
	}



	TEST(CombinedProcessorTest, ConceptsAppliedRandomAccessAndIntegral)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		std::vector<DataEntry> data = create_test_data(); // 5—v‘f
		// ID: 1, 2, 3, 4, 5

		// 1. Find existing id (ID=3 is index 2)
		long long expected_index = 2;
		int target_id = 3;

		long long result17 = p17.process_and_find_index(data, target_id);
		long long result20 = p20.process_and_find_index(data, target_id);

		std::cout << "\n--- Testing Random Access & Find Index ---" << std::endl;
		std::cout << "  Target ID: " << target_id << std::endl;
		std::cout << "  Expected Index: " << expected_index << std::endl;
		std::cout << "  C++20 Result: " << result20 << std::endl;

		EXPECT_EQ(result17, expected_index);
		EXPECT_EQ(result20, expected_index);

		// 2. Find NOT existing id
		target_id = 99;
		EXPECT_EQ(p20.process_and_find_index(data, target_id), -1);

		// Concepts Check: IntegralArgument
		// Try bellow for checking it causes compile error (because 3.14 is not int)
		// Cpp20Processor::find_index(data, 3.14);
	}

	TEST(CombinedProcessorTest, ConceptsAppliedConcatenationAndComparison)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		std::vector<DataEntry> data = create_test_data(); // 5 elements
		size_t original_size = data.size(); // 5

		// 1. OK case (min_count = 5)
		size_t min_count_ok = 5;
		size_t expected_size = original_size * 2; // 10

		size_t result17 = p17.process_and_concat(data, min_count_ok);
		size_t result20 = p20.process_and_concat(data, min_count_ok);

		std::cout << "\n--- Testing Concatenation & Comparison (Concepts) ---" << std::endl;
		std::cout << "  Original Size: " << original_size << ", Min Count: " << min_count_ok << std::endl;
		std::cout << "  Expected Size: " << expected_size << std::endl;
		std::cout << "  C++20 Result: " << result20 << std::endl;

		EXPECT_EQ(result17, expected_size);
		EXPECT_EQ(result20, expected_size);

		// 2. NG case (min_count = 6) -> expecting std::out_of_range exception
		size_t min_count_fail = 6;

		// Exception check in C++17 style
		EXPECT_THROW(p17.process_and_concat(data, min_count_fail), std::out_of_range);

		// Exception check in C++20 style (thrown from Concepts applied function)
		EXPECT_THROW(p20.process_and_concat(data, min_count_fail), std::out_of_range);

		// Concepts Check: ThreeWayComparable & DefaultInitializable
		// DataEntry has got operator<=>, so ThreeWayComparable is satisified
		// DataEntry has got default constructor, DefaultInitializable is satisified
	}

	TEST(CombinedProcessorTest, ConceptsAppliedSliceAndConvertible)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		std::vector<DataEntry> data = create_test_data(); // 5 elements
		// 5 elements -> slice (drop 1, take 3) -> left 3 elements

		// 1. OK case (max_elements_double = 10.0) -> left 3 elements
		double max_limit_ok = 10.0;
		size_t expected_size = 3;

		size_t result17 = p17.process_and_slice(data, max_limit_ok);
		size_t result20 = p20.process_and_slice(data, max_limit_ok);

		std::cout << "\n--- Testing Slice (drop/take) & Convertible Concepts ---" << std::endl;
		std::cout << "  Original Size: 5, Sliced Size: 3" << std::endl;
		std::cout << "  C++20 Result: " << result20 << std::endl;

		EXPECT_EQ(result17, expected_size);
		EXPECT_EQ(result20, expected_size);

		// 2. Limitad case (max_elements_double = 1.0) -> return 1 element (limit val)
		double max_limit_fail = 1.0;
		expected_size = 1; // return limit val

		result20 = p20.process_and_slice(data, max_limit_fail);
		EXPECT_EQ(result20, expected_size);

		// Concepts Check: ConvertibleToSizeT
		// Check bellow, if it causes compile error (because std::string can't be converted to size_t)
		// Cpp20Processor::slice_and_count(data, std::string("oops")); 
	}

	TEST(CombinedProcessorTest, ConceptsAppliedBidirectionalAndInvocable)
	{
		Cpp17Processor p17;
		Cpp20Processor p20;

		std::vector<DataEntry> data = create_test_data(); // 5 elements: {10.5, 5.0, 20.0, 15.5, 3.0}

		// Expected: Total of 0 (10.5), 2 (20.0), 4 (3.0)
		double expected_sum = 10.5 + 20.0 + 3.0; // 33.5

		double result17 = p17.process_bidirectional_stride_sum(data);
		double result20 = p20.process_bidirectional_stride_sum(data);

		std::cout << "\n--- Testing Bidirectional Stride Sum ---" << std::endl;
		std::cout << "  Original Data Values: 10.5, 5.0, 20.0, 15.5, 3.0" << std::endl;
		std::cout << "  Expected Sum (0, 2, 4th): " << expected_sum << std::endl;
		std::cout << "  C++20 Result: " << result20 << std::endl;

		EXPECT_NEAR(result17, expected_sum, 1e-9);
		EXPECT_NEAR(result20, expected_sum, 1e-9);

		// Concepts Check: Invocable/Bidirectional

		// Reverse filtering test of BidirectionalRange
		auto is_large = [](const DataEntry& e) { return e.value > 15.0; };
		// Reverse scan: {3.0, 15.5, 20.0, 5.0, 10.5} -> large: 15.5, 20.0 (2 elements)
		size_t filtered_count = p20.count_filtered_bidirectional(data, is_large);
		EXPECT_EQ(filtered_count, 2);
	}

}


