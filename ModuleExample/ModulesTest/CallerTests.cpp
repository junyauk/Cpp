#include "pch.h"
#include "..\Caller\Caller.h"
import ModuleT;


using namespace moduleexample::caller;

class CallerBasicTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(CallerBasicTest, TestCallAdd)
{
    EXPECT_EQ(call_add(2, 3), 50);   // (2+3)*10
    EXPECT_EQ(call_add(-1, 1), 0);   // (-1+1)*10
}

TEST_F(CallerBasicTest, TestCallConcat)
{
    EXPECT_EQ(call_concat("A", "B"), "[A|B]");
}

TEST_F(CallerBasicTest, TestComputeValue)
{
    EXPECT_EQ(call_compute_value(1), 200); // (1+1)*100
    EXPECT_EQ(call_compute_value(2), 300); // (2+1)*100
}

TEST_F(CallerBasicTest, TestGetMessage) {
    EXPECT_EQ(call_get_message(), "ModuleA says hi!");
}

TEST_F(CallerBasicTest, TestCallMultiply)
{
    EXPECT_EQ(call_multiply(3, 5), 15);
    EXPECT_EQ(call_multiply(-2, 4), -8);
}

TEST_F(CallerBasicTest, TestCallCalculatorInfo)
{
    EXPECT_EQ(call_calculator_info(), "ModuleA::Calculator");
}

class CallerUsingModulesTest : public ::testing::Test
{ };

TEST_F(CallerUsingModulesTest, TestCallAddBoth)
{
    // ModuleA: (2+3)*10=50
    // ModuleB: (2+3)*100=500
    EXPECT_EQ(call_add_both(2, 3), 550);

    // ModuleA: (-1+1)*10=0
    // ModuleB: (-1+1)*100=0
    EXPECT_EQ(call_add_both(-1, 1), 0);
}

TEST_F(CallerUsingModulesTest, TestCallConcatBoth) {
    EXPECT_EQ(call_concat_both("A", "B"), "[A|B]<A,B>");
}

TEST_F(CallerUsingModulesTest, TestComputeValueBoth) {
    // ModuleA: (2+1)*100=300
    // ModuleB: (2+1)*1000=3000
    EXPECT_EQ(call_compute_value_both(2), 3300);
}

TEST_F(CallerUsingModulesTest, TestGetMessageBoth) {
    EXPECT_EQ(call_get_message_both(), "ModuleA says hi! | ModuleB says hello!");
}

TEST_F(CallerUsingModulesTest, TestCallMultiplyBoth) {
    // ModuleA: 3*5=15
    // ModuleB: 3*5*10=150
    EXPECT_EQ(call_multiply_both(3, 5), 165);

    // ModuleA: -2*4=-8
    // ModuleB: -2*4*10=-80
    EXPECT_EQ(call_multiply_both(-2, 4), -88);
}
TEST_F(CallerUsingModulesTest, TestCalculatorInfoBoth) {
    EXPECT_EQ(call_calculator_info_both(), "ModuleA::Calculator & ModuleB::Calculator");
}

class CallerUsingLegacyTest : public ::testing::Test {};

TEST_F(CallerUsingLegacyTest, TestCallLegacyAdd) {
    EXPECT_EQ(call_legacy_add(2, 3), 5);
    EXPECT_EQ(call_legacy_add(-1, 1), 0);
}

TEST_F(CallerUsingLegacyTest, TestCallLegacyMultiply) {
    EXPECT_EQ(call_legacy_multiply(3, 5), 15);
    EXPECT_EQ(call_legacy_multiply(-2, 4), -8);
}

TEST_F(CallerUsingLegacyTest, TestCallLegacyCalculatorInfo) {
    EXPECT_EQ(call_legacy_calculator_info(), "LegacyCalculator");
}


class CallerParamTest : public ::testing::TestWithParam<int> {};

TEST_P(CallerParamTest, ComputeValueParam) {
    int x = GetParam();
    EXPECT_EQ(call_compute_value(x), (x + 1) * 100);
}

INSTANTIATE_TEST_CASE_P(
    ComputeValueTests,
    CallerParamTest,
    ::testing::Values(0, 1, 2, 5, 10)
);

class CallerNestedModulesTest : public ::testing::Test {};

