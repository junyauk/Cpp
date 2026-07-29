#include "pch.h"
#include "..\05_ThreeWayComparison\05_ThreeWayComparison.h"

namespace ThreeWayComparisonSamples
{
	TEST(ThreeWayComparisonTests, PersonComparison_Defaulted)
	{
        Person alice{ "Alice", 25 };
        Person bob{ "Bob", 30 };
        Person alice2{ "Alice", 25 };

        EXPECT_TRUE(alice < bob);
        EXPECT_TRUE(bob > alice);
        EXPECT_TRUE(alice == alice2);
    }

    TEST(ThreeWayComparisonTests, PointComparison_Manual)
    {
        Point p1{ 1, 2 };
        Point p2{ 1, 3 };
        Point p3{ 2, 0 };

        EXPECT_TRUE(p1 < p2);
        EXPECT_TRUE(p2 < p3);
        EXPECT_TRUE(p1 != p3);
    }

    TEST(ThreeWayComparisonTests, CompareAges)
    {
        Person alice{ "Alice", 25 };
        Person bob{ "Bob", 30 };

        EXPECT_EQ(CompareAges(alice, bob), -1);
        EXPECT_EQ(CompareAges(bob, alice), 1);
        EXPECT_EQ(CompareAges(alice, alice), 0);
    }

    TEST(ThreeWayComparisonTests, CompareInts)
    {
        EXPECT_EQ(CompareInts(3, 5), "3 < 5");
        EXPECT_EQ(CompareInts(7, 7), "7 == 7");
        EXPECT_EQ(CompareInts(10, 2), "10 > 2");
    }

    TEST(ThreeWayComparisonTests, CompareDoubles)
    {
        EXPECT_EQ(CompareDoubles(3.14, 2.71), "3.14 > 2.71");
        EXPECT_EQ(CompareDoubles(5.0, 5.0), "5 == 5");
        EXPECT_EQ(CompareDoubles(1.0, 2.0), "1 < 2");

        double nan = std::numeric_limits<double>::quiet_NaN();
        EXPECT_EQ(CompareDoubles(nan, 1.0), "");
    }
}
