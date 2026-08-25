#include "gtest/gtest.h"
#include "classicbarrierpipeline.h"
#include "modernsyncbarrierpipeline.h"
#include <random>

using namespace Ex03_SyncBarrier_Pipeline;

namespace Ex03_SyncBarrier_PipelineTests
{
	template<typename T>
	class BarrierPipelineTests : public ::testing::Test {};
	using BarrierPipelineImplimentations = ::testing::Types<ClassicBarrierPipeline, ModernSyncBarrierPipeline>;
	TYPED_TEST_CASE(BarrierPipelineTests, BarrierPipelineImplimentations);


	TYPED_TEST(BarrierPipelineTests, BasicTest)
	{
		PipelineMetrics<std::chrono::nanoseconds> metrics;
		FrameBatch fb;
		uint32_t bufferSize = 10;
		fb.pixelData.resize(bufferSize);

		std::vector<float> values =	{ 0.0f, 0.25f, 0.5f, 0.75f, 1.0f };
		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			fb.pixelData[i] = values[i % values.size()];
		}
		std::vector<double> expected =
		{
			0.391699642,
			0.836238325,
			0.967158675,
			0.999959886,
			1.00000000,
			0.391699642,
			0.836238325,
			0.967158675,
			0.999959886,
			1.00000000
		};

		TypeParam pipeline;
		pipeline.Process(fb, &metrics);
		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			double e = expected[i];
			double a = fb.pixelData[i];
			EXPECT_NEAR(e, a, 1e-4f);
		}
	}

	TYPED_TEST(BarrierPipelineTests, BoundaryTest)
	{
		PipelineMetrics<std::chrono::nanoseconds> metrics;
		FrameBatch fb;
		uint32_t bufferSize = 10;
		fb.pixelData.resize(bufferSize);

		std::vector<float> values = { -0.5f, -0.25f, 0.0f, 0.5f, 1.5f };
		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			fb.pixelData[i] = values[i % values.size()];
		}
		std::vector<double> expected =
		{
			0.00000000,
			0.00000000,
			0.391699642,
			0.967158675,
			1.00000000,
			0.00000000,
			0.00000000,
			0.391699642,
			0.967158675,
			1.00000000
		};

		TypeParam pipeline;
		pipeline.Process(fb, &metrics);
		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			double e = expected[i];
			double a = fb.pixelData[i];
			EXPECT_NEAR(e, a, 1e-4f);
		}
	}

	TYPED_TEST(BarrierPipelineTests, EmptyTest)
	{
		PipelineMetrics<std::chrono::nanoseconds> metrics;
		FrameBatch fb;
		TypeParam pipeline;
		pipeline.Process(fb, &metrics);

		SUCCEED();
	}

	TEST(BarrierPipelineTest, ParityTest)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);

		PipelineMetrics<std::chrono::nanoseconds> metrics;
		FrameBatch fb_classic;
		FrameBatch fb_modern;
		uint32_t bufferSize = 100000;
		fb_classic.pixelData.resize(bufferSize);
		fb_modern.pixelData.resize(bufferSize);

		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			float val = dis(gen);
			fb_classic.pixelData[i] = val;
			fb_modern.pixelData[i] = val;
		}

		ClassicBarrierPipeline classic;
		ModernSyncBarrierPipeline modern;

		classic.Process(fb_classic, &metrics);
		metrics.Reset();
		modern.Process(fb_modern, &metrics);
		metrics.Reset();

		for (uint32_t i = 0; i < bufferSize; ++i)
		{
			EXPECT_FLOAT_EQ(fb_classic.pixelData[i], fb_modern.pixelData[i]);
		}
	}
}


