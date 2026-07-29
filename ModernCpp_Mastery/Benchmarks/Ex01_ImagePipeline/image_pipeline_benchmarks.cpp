#include <benchmark/benchmark.h>
#include "image_filter.h"
#include "image_pipeline.h"
#include "threshold_filter.h"
#include "grayscale_filter.h"
#include "sepia_filter.h"
#include "blur_filter.h"
#include "edge_filter.h"

using namespace Ex01_ImagePipeline;

template<Strategy S>
static void BM_ThresholdFilter(benchmark::State& state)
{
	uint16_t w = 4096;
	uint16_t h = 4096;
	Image<GrayPixel> srcImage(w, h);
	Image<GrayPixel> dstImage(w, h);

	// Draw gradient pattern
	for (uint16_t y = 0; y < h; ++y)
	{
		for (uint16_t x = 0; x < w; ++x)
		{
			float t = float(x + y) / float((w - 1) + (h - 1));
			uint8_t v = static_cast<uint8_t>(t * 255.0f);

			srcImage.at(x, y).intensity = v;
		}
	}
	
	// Create filter
	ThresholdFilter<GrayPixel, S> filter(200);

	// Create pipeline
	ImagePipeline pipeline(filter);

	for (auto _ : state)
	{
		pipeline.apply(srcImage, dstImage);
		// Force the compiler to believe that the memory of dstImage is actually being read.
		benchmark::DoNotOptimize(dstImage);
	}
	benchmark::ClobberMemory();
	// Bytes read + written per iteration
	int64_t totalBytes = static_cast<int64_t>(w) * h * (sizeof(GrayPixel) + sizeof(GrayPixel));
	state.SetBytesProcessed(state.iterations() * totalBytes);
	// Total pixels processed per iteration
	state.SetItemsProcessed(state.iterations() * static_cast<int64_t>(w) * h);
}

template<Strategy S>
static void BM_GrayScaleFilter(benchmark::State& state)
{
	uint16_t w = 4096;
	uint16_t h = 4096;
	Image<RgbaPixel> srcImage(w, h);
	Image<GrayPixel> dstImage(w, h);

	const float denom = static_cast<float>((w - 1) + (h - 1));

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float t = (x + y) / denom;

			uint8_t r = static_cast<uint8_t>(255 * t);
			uint8_t g = static_cast<uint8_t>(255 * (1.0f - t));
			uint8_t b = static_cast<uint8_t>(255 * (0.5f + 0.5f * t));

			srcImage.at(x, y) = RgbaPixel{ r, g, b, 255 };
		}
	}

	// Create filter
	GrayScaleFilter<RgbaPixel, GrayPixel, S> filter;

	// Create pipeline
	ImagePipeline pipeline(filter);

	for (auto _ : state)
	{
		pipeline.apply(srcImage, dstImage);
		// Force the compiler to believe that the memory of dstImage is actually being read.
		benchmark::DoNotOptimize(dstImage);
	}
	benchmark::ClobberMemory();
	// Bytes read + written per iteration
	int64_t totalBytes = static_cast<int64_t>(w) * h * (sizeof(RgbaPixel) + sizeof(GrayPixel));
	state.SetBytesProcessed(state.iterations() * totalBytes);
	// Total pixels processed per iteration
	state.SetItemsProcessed(state.iterations() * static_cast<int64_t>(w) * h);
}

template<Strategy S>
static void BM_SepiaFilter(benchmark::State& state)
{
	uint16_t w = 4096;
	uint16_t h = 4096;
	Image<GrayPixel> srcImage(w, h);
	Image<RgbaPixel> dstImage(w, h);

	// Draw gradient pattern
	for (uint16_t y = 0; y < h; ++y)
	{
		for (uint16_t x = 0; x < w; ++x)
		{
			float t = float(x + y) / float((w - 1) + (h - 1));
			uint8_t v = static_cast<uint8_t>(t * 255.0f);

			srcImage.at(x, y).intensity = v;
		}
	}

	// Create filter
	SepiaFilter<GrayPixel, RgbaPixel, S> filter;

	// Create pipeline
	ImagePipeline pipeline(filter);

	for (auto _ : state)
	{
		pipeline.apply(srcImage, dstImage);
		// Force the compiler to believe that the memory of dstImage is actually being read.
		benchmark::DoNotOptimize(dstImage);
	}
	benchmark::ClobberMemory();
	// Bytes read + written per iteration
	int64_t totalBytes = static_cast<int64_t>(w) * h * (sizeof(GrayPixel) + sizeof(RgbaPixel));
	state.SetBytesProcessed(state.iterations() * totalBytes);
	// Total pixels processed per iteration
	state.SetItemsProcessed(state.iterations() * static_cast<int64_t>(w) * h);
}

