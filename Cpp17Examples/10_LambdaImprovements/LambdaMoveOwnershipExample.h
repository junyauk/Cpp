#pragma once
#include <iostream>
#include <string>
#include <future>
#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include <chrono>

namespace LambdaImprovements
{
	class LambdaMoveOwnershipExample
	{
	public:
		// 1. using std::async with unique_ptr
		static std::string processWithAsync();

		// 2. Thread pool like
		static void runThreadPoolSimulation();

		// 3. Transfer file as unique_ptr<fstream>
		static bool writeToFileWithMove(const std::string& filename);

		// 4. Two stage move
		static std::unique_ptr<std::string> transferOwnershipTwice();
	};
}

