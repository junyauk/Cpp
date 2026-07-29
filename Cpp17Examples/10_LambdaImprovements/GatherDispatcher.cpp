#include "pch.h"
#include "GatherDispatcher.h"
#include <iostream>

namespace LambdaImprovements
{
	void runGatherDispatcherExample()
	{
		GatherDispatcher<int> gd;
		gd.submit([]() {return 1; });
		gd.submit([]() {return 2; });
		gd.submit([]() -> int {throw std::runtime_error("boom"); });

		auto futures = gd.runAll();
		auto results = GatherDispatcher<int>::gather(futures);

		for (size_t i = 0; i < results.size(); ++i)
		{
			if (std::holds_alternative<int>(results[i]))
			{
				std::cout << "Result[" << i << "] = " << std::get<int>(results[i]) << std::endl;
			}
			else
			{
				try
				{
					std::rethrow_exception(std::get<std::exception_ptr>(results[i]));
				}
				catch (const std::exception& e)
				{
					std::cout << "Result[" << i << "] exception: " << e.what() << std::endl;
				}
			}
		}
	}
}
