#include "pch.h"
#include "LambdaMoveThreadExample.h"

namespace LambdaImprovements
{
	void LambdaMoveThreadExample::runTaskWithMovedResource()
	{
		auto data = std::make_unique<std::string>("Hello from moved unique_ptr!!");

		std::thread worker([ptr = std::move(data)]() mutable
			{
				std::cout << "[Worker] " << *ptr << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				*ptr += " (procssed)";
				std::cout << "[Worker] " << *ptr << std::endl;
			});
		worker.join();
	}

	void LambdaMoveThreadExample::distributeTasks()
	{
		for (int i = 0; i < 3; ++i)
		{
			auto message = std::make_unique<std::string>("Task " + std::to_string(i));
			std::thread([msg = std::move(message), i]
				{
					std::cout << "[Thread " + i << "] " << *msg << std::endl;
				}).detach();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	void LambdaMoveThreadExample::exampleInvalidStdFunctionUsage()
	{
		auto func = [ptr = std::make_unique<int>(42)]() {std::cout << *ptr; };
		// NG
		// This line will cause C2338
//		std::function<void()> f = std::move(func);
//		f();
	}
}

