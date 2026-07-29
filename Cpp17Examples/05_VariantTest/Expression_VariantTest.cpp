#include "pch.h"
#include "gtest/gtest.h"
#include "..\05_Variant\Expression_Variant.h"

using namespace ExpressionVariantExamples;

TEST(ExpressionVariantTests, SimpleNumber)
{
	Expr e = Number{ 42 };
	EXPECT_DOUBLE_EQ(eval(e), 42);
}

TEST(ExpressionVariantTests, AddNumbers)
{
	Expr e = std::make_shared<Add>(Add{ Number{2}, Number{3} });
	EXPECT_DOUBLE_EQ(eval(e), 5);
}

TEST(ExpressionVariantTests, MulAndAdd)
{
	Expr e = std::make_shared<Add>(
		Add
		{
			std::make_shared<Mul>(
					Mul{ Number{2},
						 Number{3}}
			),
			Number{4}
		}
	);
	EXPECT_DOUBLE_EQ(eval(e), 10);
}
