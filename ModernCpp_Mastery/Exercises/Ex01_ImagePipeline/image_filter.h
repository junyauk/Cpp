#pragma once
#include <cmath>
#include "image.h"
#include "pixel.h"
#include "slice_metadata.h"

namespace Ex01_ImagePipeline
{
	enum Strategy
	{
		Naive,
		Simd,
		Simd1,
		Simd2,
	};

	template<PixelType SrcPixel, PixelType DstPixel>
	class IImageFilter
	{
	public:
		virtual ~IImageFilter() = default;
		virtual void apply(const Image<SrcPixel>& src, Image<DstPixel>& dst) = 0;
		virtual void apply(const Image<SrcPixel>& src, Image<DstPixel>& dst, const SliceMetadata slice) = 0;
	};
}