// ----------------- Test APIs using Legacy via ModuleA -----------------
TEST_F(CallerNestedModulesTest, CallLegacyAddViaModuleA)
{
    EXPECT_EQ(call_legacy_add_viaModuleA(3, 5), 8);
}

TEST_F(CallerNestedModulesTest, CallCalculatorLegacyMultiplyViaModuleA)
{
    EXPECT_EQ(call_calculator_legacy_multiply_viaModuleA(3, 4), 12);
}

TEST_F(CallerNestedModulesTest, CallCalculatorLegacyInfoViaModuleA)
{
    EXPECT_EQ(call_calculator_legacy_info_viaModuleA(), "LegacyCalculator info via ModuleA");
}


// ----------------- Test APIs using Legacy via ModuleB -----------------
class CallerUsingModuleBTest : public ::testing::Test {};

TEST_F(CallerUsingModuleBTest, CallLegacyAddViaModuleB)
{
    EXPECT_EQ(call_legacy_add_viaModuleB(2, 3), 6); // 2+3 +1
}

TEST_F(CallerUsingModuleBTest, CallCalculatorLegacyMultiplyViaModuleB)
{
    EXPECT_EQ(call_calculator_legacy_multiply_viaModuleB(3, 4), 24); // 3*4 *2
}

TEST_F(CallerUsingModuleBTest, CallCalculatorLegacyInfoViaModuleB)
{
    EXPECT_EQ(call_calculator_legacy_info_viaModuleB(), "LegacyCalculator info via ModuleB");
}


// ----------------- Test API combining constants -----------------------------
TEST_F(CallerNestedModulesTest, GetCombinedValuesString)
{
    std::string expected = "ModuleA: 100, Legacy: 500, Combined: 600";
    EXPECT_EQ(get_combined_values_string(), expected);
}



// ----------------- Test API basic template ----------------------------------
TEST_F(CallerBasicTest, TestCallTwiceTemplate)
{
    EXPECT_EQ(call_twice(10), 20);
    EXPECT_DOUBLE_EQ(call_twice(1.5), 3.0);
}

TEST_F(CallerNestedModulesTest, TestModuleT_BoxBasic)
{
    moduleexample::modulet::Box<int> b(10);
    EXPECT_EQ(b.get(), 10);

    b.set(20);
    EXPECT_EQ(b.get(), 20);
}

// ----------------- Test APIs using Legacy via ModuleB -----------------
class CallerModuleTemplateTest : public ::testing::Test {};

TEST_F(CallerModuleTemplateTest, TestModuleT_BoxString)
{
    moduleexample::modulet::Box<std::string> b("Hello");
    EXPECT_EQ(b.get(), "Hello");

    b.set("World");
    EXPECT_EQ(b.get(), "World");
}

TEST_F(CallerModuleTemplateTest, TestPairInt)
{
    EXPECT_EQ(call_pair_int_to_string(2, 3), "2, 3");
    EXPECT_EQ(call_pair_int_to_string(-1, 10), "-1, 10");
}

TEST_F(CallerModuleTemplateTest, TestPairStringInt)
{
    EXPECT_EQ(call_pair_string_int_to_string("hello", 42), "hello, 42");
    EXPECT_EQ(call_pair_string_int_to_string("test", 0), "test, 0");
}

TEST_F(CallerModuleTemplateTest, TestModuleT_NumberBox_Int)
{
    auto info = GetIntNumberInfo(123);
    EXPECT_EQ(info.value, 123);
}

TEST_F(CallerModuleTemplateTest, TestModuleT_NumberBox_String)
{
    auto info = GetStringNumberInfo("ABCDE");
    EXPECT_EQ(info.value, 5);
}

// Caller using simple template function from TemplateA/B
TEST_F(CallerModuleTemplateTest, AddInt)
{
    EXPECT_EQ(addInt(2, 3), 5);
}

TEST_F(CallerModuleTemplateTest, MulDouble)
{
    EXPECT_DOUBLE_EQ(mulDouble(1.5, 2.0), 3.0);
}

TEST(CallerAPITest, AddThenMulInt)
{
    EXPECT_EQ(addThenMulInt(2, 3, 4), (2 + 3) * 4);
}

// Will have link errors because add<float> is not instantiated anywhere
// TEST(CallerAPITest, AddFloat)
// {
//     EXPECT_FLOAT_EQ(add(1.0f,2.0f), 3.0f);
// }
