#pragma once
#include <cstdint>
#include <concepts>
#include <type_traits>

namespace Ex01_ImagePipeline
{
	struct GrayPixel
	{
		uint8_t intensity; // Is there any other better name?
	};

	struct RgbaPixel
	{
		uint8_t r;	// Red
		uint8_t g;	// Green
		uint8_t b;	// Blue
		uint8_t a;	// Alpha
	};

	template<typename T>
	concept PixelType = 
		std::is_trivial_v<T> &&				// POD (Fixed sized Plain Old Data)
		std::is_standard_layout_v<T> &&		// Memory is contiquous
		std::is_trivially_copyable_v<T> &&	// std::memcpy can be used
		((sizeof(T) == 1) || (sizeof(T) == 4));	// Gray or RGBA

	template<typename T>
	concept RgbLikePixel = requires(T p)
	{
		{ p.r } -> std::convertible_to<uint8_t>;
		{ p.g } -> std::convertible_to<uint8_t>;
		{ p.b } -> std::convertible_to<uint8_t>;
	};
}
