#pragma once
#include <memory>
#include <future>
#include <vector>
#include <string>
#include <iostream>

namespace LambdaImprovements
{
	class Task
	{
	private:
		std::string m_name;
	public:
		explicit Task(std::string name) : m_name(std::move(name)) {}
		void run()
		{
			std::cout << "Task [" << m_name << "] running on thread "
				<< std::this_thread::get_id() << std::endl;
		}
		const std::string name() { return m_name; }
	};

	class LambdaAsyncTaskExample
	{
	public:
		static std::future<std::string> dispatchTask(std::unique_ptr<Task> task)
		{
			return std::async(std::launch::async, [task = std::move(task)]() mutable
				{
					task->run();
					return task->name();
				});
		}

		static std::vector<std::future<std::string>> dispatchMultipleTasks(std::vector<std::unique_ptr<Task>> tasks)
		{
			std::vector<std::future<std::string>> futures;
			for (auto& t : tasks)
			{
				futures.push_back(dispatchTask(std::move(t)));
			}
			return futures;
		}
	};

}

