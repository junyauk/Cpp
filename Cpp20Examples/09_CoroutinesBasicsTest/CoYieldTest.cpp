#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_CoroutinesBasics\CoYieldSample.h"
#include <filesystem>

using namespace CoYieldSample;

TEST(CoroutineTest, FibonacciGeneration)
{
	std::vector<int> expected{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };

	auto gen = fibonacci_genrator();
	int count = 0;
	for (int num : gen)
	{
		EXPECT_EQ(num, expected[count]);
		if (++count >= 10)
		{
			break;
		}
	}
	std::cout << "finished.\n";
}

TEST(CoroutineTest, ReadLineFromCSV)
{
	std::string file_name = "data.csv";
	std::vector<std::string> data =
	{
		"Name,Age\n",
		"Alice,30\n",
		"Bob,25\n"
	};

	std::ofstream test_file(file_name);
	for (const auto& line : data)
	{
		test_file << line;
	}
	test_file.close();

	int i = 0;
	for (const auto& line : read_lines_from_csv(file_name))
	{
		EXPECT_EQ(line + "\n", data[i++]);
	}

	if (std::filesystem::exists(file_name))
	{
		std::filesystem::remove(file_name);
	}
}

class CSVGeneratorTest : public ::testing::Test
{
protected:
	const std::string test_filename = "Test_data.csv";

    void SetUp() override
    {
    if (std::filesystem::exists(test_filename))
    {
    std::filesystem::remove(test_filename);
    }

    std::ofstream file(test_filename);
    file << "Header1,Header2\n";
    file << "value1,value2\n";
    file << "value3,value4\n";
    file.close();
    }

	void TearDown() override
	{
		if (std::filesystem::exists(test_filename))
		{
			std::filesystem::remove(test_filename);
		}
	}
};

TEST_F(CSVGeneratorTest, ReadsAllLinesCorrectly)
{
	std::vector<std::string> expected_lines
	{
		"Header1,Header2\n",
		"value1,value2\n",
		"value3,value4\n"
	};

	std::vector<std::string> actual_lines;
	for (const auto& line : read_lines_from_csv(test_filename))
	{
		actual_lines.push_back(line + "\n");
	}

	ASSERT_EQ(expected_lines, actual_lines);
}

TEST_F(CSVGeneratorTest, HandlesNonexistentFile)
{
	Generator<std::string> gen = read_lines_from_csv("nonexistent.csv");

	ASSERT_EQ(gen.begin(), gen.end());
}
