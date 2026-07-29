#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <chrono>
#include <iostream>
#include <random>

namespace LambdaImprovements
{
	enum class JobType
	{
		AI,
		IO,
		UI
	};

	struct Job
	{
		JobType type;
		int durationMs;
		std::string name;
	};

	inline void processJob(const Job& job)
	{
		std::cout << "[START] " << job.name << " on thread "
			<< std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(job.durationMs));
		std::cout << "[DONE ] " << job.name << std::endl;
	}

	inline double processAIJob(const Job& job)
	{
		std::cout << "{AI   } Start " << job.name << " on thread "
			<< std::this_thread::get_id() << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(job.durationMs));

		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_real_distribution<> dist(0.0, 100.0);
		double score = dist(gen);

		std::cout << "[AI   ] Done  " << job.name
			<< " -> score: " << score << std::endl;
		return score;
	}
	inline void processSimpleJob(const Job& job)
	{
		std::cout << "[TASK ] Start " << job.name << " on thread "
			<< std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(job.durationMs));
		std::cout << "[TASK ] Done  " << job.name << std::endl;
	}

	inline int getPriority(const Job& job)
	{
		switch (job.type)
		{
		case JobType::AI: return 3;
		case JobType::IO: return 2;
		case JobType::UI: return 1;
		default: return 0;
		}
	}
}
