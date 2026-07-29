#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <compare>
#include <ranges>
#include <utility>

namespace Combined_learning
{
	// ========================================================================
	// --- Shared data structure ---
	struct DataEntry
	{
		int id{};
		double value{};
		std::string tag;

		// Using C++20's Three-Way Comparison for automatic ordering (Strong Ordering)
		auto operator<=>(const DataEntry&) const = default;
	};

	// --- Common Interface ---
	class IProcessor
	{
	public:
		virtual ~IProcessor() = default;
		// The core processing method: Filter entries with value > threshold and sum their values.
		virtual double process_and_sum(const std::vector<DataEntry>& data, double threshold) const = 0;
		virtual std::string get_style() const = 0;

		// Make unique values only and sum from back
		virtual double process_drop_reverse_sum(std::vector<DataEntry> data) const = 0;

		// Check if size of ranges can be got, and move elements to a new vector
		virtual size_t process_and_check_size(std::vector<DataEntry> data) const = 0;

		// Filter elements which has got the specific tag, and set the filtered elements to a new container
		virtual size_t filter_and_output(const std::vector<DataEntry>& data, const std::string& tag_filter) const = 0;

		// Filter if the range can be random accessed, and if the element has got the target id
		virtual long long process_and_find_index(const std::vector<DataEntry>& data, const int target_id) const = 0;

		// Check if the range size is bigger than the specified size, and returns the size of duplicated range
		virtual size_t process_and_concat(const std::vector<DataEntry>& data, size_t min_count) const = 0;

		// Extract the middle portion of the range (excluding the first and last elements) and return the number of elements in it.
		virtual size_t process_and_slice(const std::vector<DataEntry>& data, double max_elements_double) const = 0;

		// Verify bidirectional scanning capability and sum elements by skipping every other one (even-indexed elements).
		virtual double process_bidirectional_stride_sum(const std::vector<DataEntry>& data) const = 0;
	};

	// --- C++20 Style Concepts Definition (for C++20 implementation) ---
	// A concept to ensure the input is an iterable range of numeric elements
	template<typename T>
	concept NumericRange =
		std::ranges::range<T> &&								// iterable range
		std::is_arithmetic_v<std::ranges::range_value_t<T>>;	// numeric

	// Make sure that
	// - std::sort can be used
	// - std::unique doesn't need to copy values
	template<typename T>
	concept SortableRange =
		std::ranges::range<T> &&
		std::totally_ordered<std::ranges::range_value_t<T>> &&	// sortable
		std::copyable<std::ranges::range_value_t<T>>;			// copyable

	template<typename T>
	concept EfficientForwardRange =
		std::ranges::forward_range<T> &&
		std::ranges::sized_range<T>;

	template<typename T>
	concept MovableElementRange =
		std::ranges::range<T> &&
		std::movable<std::ranges::range_value_t<T>>;

	template<typename R, typename Out>
	concept FilterableRange =
		std::ranges::forward_range<R> &&	// Forward iteratable (it++)
		std::equality_comparable<std::ranges::range_value_t<R>> &&	// Support operator==
		std::output_iterator<Out, std::ranges::range_value_t<R>>;	// Support output iterator

	// ---------------------------------------------------------------------------
	template<typename T>
	concept RandomAccessRange =
		std::ranges::random_access_range<T>;

	template<typename T>
	concept IntegralArgument =
		std::integral<T>;

	// ---------------------------------------------------------------------------
	template<typename T>
	concept ThreeWayComparable =
		std::three_way_comparable<T>;

	template<typename T>
	concept DefaultInitializable =
		std::default_initializable<T>;

	// ---------------------------------------------------------------------------
	template<typename T>
	concept ConvertibleToSizeT =
		std::convertible_to<T, size_t>;

	template<typename T>
	concept SafeRandomAccessContainer =
		RandomAccessRange<T> &&				// std::ranges::random_access_range<T>
		!std::ranges::borrowed_range<T>;	// Check if it's NOT borrowed_range

	// ---------------------------------------------------------------------------
	// Ensure that the range is bidirectionally scannable.
	template<typename T>
	concept BidirectionalRange =
		std::ranges::bidirectional_range<T>;

	// Ensure that a function taking DataEntry as an argument and returning bool is callable.
	template<typename F>
	concept DataEntryPredicate =
		std::invocable<F, const DataEntry&>&&
		std::convertible_to<std::invoke_result_t<F, const DataEntry&>, bool>;

	// ========================================================================
	// C++17 implementation
	class Cpp17Processor : public IProcessor
	{
	public:
		std::string get_style() const override { return "C++17 (Iterator-based Algorithms)"; }

