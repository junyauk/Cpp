#include <filesystem>
#include "gtest/gtest.h"
#include "image_pipeline.h"
#include "grayscale_filter.h"
#include "blur_filter.h"
#include "edge_filter.h"
#include "sepia_filter.h"
#include "threshold_filter.h"
#include "blur_filter.h"
#include "edge_filter.h"
#include <sstream>

using namespace Ex01_ImagePipeline;

namespace Ex01_ImagePipelineTests
{
	static std::filesystem::path getTestSrcDirectory()
	{
		std::filesystem::path src_file_path(__FILE__);

		return src_file_path.parent_path();
	}

	void drawWhiteRect(Image<RgbaPixel>& image)
	{
		uint32_t lx = image.width() / 4;
		uint32_t rx = image.width() - lx;
		uint32_t ty = image.height() / 4;
		uint32_t by = image.height() - ty;

		for (uint32_t y = 0; y < image.height(); ++y)
		{
			for (uint32_t x = 0; x < image.width(); ++x)
			{
				if ((lx < x) && (x < rx) && (ty < y) && (y < by))
				{
					image.at(x, y) = RgbaPixel{ 255, 255, 255, 255 };	// White
				}
				else
				{
					image.at(x, y) = RgbaPixel{ (uint8_t)(x & 256), 255, 255, 255 }; // shading
				}
			}
		}
	}

	TEST(ImagePipelineTests, BoundariesCheck)
	{
		// Same size ( No throwing)
		{
			uint32_t w = 100;
			uint32_t h = 100;
			Image<RgbaPixel> srcImage(w, h);
			Image<GrayPixel> dstImage(w, h);

			// Gray filter
			GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> grayScaleFilter;

			// Pipeline
			ImagePipeline pipeline(grayScaleFilter);

			EXPECT_NO_THROW(pipeline.apply(srcImage, dstImage));
		}

		// Different size
		{
			Image<RgbaPixel> srcImage(100, 50);
			Image<GrayPixel> dstImage(257, 300);	// Different size

			// Gray filter
			GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> grayScaleFilter;

			// Pipeline
			ImagePipeline pipeline(grayScaleFilter);

			EXPECT_THROW(pipeline.apply(srcImage, dstImage), std::invalid_argument);
		}
	}

	TEST(ImagePipelineTests, BlurFilters)
	{
		std::string expectedFileName = "BlurFilter_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;
		// Images
		Image<GrayPixel> srcImage(w, h);
		drawWhiteRect(srcImage);
		Image<GrayPixel> naiveImage(w, h);
		Image<GrayPixel> simdImage(w, h);

		// Filters
		BlurFilter<GrayPixel, Strategy::Naive> naiveFilter;
		BlurFilter<GrayPixel, Strategy::Simd> simdFilter;

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simdPipeline(simdFilter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simdPipeline.apply(srcImage, simdImage);
#if true
		// Assert
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<GrayPixel> expectedImage = loadFromPPM<GrayPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(expectedImage, naiveImage));
		EXPECT_TRUE(compareImages(expectedImage, simdImage));
#else
		saveAsPPM(naiveImage, expectedFileName);
#endif

	}

