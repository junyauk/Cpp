#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaFunctionCost.h"

using namespace LambdaImprovements;

TEST(LambdaFunctionCostTest, CompareLambdaAndStdFunction) {
    constexpr int iterations = 1'000'000;

    auto lambda = []() {};
    std::function<void()> func = lambda;

    double empty = LambdaFunctionCost::measureEmptyLoop(iterations);
    double lambdaCost = LambdaFunctionCost::measureLambdaCost(lambda, iterations);
    double stdFuncCost = LambdaFunctionCost::measureStdFunctionCost(func, iterations);

    std::cout << "Empty loop     : " << empty << " us\n";
    std::cout << "Lambda direct  : " << lambdaCost << " us\n";
    std::cout << "std::function  : " << stdFuncCost << " us\n";

    EXPECT_GT(lambdaCost, empty);       // lambda > empty
    EXPECT_GT(stdFuncCost, lambdaCost); // func > lambda
}
