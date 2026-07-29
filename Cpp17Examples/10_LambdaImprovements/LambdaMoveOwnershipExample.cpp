#include "pch.h"
#include "LambdaMoveOwnershipExample.h"

namespace LambdaImprovements
{
	// 1. using std::async with unique_ptr
	std::string LambdaMoveOwnershipExample::processWithAsync()
	{
		auto data = std::make_unique<std::string>("async_task_data");
		auto future = std::async(std::launch::async,
			[ptr = std::move(data)]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				return *ptr + "_processed";
			});
		return future.get();
	}

	// 2. Thread pool like
	void LambdaMoveOwnershipExample::runThreadPoolSimulation()
	{
		std::vector<std::thread> threads;
		for (int i = 0; i < 3; ++i)
		{
			auto msg = std::make_unique<std::string>("task_" + std::to_string(i));
			threads.emplace_back([m = std::move(msg), i]() mutable
				{
					std::cout << "[Worker " << i << "] processing: " << *m << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(30));
					*m += "_done";
					std::cout << "[Worker " << i << "] result: " << *m << std::endl;
				});
		}

		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
	}

	// 3. Transfer file as unique_ptr<fstream>
	bool LambdaMoveOwnershipExample::writeToFileWithMove(const std::string& filename)
	{
		auto file = std::make_unique<std::ofstream>(filename);
		if (!file->is_open()) return false;

		auto writer = [f = std::move(file)]() mutable
			{
				(*f) << "Hello from moved fstream!" << std::endl;
			};
		writer();
		return true;
	}

	// 4. Two stage move
	std::unique_ptr<std::string> LambdaMoveOwnershipExample::transferOwnershipTwice()
	{
		auto msg = std::make_unique<std::string>("first_owner");
		auto forwarder = [ptr = std::move(msg)]() mutable
			{
				return [p = std::move(ptr)]() mutable
					{
						*p += "_moved_twice";
						return std::move(p);
					};
			};
		auto secondLambda = forwarder(); // first_owner -> forwarder -> secondLambda
		auto ret = secondLambda();
		return ret;
	}
}


