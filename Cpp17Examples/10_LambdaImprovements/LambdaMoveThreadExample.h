#pragma once
#include <functional>
#include <thread>
#include <memory>
#include <iostream>
#include <string>
#include <chrono>

namespace LambdaImprovements
{
	class LambdaMoveThreadExample
	{
	public:
		static void runTaskWithMovedResource();
		static void distributeTasks();
		static void exampleInvalidStdFunctionUsage();
	};
}