		// --------------------------------------------------------------------------
		double process_and_sum(const std::vector<DataEntry>& data, double threshold) const override
		{
			double sum = 0.0;

			// 1. Filtering: Requires an explicit loop or std::copy_if into a temporary container (less efficient).
			// Here, we use a loop for simplicity and direct comparison to C++20 ranges.
			for (const auto& entry : data)
			{
				if (entry.value > threshold)
				{
					// 2. Accumulation: Manual summation
					sum += entry.value;
				}
			}
			// If complex transformations were needed, multiple steps/loops would be required.
			return sum;
		}

		// --------------------------------------------------------------------------
		double process_drop_reverse_sum(std::vector<DataEntry> data) const override
		{
			// 1. Sort for calling std::unique
			std::sort(data.begin(), data.end());

			// 2. Drop the first 2 elements
			if (data.size() >= 2)
			{
				data.erase(data.begin(), data.begin() + 2);
			}
			else
			{
				data.clear();
			}
			// 3. Reverse sum
			double sum = 0.0;
			for (auto it = data.rbegin(); it != data.rend(); ++it)
			{
				sum += it->value;
			}
			return sum;
		}

		// --------------------------------------------------------------------------
		size_t process_and_check_size(std::vector<DataEntry> data) const override
		{
			// Size check
			size_t size = data.size();

			// Move data (allocate destination)
			std::vector<DataEntry> moved_data;
			moved_data.reserve(size);

			// Move data (call std::move)
			std::move(data.begin(), data.end(), std::back_inserter(moved_data));

			return size / 2;
		}

		size_t filter_and_output(const std::vector<DataEntry>& data, const std::string& tag_filter) const override
		{
			std::vector<DataEntry> result;

			std::copy_if(data.begin(), data.end(), std::back_inserter(result),
				[&tag_filter](const DataEntry& e)
				{
					return e.tag == tag_filter;
				});

			return result.size();
		}

		// --------------------------------------------------------------------------
		long long process_and_find_index(const std::vector<DataEntry>& data, int target_id) const override
		{
			// 1. std::find_if
			auto it = std::find_if(data.begin(), data.end(), [target_id](const DataEntry& e)
				{
					return e.id == target_id;
				});

			// 2. Return if not found
			if (it == data.end())
			{
				return -1;
			}

			// 3. std::distance
			// The iterator of std::vector is random access iterator, so std::distance() is quick O(1).
			return std::distance(data.begin(), it);
		}

		// --------------------------------------------------------------------------
		size_t process_and_concat(const std::vector<DataEntry>& data, size_t min_count) const override
		{
			// 1. Check the size
			if (data.size() < min_count)
			{
				throw std::out_of_range("Range size is below the required minimum count.");
			}

			// 2. Concat (copy the original range twice)
			std::vector<DataEntry> result_concat;
			size_t original_size = data.size();
			result_concat.reserve(original_size * 2);

			// 1st
			result_concat.insert(result_concat.end(), data.begin(), data.end());
			// 2nd
			result_concat.insert(result_concat.end(), data.begin(), data.end());

			// 3. Return result
			return result_concat.size();
		}

		// --------------------------------------------------------------------------
		size_t process_and_slice(const std::vector<DataEntry>& data, double max_elements_double) const override
		{
			// 1. Check the size
			size_t size = data.size();
			if (size < 3)
			{
				return 0;
			}

			// 2. Get the iterator of the size that the first and last elements are skipped.
			auto begin = data.begin() + 1;	// Skip the first element
			auto end = data.end() - 1;		// Skip the last element

			// 3. Check the new size
			size_t current_size = std::distance(begin, end);

			// 4. Limit check
			size_t max_limit = static_cast<size_t>(max_elements_double);
			if (current_size > max_limit)
			{
				return max_limit;
			}

			return current_size;
		}

		// --------------------------------------------------------------------------
		double process_bidirectional_stride_sum(const std::vector<DataEntry>& data) const override
		{
			// C++17 style
			double sum = 0.0;

			for (auto i = 0; i < data.size(); i+=2)
			{
				sum += data[i].value;
			}
			return sum;
		}

	};

	// ========================================================================
	// C++20 implementation
	class Cpp20Processor : public IProcessor
	{
	public:
		std::string get_style() const override { return "C++20 (Iterator-based Algorithms)"; }

