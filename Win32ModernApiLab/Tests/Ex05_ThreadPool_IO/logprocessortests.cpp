#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include "classiclogprocessor.h"

using namespace Ex05_ThreadPool_IO;

namespace Ex05_ThreadPool_IO_Tests
{
	static std::filesystem::path getTestSrcDirectory()
	{
		std::filesystem::path src_file_path(__FILE__);

		return src_file_path.parent_path();
	}

	class LogProcessorTests : public ::testing::Test
	{
	public:
		LogProcessorTests()
		{
			std::string expectedFileName = "test_log.txt";
			std::string expectedFilePath = (getTestSrcDirectory() / "expected" / expectedFileName).string();
		}
		void CreateTestLogFile(const std::string& filePath, const uint64_t lines, const bool endingLF)
		{
			std::ofstream ofs(filePath, std::ios::binary);
			if (!ofs)
			{
				throw std::runtime_error("Failed to create test log file: " + filePath);
			}
			for (uint64_t i = 0; i < lines; ++i)
			{
				ofs << "This is a test log line number " << i + 1;
				if (i < lines - 1 || endingLF)
				{
					ofs << "\n";
				}
			}
		}

	private:
		ScopedHandle m_fileHandle;

	};



	TEST(ClassicLogProcessorTests, ProcessValidFile)
	{
		ClassicLogProcessor processor;
		std::wstring testFilePath = L"test_log.txt"; // Ensure this file exists with valid log data for testing
		LogAnalysisResult result = processor.Process(testFilePath);
		// Validate the results (these values should be based on the actual content of test_log.txt)
		EXPECT_GT(result.totalLines, 0);
		EXPECT_GE(result.errorCounts, 0);
		EXPECT_GT(result.totalBytes, 0);
		EXPECT_GT(result.processingTime.count(), 0);
	}
	TEST(ClassicLogProcessorTests, ProcessInvalidFile)
	{
		ClassicLogProcessor processor;
		std::wstring invalidFilePath = L"non_existent_file.txt";
		LogAnalysisResult result = processor.Process(invalidFilePath);
		// Validate that processing an invalid file returns default results
		EXPECT_EQ(result.totalLines, 0);
		EXPECT_EQ(result.errorCounts, 0);
		EXPECT_EQ(result.totalBytes, 0);
		EXPECT_EQ(result.processingTime.count(), 0);
	}
}
