#include "pch.h"
#include "DynamicPriorityTaskDispatcher_AutoShrink.h"
#include "JobSystemExample.h"

namespace LambdaImprovements
{
	void RunJobSystemSimpleExample()
	{
		DynamicPriorityTaskDispatcher_AutoShrink dispatcher(4, 8);

		std::vector<Job> jobs =
		{
			{ JobType::AI, 800, "AI_Analysis_1" },
			{ JobType::IO, 500, "IO_ReadDisk" },
			{ JobType::UI, 300, "UI_Update" },
			{ JobType::AI, 1000, "AI_Analysis_2" },
			{ JobType::IO, 700, "IO_WriteNetwork" },
			{ JobType::UI, 200, "UI_Animation" }
		};

		std::vector<std::future<void>> futures;

		for (auto& job : jobs)
		{
			int priority = getPriority(job);
			futures.push_back(dispatcher.enqueue(priority, [job]() { processJob(job); }));
		}

		for (auto& f : futures)
		{
			f.get();
		}

		std::cout << "All jobs completed.\n";
	}

	void RunJobSystemAIScoreExample()
	{
		DynamicPriorityTaskDispatcher_AutoShrink dispatcher(2, 8);

		std::vector<Job> jobs =
		{
			{ JobType::AI, 800, "AI_Model_A" },
			{ JobType::AI, 600, "AI_Model_B" },
			{ JobType::IO, 400, "IO_LoadTexture" },
			{ JobType::UI, 200, "UI_Refresh" },
			{ JobType::AI, 700, "AI_Model_C" },
			{ JobType::IO, 500, "IO_SaveResult" }
		};

		std::vector<std::future<double>> aiFutures;
		std::vector<std::future<void>> otherFutures;

		for (auto& j : jobs)
		{
			int priority = getPriority(j);
			if (j.type == JobType::AI)
			{
				aiFutures.push_back(dispatcher.enqueue(priority, [j]() {return processAIJob(j); }));
			}
			else
			{
				otherFutures.push_back(dispatcher.enqueue(priority, [j]() {return processSimpleJob(j); }));
			}
		}

		for (auto& f : otherFutures)
		{
			f.get();
		}

		double total = 0.0;
		for (auto& f : aiFutures)
		{
			total += f.get();
		}

		double average = total / aiFutures.size();

		std::cout << "\nAverage AI scores = " << average << std::endl;
	}
}

