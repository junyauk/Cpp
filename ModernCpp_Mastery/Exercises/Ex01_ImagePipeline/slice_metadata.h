#pragma once
#include <mdspan>

namespace Ex01_ImagePipeline
{
	struct SliceMetadata
	{
		uint32_t startY;
		uint32_t height;
		uint32_t globalWidth;
		uint32_t globalHeight;
	};
}