template<Strategy S>
static void BM_BlurFilter(benchmark::State& state)
{
	uint16_t w = 4096;
	uint16_t h = 4096;
	Image<GrayPixel> srcImage(w, h);
	Image<GrayPixel> dstImage(w, h);

	// Draw gradient pattern
	for (uint16_t y = 0; y < h; ++y)
	{
		for (uint16_t x = 0; x < w; ++x)
		{
			float t = float(x + y) / float((w - 1) + (h - 1));
			uint8_t v = static_cast<uint8_t>(t * 255.0f);

			srcImage.at(x, y).intensity = v;
		}
	}

	// Create filter
	BlurFilter<GrayPixel, S> filter;

	// Create pipeline
	ImagePipeline pipeline(filter);

	for (auto _ : state)
	{
		pipeline.apply(srcImage, dstImage);
		// Force the compiler to believe that the memory of dstImage is actually being read.
		benchmark::DoNotOptimize(dstImage);
	}
	benchmark::ClobberMemory();
	// Bytes read + written per iteration
	int64_t totalBytes = static_cast<int64_t>(w) * h * (sizeof(GrayPixel) + sizeof(GrayPixel));
	state.SetBytesProcessed(state.iterations() * totalBytes);
	// Total pixels processed per iteration
	state.SetItemsProcessed(state.iterations() * static_cast<int64_t>(w) * h);
}

template<Strategy S>
static void BM_EdgeFilter(benchmark::State& state)
{
	uint16_t w = 4096;
	uint16_t h = 4096;
	Image<GrayPixel> srcImage(w, h);
	Image<GrayPixel> dstImage(w, h);

	// Draw gradient pattern
	for (uint16_t y = 0; y < h; ++y)
	{
		for (uint16_t x = 0; x < w; ++x)
		{
			float t = float(x + y) / float((w - 1) + (h - 1));
			uint8_t v = static_cast<uint8_t>(t * 255.0f);

			srcImage.at(x, y).intensity = v;
		}
	}

	// Create filter
	EdgeFilter<GrayPixel, S> filter;

	// Create pipeline
	ImagePipeline pipeline(filter);

	for (auto _ : state)
	{
		pipeline.apply(srcImage, dstImage);

		// Force the compiler to believe that the memory of dstImage is actually being read.
		benchmark::DoNotOptimize(dstImage);
	}
	benchmark::ClobberMemory();
	// Bytes read + written per iteration
	int64_t totalBytes = static_cast<int64_t>(w) * h * (sizeof(GrayPixel) + sizeof(GrayPixel));
	state.SetBytesProcessed(state.iterations() * totalBytes);

	// Total pixels processed per iteration
	state.SetItemsProcessed(state.iterations() * static_cast<int64_t>(w) * h);
}

BENCHMARK_TEMPLATE(BM_BlurFilter, Strategy::Naive)->UseRealTime();
BENCHMARK_TEMPLATE(BM_BlurFilter, Strategy::Simd)->UseRealTime();
BENCHMARK_TEMPLATE(BM_EdgeFilter, Strategy::Naive)->UseRealTime();
BENCHMARK_TEMPLATE(BM_EdgeFilter, Strategy::Simd)->UseRealTime();
BENCHMARK_TEMPLATE(BM_GrayScaleFilter, Strategy::Naive)->UseRealTime();
BENCHMARK_TEMPLATE(BM_GrayScaleFilter, Strategy::Simd)->UseRealTime();
BENCHMARK_TEMPLATE(BM_SepiaFilter, Strategy::Naive)->UseRealTime();
BENCHMARK_TEMPLATE(BM_SepiaFilter, Strategy::Simd1)->UseRealTime();
BENCHMARK_TEMPLATE(BM_SepiaFilter, Strategy::Simd2)->UseRealTime();
BENCHMARK_TEMPLATE(BM_ThresholdFilter, Strategy::Naive)->UseRealTime();
BENCHMARK_TEMPLATE(BM_ThresholdFilter, Strategy::Simd)->UseRealTime();


BENCHMARK_MAIN();