		// --------------------------------------------------------------------------
		double process_and_sum(const std::vector<DataEntry>& data, double threshold) const override
		{
			// C++20 Ranges: Use a single pipeline for filtering and extracting the value.
			auto filtered_view = data
				| std::views::filter([threshold](const DataEntry& e) // filtering
					{
						return e.value > threshold;
					})
				| std::views::transform([](const DataEntry& e)		// processing (just extracting for this time)
					{
						// Extract only the 'value' for summation
						return e.value;
					});
			// 2. Accumulation: Use std::accumulate on the generated view (Requires <numeric>).
			// Note: std::ranges::fold/reduce is also available in C++20/23.
			double sum = std::accumulate(filtered_view.begin(), filtered_view.end(), 0.0);

			return sum;
		}

		// Example of a function constrained by the 'NumericRange' concept (not used by the interface, but shows C++20 usage)
		// This function will only compile if T is a range of arithmetic types.
		template<NumericRange T>
		auto compute_average(const T& range) const
		{
			// Use auto for the return type (C++14 feature, but common in modern C++)
			if (std::ranges::empty(range)) return 0.0;
			return std::accumulate(std::ranges::begin(range), std::ranges::end(range), 0.0) / std::ranges::size(range);
		}



		// --------------------------------------------------------------------------
		double process_drop_reverse_sum(std::vector<DataEntry> data) const override
		{
			// 1. Sort
			std::ranges::sort(data);

			// 2. Ranges pipeline
			// - drop
			// - reverse
			// - transform
			auto processed_view = data
				| std::views::drop(2)							// Skip the first 2 elements
				| std::views::reverse							// Reversing
				| std::views::transform([](const DataEntry& e)	// Extract value
					{
						return e.value;
					});

			// 3. Accumulate
			return std::accumulate(processed_view.begin(), processed_view.end(), 0.0);
		}

		// --------------------------------------------------------------------------
		template<SortableRange T>
		size_t count_unique_elements(const T& range) const
		{
			using ElementType = std::ranges::range_value_t<T>;

			// 0. Make a vector that std::ranges::sort can handle
			std::vector<ElementType> sorted_data(std::ranges::begin(range), std::ranges::end(range));

			// 1. Sort the range first (required for unique to work correctly)
			std::sort(sorted_data.begin(), sorted_data.end());

			// 2. Use std::ranges::unique to move unique elements to the front.
			// This returns a sub-range (view) covering the unique elements.
			auto unique_end_result = std::ranges::unique(sorted_data);

			// 3. The distance of the resulting sub-range (from begin to unique_end) is the count.
			return std::ranges::distance(sorted_data.begin(), unique_end_result.begin());
		}

		// --------------------------------------------------------------------------
		template<EfficientForwardRange T>
		requires MovableElementRange<T>
		size_t check_and_move_elements(T& range) const
		{
			// 1. Get the size
			size_t size = std::ranges::size(range);

			// 2. Move
			std::vector<DataEntry> moved_data;
			moved_data.reserve(size);
			std::ranges::move(range, std::back_inserter(moved_data));
			return size / 2;
		}

		size_t process_and_check_size(std::vector<DataEntry> data) const override
		{
			return check_and_move_elements(data);
		}

		// --------------------------------------------------------------------------
		template<typename R, typename Container>
		requires FilterableRange<R, typename Container::iterator> &&	// Check iterator of input range and output container
		std::ranges::range<Container>									// Check if the Container is range
		auto filter_to_container(const R& input_range, const std::string& filter_tag) const
		{
			using ElementType = std::ranges::range_value_t<R>;

			// 1. Filtering using range pipeline
			auto filtered_view = input_range
				| std::views::filter([&filter_tag](const ElementType& e)
					{
						return e.tag == filter_tag;
					});
			// 2. Copy the filtered elements to a new container
			Container result;
			std::ranges::copy(filtered_view, std::back_inserter(result));

			return result;
		}

		size_t filter_and_output(const std::vector<DataEntry>& data, const std::string& tag_filter) const override
		{
			// Call the template func with concccts fron the virtual function
			auto result_vec = filter_to_container<const std::vector<DataEntry>&, std::vector<DataEntry>>(data, tag_filter);
			return result_vec.size();
		}

		// --------------------------------------------------------------------------
		template<typename R>
		requires RandomAccessRange<R> &&						// The range must be able to random access
		std::same_as<std::ranges::range_value_t<R>, DataEntry>	// The element must be DataEntry
		auto find_index(const R& input_range, IntegralArgument auto target_id) const -> long long
		{
			// 1. Get the iterator using std::ranges::find_if()
			auto it = std::ranges::find_if(input_range, [target_id](const DataEntry& e)
				{
					return e.id == target_id;
				});

			// Return if not found
			if (it == std::ranges::end(input_range))
			{
				return -1;
			}

			// 3. Random access range will be able to run std::ranges:distance() in O(1).
			return std::ranges::distance(std::ranges::begin(input_range), it);
		}

