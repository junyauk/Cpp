#include "pch.h"
#include "..\04_StdSpan\04_StdSpan.h"
#include <vector>
#include <array>
#include <string>

using namespace StdSpanSamples;

TEST(StdSpanTest, SumArray) 
{
    int arr[] = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(Sum(arr), 15);
}

TEST(StdSpanTest, SumVector)
{
    std::vector<int> vec = { 10, 20, 30 };
    EXPECT_EQ(Sum(vec), 60);
}

TEST(StdSpanTest, Subspan)
{
    std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
    auto sub = GetSubspan(arr, 1, 3);
    EXPECT_EQ(Sum(sub), 2 + 3 + 4);
}

TEST(StdSpanTest, ContainsChar)
{
    std::string text = "hello";
    EXPECT_TRUE(ContainsChar(text, 'e'));
    EXPECT_FALSE(ContainsChar(text, 'z'));
}

TEST(StdSpanTest, SumMatrix)
{
    int mat[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    auto flat = std::span(mat[0], 6);
    EXPECT_EQ(SumMatrix(flat), 21);
}

TEST(StdSpanTest, PrintNumbers)
{
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        testing::internal::CaptureStdout();
        PrintNumbers(arr);
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_EQ(result, "1 2 3 4 5 \n");
    }

    {
        std::vector<int> vec = { 10, 20, 30, 40 };
        testing::internal::CaptureStdout();
        PrintNumbers(vec);
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_EQ(result, "10 20 30 40 \n");
    }
}

TEST(StdSpanTest, PrintSlice)
{
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7 };
    std::span<int> spanAll(data);
    std::span<int> spanMid = spanAll.subspan(2, 3);

    {
        testing::internal::CaptureStdout();
        PrintNumbers(spanAll); // 1 2 3 4 5 6 7
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_EQ(result, "1 2 3 4 5 6 7 \n");
    }
    {
        testing::internal::CaptureStdout();
        PrintNumbers(spanMid); // 3 4 5
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_EQ(result, "3 4 5 \n");
    }
}

TEST(StdSpanTest, FillBuffer)
{
    std::array<int, 5> arr{};

    FillBuffer(arr, 42);

    for (auto v : arr)
    {
        EXPECT_EQ(v, 42);
    }
}

TEST(StdSpanTest, PrintMatrix)
{
    int mat[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    testing::internal::CaptureStdout();
    PrintMatrix(std::span<int, 9>(reinterpret_cast<int*>(mat), 9));
    auto result = testing::internal::GetCapturedStdout();
    EXPECT_EQ(result, "1 2 3\n4 5 6\n7 8 9\n");
}