	TEST(ImagePipelineTests, EdgeFilters)
	{
		std::string expectedFileName = "EdgeFilter_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;
		// Images
		Image<GrayPixel> srcImage(w, h);
		drawWhiteRect(srcImage);
		Image<GrayPixel> naiveImage(w, h);
		Image<GrayPixel> simdImage(w, h);

		// Filters
		EdgeFilter<GrayPixel, Strategy::Naive> naiveFilter;
		EdgeFilter<GrayPixel, Strategy::Simd> simdFilter;

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simdPipeline(simdFilter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simdPipeline.apply(srcImage, simdImage);
#if true
		// Assert
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<GrayPixel> expectedImage = loadFromPPM<GrayPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(expectedImage, naiveImage));
		EXPECT_TRUE(compareImages(expectedImage, simdImage));
#else
		saveAsPPM(naiveImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, GrayScaleFilters)
	{
		std::string expectedFileName = "GrayScaleFilter_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;
		// Images
		Image<RgbaPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<GrayPixel> naiveImage(w, h);
		Image<GrayPixel> simdImage(w, h);

		// Filters
		GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> naiveFilter;
		GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Simd> simdFilter;

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simdPipeline(simdFilter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simdPipeline.apply(srcImage, simdImage);
#if true
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<GrayPixel> expectedImage = loadFromPPM<GrayPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(expectedImage, naiveImage));
		EXPECT_TRUE(compareImages(expectedImage, simdImage));
#else
		saveAsPPM(naiveImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, SepiaFilters)
	{
		std::string expectedFileName = "SepiaFilter_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;
		// Images
		Image<GrayPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<RgbaPixel> naiveImage(w, h);
		Image<RgbaPixel> simd1Image(w, h);
		Image<RgbaPixel> simd2Image(w, h);

		// Filters
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Naive> naiveFilter;
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Simd1> simd1Filter;
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Simd2> simd2Filter;

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simd1Pipeline(simd1Filter);
		ImagePipeline simd2Pipeline(simd2Filter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simd1Pipeline.apply(srcImage, simd1Image);
		simd2Pipeline.apply(srcImage, simd2Image);
#if true
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<RgbaPixel> expectedImage = loadFromPPM<RgbaPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(expectedImage, naiveImage));
		EXPECT_TRUE(compareImages(expectedImage, simd1Image));
		EXPECT_TRUE(compareImages(expectedImage, simd2Image));
#else
		saveAsPPM(naiveImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, ThresholdFilters)
	{
		uint8_t threshold = 135;
		// Images
		uint32_t w = 100;
		uint32_t h = 100;
		Image<GrayPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<GrayPixel> naiveImage(w, h);
		Image<GrayPixel> simdImage(w, h);

		// Filters
		ThresholdFilter<GrayPixel, Strategy::Naive> naiveFilter(threshold);
		ThresholdFilter<GrayPixel, Strategy::Simd> simdFilter(threshold);

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simdPipeline(simdFilter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simdPipeline.apply(srcImage, simdImage);

		// Simply check the intensity values
		for (uint32_t y = 0; y < h; ++y)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				uint8_t expected = srcImage.at(x, y).intensity >= threshold ? 255 : 0;
				EXPECT_EQ(expected, naiveImage.at(x, y).intensity);
				EXPECT_EQ(expected, simdImage.at(x, y).intensity);
			}
		}
	}

	TEST(ImagePipelineTests, DoubleFilters)
	{
		std::string expectedFileName = "DoubleFilters_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;
		// Images
		Image<RgbaPixel> srcImage(w, h);
		drawWhiteRect(srcImage);
		Image<GrayPixel> dstImage(w, h);

		// Gray filter
		GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> grayScaleFilter;

		// Blur filter
		BlurFilter<GrayPixel, Strategy::Naive> blurFilter;

		// Pipeline
		ImagePipeline pipeline(grayScaleFilter, blurFilter);

		pipeline.apply(srcImage, dstImage);
#if true
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<GrayPixel> expectedImage = loadFromPPM<GrayPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(dstImage, expectedImage));
#else
		saveAsPPM(dstImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, TripleFilters)
	{
		std::string expectedFileName = "TripleFilters_Naive.ppm";

		uint32_t w = 100;
		uint32_t h = 100;

		// Images
		Image<RgbaPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<GrayPixel> dstImage(w, h);

		// Gray filter
		GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> grayScaleFilter;

		// Threshold filter
		ThresholdFilter<GrayPixel, Strategy::Naive> thresholdFilter(135);

		// Blur filter
		BlurFilter<GrayPixel, Strategy::Naive> blurFilter;

		// Pipeline
		ImagePipeline pipeline(grayScaleFilter, thresholdFilter, blurFilter);

		pipeline.apply(srcImage, dstImage);
#if true
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<GrayPixel> expectedImage = loadFromPPM<GrayPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(dstImage, expectedImage));
#else
		saveAsPPM(dstImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, RgbaPixelOut)
	{
		std::string expectedFileName = "RgbaPixelOut_Naive.ppm";

		// Images
		uint32_t w = 100;
		uint32_t h = 100;
		Image<RgbaPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<RgbaPixel> dstImage(w, h);

		// Gray filter
		GrayScaleFilter<RgbaPixel, GrayPixel, Strategy::Naive> grayScaleFilter;

		// Sepia filter
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Naive> sepiaFilter;

		// Pipeline
		ImagePipeline pipeline(grayScaleFilter, sepiaFilter);

		pipeline.apply(srcImage, dstImage);
#if true
		std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		Image<RgbaPixel> expectedImage = loadFromPPM<RgbaPixel>(expectedFilePath);
		EXPECT_TRUE(compareImages(dstImage, expectedImage));
#else
		saveAsPPM(dstImage, expectedFileName);
#endif
	}

	TEST(ImagePipelineTests, Debug)
	{
		uint32_t w = 130;
		uint32_t h = 100;
		// Images
		Image<GrayPixel> srcImage(w, h);
		drawDiagonalGradient(srcImage);
		Image<RgbaPixel> naiveImage(w, h);
		Image<RgbaPixel> simd1Image(w, h);
		Image<RgbaPixel> simd2Image(w, h);

		// Filters
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Naive> naiveFilter;
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Simd1> simd1Filter;
		SepiaFilter<GrayPixel, RgbaPixel, Strategy::Simd2> simd2Filter;

		// Pipelines
		ImagePipeline naivePipeline(naiveFilter);
		ImagePipeline simd1Pipeline(simd1Filter);
		ImagePipeline simd2Pipeline(simd2Filter);

		// Act
		naivePipeline.apply(srcImage, naiveImage);
		simd1Pipeline.apply(srcImage, simd1Image);
		simd2Pipeline.apply(srcImage, simd2Image);

		std::string expectedFileName = "simd1Image.ppm";
		ASSERT_TRUE(compareImages(naiveImage, simd1Image));
		ASSERT_TRUE(compareImages(naiveImage, simd2Image));
	}


}
