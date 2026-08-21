#pragma once
#include <string>

namespace Ex02_ThreadPool_WorkTimer
{
	struct TaskData
	{
		uint64_t taskId;
		std::string payload;
		bool isProcessed;
	};
}