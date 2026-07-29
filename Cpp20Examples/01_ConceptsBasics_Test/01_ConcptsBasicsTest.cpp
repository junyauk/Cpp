#include "pch.h"
#include "gtest/gtest.h"

#include "..\01_ConceptsBasics\01_ConceptsBasics.h"
#include "..\TestUtilities\TestUtils.h"
#include <string>

TEST(ConceptsTest, Simple)
{
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_DOUBLE_EQ(add(2.5, 3.1), 5.6);
}

TEST(ConceptsTest, Custom)
{
    std::string s = "Hello";
    std::string output = captureOutput([&]() {
        printLength(s);
        });
    EXPECT_NE(output.find("Length:"), std::string::npos);
}

TEST(ConceptsTest, Multiple)
{
    EXPECT_EQ(negativeValue(-5), 5);
    EXPECT_DOUBLE_EQ(negativeValue(3.14), -3.14);
}

TEST(ConceptsTest, Requires)
{
    EXPECT_EQ(gcd(48, 18), 6);
    EXPECT_EQ(gcd(101, 103), 1);
}

TEST(ConceptsTest, Overload)
{
    {
        std::string output = captureOutput( []() { process(42); } );
        EXPECT_NE(output.find("Integral:"), std::string::npos);
    }
    {
        std::string output = captureOutput( []() { process(3.14); } );
        EXPECT_NE(output.find("Floating point:"), std::string::npos);
    }
}
