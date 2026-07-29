#pragma once
#include "pixel.h"
#include "image.h"
#include "image_filter.h"
#include "thread_pool.h"
#include "slice_metadata.h"
#include <tuple>
#include <concepts>
#include <stdexcept>
#include <format>
#include <mdspan>
#include <barrier>

namespace Ex01_ImagePipeline
{
	// 1. Base case: An empty pack or a single filter is always valid by default
	template<typename... Ts>
	struct is_valid_chain : std::true_type {};
	// 2. Recursive case: Match at least TWO adjacent filters
	template<typename CurrentFilter, typename NextFilter, typename... Rest>
	struct is_valid_chain<CurrentFilter, NextFilter, Rest...>
	{
		// Check if the current output connects to the next input
		static constexpr bool current_pair_matches =
			std::is_same_v<typename CurrentFilter::dst_pixel_type, typename NextFilter::src_pixel_type>;

		// The whole chain is valid if this pair matches And the rest of the chain matches recursively
		static constexpr bool value = current_pair_matches & is_valid_chain<NextFilter, Rest...>::value;
	};

	// 1. Base case: 0 or 1 filter remaining means 0 intermediate buffers needed.
	// (e.g., if we only have 1 filter, it needs from src and writes directly to dst.
	template<typename... Filters>
	struct intermediate_buffers
	{
		using type = std::tuple<>;
	};
	// 2. Recursive case: Match at least Two adjacent filters in the chain.
	template<typename CurrentFilter, typename NextFilter, typename... Rest>
	struct intermediate_buffers<CurrentFilter, NextFilter, Rest...>
	{
		// A. Recursively find the buffer types needed for the rest of the chain.
		using rest_tuple = typename intermediate_buffers<NextFilter, Rest...>::type;
		// B. Prepend our current filter's destination image type to the front of that tuple.
		// Use std::tuple_cat inside decltype to merge the types at compile time.
		using type = decltype(std::tuple_cat(
			std::declval<std::tuple<Image<typename CurrentFilter::dst_pixel_type>>>(),
			std::declval<rest_tuple>()
		));
	};

	// Helper function to unpack the tuple indices and construct each element
	template<typename Tuple, std::size_t... Is>
	Tuple create_temp_buffers_impl(uint32_t width, uint32_t height, std::index_sequence<Is...>)
	{
		// This expands at compile-time to construct each individual image with (width, height)
		return Tuple{ typename std::tuple_element_t<Is, Tuple>{width, height}... };
	}
	template<typename Tuple>
	Tuple create_temp_buffers(uint32_t width, uint32_t height)
	{
		return create_temp_buffers_impl<Tuple>(
			width, height,
			std::make_index_sequence<std::tuple_size_v<Tuple>>{}
		);
	}

	template<typename... Filters>
	requires is_valid_chain<Filters...>::value	// Checking filter chain as requires
	class ImagePipeline
	{
	private:
		std::tuple<Filters...> m_filters;	// All filters
		using FirstFilterType = std::tuple_element_t<0, decltype(m_filters)>;
		using LastFilterType = std::tuple_element_t < (sizeof...(Filters) - 1), decltype(m_filters)>;
		using TempBuffersTuple = typename intermediate_buffers<Filters...>::type;

		static const size_t NumThreads = 1;
		ThreadPool m_pool = ThreadPool(NumThreads);
		
		std::vector<SliceMetadata> split_ranges(uint32_t width, uint32_t height, uint32_t n)
		{
			std::vector<SliceMetadata> ranges;
			ranges.reserve(n);
			auto q = height / n;
			auto r = height % n;

			uint32_t y = 0;	// startY
			for (uint32_t i = 0; i < n; ++i)
			{
				uint32_t h = (i < r ? q + 1 : q);	// height
				ranges.emplace_back(y, h, width, height);	// A set of startY and height
				y += h;	// Next startY
			}
			return ranges;
		}

	public:

		ImagePipeline(Filters... rest) :m_filters(rest...)
		{
			// Checking filter chain As static assert
			// static_assert(is_valid_chain<Filters...>::value, "Pipeline contains incompatible filter connections!");
		}

		template<size_t Index, typename ImageTuple>
		void process_step(ImageTuple& images,
						   SliceMetadata slice, 
						   std::barrier<>& barrier)
		{
			auto& filter = std::get<Index>(m_filters);
			auto& src = std::get<Index>(images);
			auto& dst = std::get<Index+1>(images);

			// Apply filter with target area
			filter.apply(src, dst, slice);

			if constexpr (Index != (sizeof...(Filters) - 1))
			{
				// This is not the final filter
				// Wait for other tasks before procssing the next filter
				barrier.arrive_and_wait();
				// Go next filter
				this->process_step<Index + 1>(images, slice, barrier);
			}
		}

		template<typename SrcPixel, typename DstPixel>
		requires std::same_as<SrcPixel, typename FirstFilterType::src_pixel_type> &&
				 std::same_as<DstPixel, typename LastFilterType::dst_pixel_type>
		void apply(const Image<SrcPixel>& src, Image<DstPixel>& dst)
		{
			if (src.width() != dst.width() || src.height() != dst.height())
			{
				throw std::invalid_argument(
					std::format("Source size ({}x{}) does not match Destination size ({}x{})",
						src.width(), src.height(),
						dst.width(), dst.height()));
			}

			// Create temp images (they have appropriate PixelType according to each filter)
			TempBuffersTuple tmp_images = create_temp_buffers<TempBuffersTuple>(src.width(), src.height());
			// Concatenating src + tmp_images + dst to make a single tuple
			auto all_images = std::apply([&](auto&... temps)
				{
					return std::forward_as_tuple(src, temps..., dst);
				},
				tmp_images);

			std::barrier barrier(NumThreads);

			// Create ranges
			std::vector<SliceMetadata> slices = split_ranges(src.width(), src.height(), NumThreads);

			std::vector<std::future<void>> futures;
			futures.reserve(NumThreads);

			for (SliceMetadata& slice : slices)
			{
				futures.push_back(m_pool.enqueue([this, all_images, slice, &barrier]()
							{
								this->process_step<0>(all_images, slice, barrier);
							})
				);
			}

			// To make sure all tasks have already finished before exiting
			for (auto& f : futures)
			{
				f.get();
			}
		}
	};



}