		long long process_and_find_index(const std::vector<DataEntry>& data, const int target_id) const override
		{
			return find_index(data, target_id);
		}


		// --------------------------------------------------------------------------
		template<typename R>
		requires RandomAccessRange<R> &&
				 ThreeWayComparable<std::ranges::range_value_t<R>> &&	// The element should support <=>
				 DefaultInitializable<std::ranges::range_value_t<R>>	// The element should have default constructor without parameter
		size_t concatenate_and_count(const R& input_range, size_t required_count) const
		{
			// 1. Check the size
			if (std::ranges::size(input_range) < required_count)
			{
				throw std::out_of_range("Range size is below the required minimum count.");
			}

			// 2. Concat range (C++20: using std::ranges::concat() with multiple ranges)
			// Due to a legacy from Range-v3, std::views::concat() has been deprecated in C++23.
			// It mimics a view that can stably process two consecutive ranges in C++20.

			// Copy the range and create a new vector
			std::vector<DataEntry> duplicate_data(std::ranges::begin(input_range), std::ranges::end(input_range));

			// Process as if the replicated data and the original data were combined
			// In practice, the most robust approach is to copy it twice into a temporary container and return its size.
			std::vector<DataEntry> result_concat;
			result_concat.reserve(std::ranges::size(input_range) * 2);
			std::ranges::copy(input_range, std::back_inserter(result_concat));
			std::ranges::copy(duplicate_data, std::back_inserter(result_concat));

			// 3. Return the size
			return result_concat.size();
		}

		size_t process_and_concat(const std::vector<DataEntry>& data, size_t min_count) const override
		{
			return concatenate_and_count(data, min_count);
		}

		// --------------------------------------------------------------------------
		template<typename R>
		requires SafeRandomAccessContainer<R>
		size_t slice_and_count(const R& input_range, ConvertibleToSizeT auto max_elements_double) const
		{
			// 1. Get the start/end slice pos
			size_t size = std::ranges::size(input_range);
			if (size < 3) return 0;	// at least 3 elements are required for slicing front, middle and back

			// 2. C++20 ranges: Skip the first and last elements
			auto sliced_view = input_range
				| std::views::drop(1)			// Skip the first element
				| std::views::take(size - 2);	// Skip the one from the last (size - 1 - 1)

			// 3. Check the size
			size_t max_limit = static_cast<size_t>(max_elements_double);
			size_t current_size = std::ranges::size(sliced_view);

			if (current_size > max_limit)
			{
				return max_limit;	// Return max if bigger the max limit
			}

			return current_size;
		}

		size_t process_and_slice(const std::vector<DataEntry>& data, double max_elements_double) const override
		{
			return slice_and_count(data, max_elements_double);
		}

		// --------------------------------------------------------------------------
		// Composite Constraints and Custom View Imitation
		template <typename R>
		requires BidirectionalRange<R> &&
		std::same_as<std::ranges::range_value_t<R>, DataEntry>
		double stride_sum(const R& input_range, int stride_step) const
		{
			// 1. Thinning elements in range pipelines (mimicking std::views::stride)
			// Since std::views::stride was introduced in C++23, it must be implemented manually in C++20.
			double sum = 0.0;
			size_t count = 0;

			// Manually advance the iterator 
			// (Since it is a BidirectionalRange, this is inefficient but scanning is possible)
			for (auto it = std::ranges::begin(input_range); it != std::ranges::end(input_range);)
			{
				if (count % stride_step == 0)
				{
					sum += it->value;
				}

				// Next element
				if (++count < std::ranges::size(input_range))
				{
					++it; // Increment count first, then next it
				}
				else
				{
					break;
				}
			}
			return sum;
		}

		// Final demo of Concepts and requires (accepting a filter function)
		template<typename R, typename Predicate>
		requires BidirectionalRange<R> && DataEntryPredicate<Predicate>
		size_t count_filtered_bidirectional(const R& input_range, Predicate pred) const
		{
			// Iterate over the BidirectionalRange R in reverse order 
			// and count the number of elements satisfying the Predicate.
			// BidirectionalRange supports reverse_iterator, 
			// enabling efficient reverse traversal.
			auto reversed_view = input_range | std::views::reverse;
			return std::ranges::distance(reversed_view | std::views::filter(pred));
		}

		double process_bidirectional_stride_sum(const std::vector<DataEntry>& data) const override
		{
			return stride_sum(data, 2); // Skip 2 (0, 2nd, 4rth...)
		}
	};
}

