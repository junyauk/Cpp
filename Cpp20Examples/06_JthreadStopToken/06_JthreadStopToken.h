#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <deque>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <stop_token>
#include <chrono>

namespace JThreadStopTokenSamples
{
	// -----------------------------------------------------------------------
	class Worker
	{
	private:
		std::jthread _thread;
		void Run(std::stop_token st);
	public:
		Worker();
		~Worker();

		void stop();
	};

	// -----------------------------------------------------------------------
	class Worker2
	{
	private:
		void run(std::stop_token st);
		std::jthread _thread;
		std::string _name;
	public:
		Worker2(const std::string& name);

		~Worker2();

		void stop();
	};

	// -----------------------------------------------------------------------
	class Worker3
	{
	private:
		void run(std::stop_token st);

		std::jthread _thread;
		std::atomic<bool> _running;
		std::atomic<int> _counter;
	public:
		Worker3();
		~Worker3();

		void start();
		void stop();

		bool isRunning() const { return _running; }
		int getCounter() const { return _counter; }
	};


	// -----------------------------------------------------------------------
	class Worker4
	{
	private:
		std::vector<int> m_data;
		std::atomic<int> m_sum;
		std::stop_token m_st;
		std::jthread m_thread;
	public:
		Worker4(std::stop_token st, std::vector<int> data);
		~Worker4();
		void start();
		void join();
		int result() const;
	};

	// -----------------------------------------------------------------------
	class Worker5
	{
	private:
		std::atomic<bool> m_running;
		std::stop_token m_st;
		std::jthread m_thread;
	public:
		Worker5(std::stop_token st);
		void start();
		void join();
		bool isRunning() const;
	};



	// -----------------------------------------------------------------------
	class ThreadPool
	{
	private:
		void worker(std::stop_token st);

		std::queue<std::function<void()>> tasks;
		std::mutex queueMutex;
		std::condition_variable_any cv;
		bool stopped = false;
		std::vector<std::jthread> workers; // worker threads need to be destroyed before other members
	public:
		explicit ThreadPool(std::size_t numThreads);
		~ThreadPool();

		void enqueue(std::function<void()> task);
		void stop();
	};

	// -----------------------------------------------------------------------
	class WorkerPool
	{
	private:
		void workerTask(std::stop_token st, size_t id);
		std::vector<std::jthread> workers;
		std::stop_source stopSource;
	public:
		WorkerPool(size_t workerCount);
		~WorkerPool();
		void stop_all();
	};

	// -----------------------------------------------------------------------



}
