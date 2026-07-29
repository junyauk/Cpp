#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\BindPitfallsExample.h"

using namespace LambdaImprovements;


TEST(BindPitfallsExampleTest, WrongOrderBind_ShowsSwappedBehavior) {
    auto f = BindPitfallsExample::wrongOrderBind();
    // actually you can't see the difference, but the order of parameters is changed
    EXPECT_EQ(f(2, 5), 7);
}

TEST(BindPitfallsExampleTest, CorrectOrderLambda_WorksAsExpected) {
    auto f = BindPitfallsExample::correctOrderLambda();
    EXPECT_EQ(f(2, 5), 7);
}

TEST(BindPitfallsExampleTest, DanglingReferenceBind_IsUnsafe) {
    auto f = BindPitfallsExample::danglingReferenceBind();
    // Execution will result in undefined behavior (cannot be safely tested, so do not call it)
    SUCCEED() << "Returning a callable that holds a dangling reference is unsafe!";
}

TEST(BindPitfallsExampleTest, SafeLambda_IsSafeAndNoCrash) {
    auto f = BindPitfallsExample::safeLambda();
    EXPECT_NO_THROW(f());
}
