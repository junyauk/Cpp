#include "pch.h"
#include "gtest/gtest.h"
#include "..\06_CTAD\01_MyPair.h"
#include "..\06_CTAD\02_Overloaded.h"
#include "..\06_CTAD\03_MoveOnlyOverloaded.h"

#include <any>

TEST(MyPairTest, DeductionGuideWorks)
{
	using namespace CTADExample1;

	MyPair p1(42, std::string("hello"));
	static_assert(std::is_same_v<decltype(p1), MyPair<int, std::string>>);

	EXPECT_EQ(p1.first, 42);
	EXPECT_EQ(p1.second, "hello");

	MyPair p2(3.14, true);
	static_assert(std::is_same_v<decltype(p2), MyPair<double, bool>>);
	EXPECT_DOUBLE_EQ(p2.first, 3.14);
	EXPECT_TRUE(p2.second);
}

TEST(OverloadedTest, VariantVisitWorks)
{
	using namespace CTADExample2;

	std::variant<int, std::string, bool> v;

	auto visitor = CTADExample2::Overloaded
	{
		[](int arg) { EXPECT_EQ(arg, 42); },
		[](const std::string& arg) { FAIL() << "Unexpected string"; },
		[](bool arg) { FAIL() << "Unexpected bool"; }
	};

	v = 42;
	std::visit(visitor, v);

	v = std::string("hello");
	auto visitor2 = CTADExample2::Overloaded
	{
		[](int arg) { FAIL() << "Unexpected int"; },
		[](const std::string& arg) { EXPECT_EQ(arg, "hello"); },
		[](bool arg) { FAIL() << "Unexpected bool"; }
	};

	v = true;
	auto visitor3 = CTADExample2::Overloaded
	{
		[](int arg) { FAIL() << "Unexpected int"; },
		[](const std::string& arg) { FAIL() << "Unexpected string"; },
		[](bool arg) { EXPECT_TRUE(arg); }
	};

	std::visit(visitor3, v);
}


TEST(MoveOnlyOverloadedTest, MoveOnlyVariantWorks)
{
	using namespace CTADExample3;

	std::variant<int, CTADExample3::MoveOnly> v;

	v = MoveOnly("init");
	auto visitor = CTADExample3::Overloaded
	{
		[](int arg) { FAIL() << "Unexpected int"; },
		[](const MoveOnly& arg) { EXPECT_EQ(arg.data, "init"); }
	};
	std::visit(visitor, v);

	v = MoveOnly("moved data");
	auto visitor2 = CTADExample3::Overloaded
	{
		[](int arg) { FAIL() << "Unexpected int"; },
		[](const MoveOnly& arg) { EXPECT_EQ(arg.data, "moved data"); }
	};

	v = 100;
	auto visitor3 = CTADExample3::Overloaded
	{
		[](int arg) { EXPECT_EQ(arg, 100); },
		[](const MoveOnly& arg) { FAIL() << "Unexpected MoveOnly"; }
	};
	std::visit(visitor3, v);
}

TEST(VariantHelperTest, HoldsAlternativeWorks)
{
	std::variant<int, std::string, bool> v = 42;

	EXPECT_TRUE(std::holds_alternative<int>(v));
	EXPECT_FALSE(std::holds_alternative<std::string>(v));
	EXPECT_FALSE(std::holds_alternative<bool>(v));

	v = std::string("test");
	EXPECT_TRUE(std::holds_alternative<std::string>(v));

	v = true;
	EXPECT_TRUE(std::holds_alternative<bool>(v));
}


TEST(AnyTest, AnyWorks)
{
	using namespace CTADExample3;
	std::any a = 42;

	EXPECT_TRUE(a.type() == typeid(int));
	EXPECT_EQ(std::any_cast<int>(a), 42);

	a = std::string("test");
	EXPECT_TRUE(a.type() == typeid(std::string));
	EXPECT_EQ(std::any_cast<std::string>(a), "test");

	a = 3.14;
	EXPECT_THROW(std::any_cast<int>(a), std::bad_any_cast);

	a = MoveOnly("any moveonly");
	EXPECT_TRUE(a.type() == typeid(MoveOnly));
	EXPECT_EQ(std::any_cast<MoveOnly>(a).data, "any moveonly");
}