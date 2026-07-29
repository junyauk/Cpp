#include "pch.h"
// GeneratorTest.cpp
#include "..\09_CoroutinesBasics\Generator.h"
#include <gtest/gtest.h>

using namespace CoroutineSamples;

TEST(CoroutineTest, CountUpTo)
{
    Generator<int> gen = count_up_to(5);

    int expected = 1;
    while (gen.next()) {
        EXPECT_EQ(gen.current(), expected);
        ++expected;
    }

    EXPECT_EQ(expected, 6); // Will be 6 eventually after 1...5
}

TEST(CoroutineTest, EmptyGenerator)
{
    Generator<int> gen = count_up_to(0);
    EXPECT_FALSE(gen.next());
}
