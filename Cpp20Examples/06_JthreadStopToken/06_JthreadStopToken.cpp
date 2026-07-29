#include "pch.h"
#include "framework.h"
#include "06_JthreadStopToken.h"


namespace JThreadStopTokenSamples
{
	// -----------------------------------------------------------------------
	void Worker::Run(std::stop_token st)
	{
		int counter = 0;
		while (!st.stop_requested())
		{
			std::cout << "Working..." << counter++ << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		std::cout << "Worker stopped." << std::endl;
	}
	Worker::Worker()
	{
		_thread = std::jthread([this](std::stop_token st)
			{
				this->Run(st);
			});
	}
	Worker::~Worker()
	{
		stop();
	}

	void Worker::stop()
	{
		if (_thread.joinable())
		{
			_thread.request_stop();
			_thread.join();
		}
	}

	// -----------------------------------------------------------------------
	void Worker2::run(std::stop_token st)
	{
		while (!st.stop_requested())
		{
			std::cout << "Worker2: " << _name << " is running...\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		std::cout << "Worker2: " << _name << " exiting...\n";
	}

	Worker2::Worker2(const std::string& name)
		:_name(name)
	{
		_thread = std::jthread([this](std::stop_token st)
			{
				this->run(st);
			});
		std::cout << "Worker2: " << _name << " started.\n";
	}

	Worker2::~Worker2()
	{
		stop();
		std::cout << "Worker2: " << _name << " destroyed.\n";
	}

	void Worker2::stop()
	{
		if (_thread.joinable())
		{
			_thread.request_stop();
			_thread.join();
			std::cout << "Worker2: " << _name << " stopped.\n";
		}
	}

	// -----------------------------------------------------------------------
	void Worker3::run(std::stop_token st)
	{
		while (!st.stop_requested())
		{
			++_counter;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::cout << "Thread is exiting.\n";
	}
	Worker3::Worker3()
	{
	}
	Worker3::~Worker3()
	{
		stop();
	}

	void Worker3::start()
	{
		if (_running) return;

		_running = true;
		_counter = 0;

//		_thread = std::jthread(&Worker3::run, this);
		_thread = std::jthread([this](std::stop_token st)
			{
				this->run(st);
			});
	}
	void Worker3::stop()
	{
		if (_thread.joinable())
		{
			_thread.request_stop();
			_thread.join();
		}
		_running = false;
	}


	// -----------------------------------------------------------------------
	Worker4::Worker4(std::stop_token st, std::vector<int> data)
		: m_st(st), m_data(std::vector<int>(data)), m_sum(0) {}

	Worker4::~Worker4()
	{
		join();
	}

	void Worker4::start()
	{
		m_thread = std::jthread([this](std::stop_token st)
			{
				for (int value : m_data)
				{
					if (st.stop_requested() || m_st.stop_requested())
					{
						std::cout << "Worker4: Stopping early due to stop request.\n";
						return;
					}
					m_sum += value;
					std::this_thread::sleep_for(std::chrono::milliseconds(20));
				}
			});
	}

	void Worker4::join()
	{
		if (m_thread.joinable())
			m_thread.join();
	}
	int Worker4::result() const { return m_sum.load(); }


	// -----------------------------------------------------------------------
	Worker5::Worker5(std::stop_token st)
		: m_st(st), m_running(false){}
	void Worker5::start()
	{
		m_running = true;
		m_thread = std::jthread([this](std::stop_token st)
			{
				while (!m_st.stop_requested())
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					std::cout << "Worker5 [" << std::this_thread::get_id() << "] is running...\n";
				}
				std::cout << "Worker5 is stopping...\n";
				m_running = false;
			});

	}
	void Worker5::join()
	{
		if (m_thread.joinable())
			m_thread.join();
	}
	bool Worker5::isRunning() const { return m_running.load(); }
	// -----------------------------------------------------------------------
	void ThreadPool::worker(std::stop_token st)
	{
		while (!st.stop_requested())
		{
			std::function<void()> task;
			{
				std::unique_lock lock(queueMutex);
				cv.wait(lock, st, [this]()
					{
						return stopped || !tasks.empty();
					});

				if (tasks.empty())
				{
					if (stopped || st.stop_requested())
					{
						break;
					}
					else
						continue;
				}
				task = std::move(tasks.front());
				tasks.pop();
			}
			task();
			std::cout << "Task was processed.\n";
		}
		std::cout << "ThreadPool worker stopped.\n";
	}
	ThreadPool::ThreadPool(std::size_t numThreads)
	{
		for (auto i = 0; i < numThreads; ++i)
		{
			workers.emplace_back([this](std::stop_token st)
				{
					this->worker(st);
				});
		}
	}
	ThreadPool::~ThreadPool()
	{
		stop();
	}
	void ThreadPool::enqueue(std::function<void()> task)
	{
		{
			std::scoped_lock lock(queueMutex);
			tasks.push(std::move(task));
		}
		cv.notify_one();
	}
	void ThreadPool::stop()
	{
		{
			std::scoped_lock lock(queueMutex);
			stopped = true;				// closing the queue indicates that we are stopping
		}
		cv.notify_all();				// wake up all threads

		for (auto& worker : workers)
		{
			if (worker.joinable())
			{
				worker.request_stop();// Need to request stop for each jthread
			}
		}
	}

	// -----------------------------------------------------------------------
	void WorkerPool::workerTask(std::stop_token st, size_t id)
	{
		while (!st.stop_requested())
		{
			std::cout << "Worker " << id << " is running...\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		std::cout << "Worker " << id << " stopped.\n";
	}
	WorkerPool::WorkerPool(size_t workerCount)
	{
		for (size_t i = 0; i < workerCount; ++i)
		{
			workers.emplace_back([this, i](std::stop_token st)
				{
					this->workerTask(st, i);
				});
		}
	}
	WorkerPool::~WorkerPool()
	{
		stop_all();
	}
	void WorkerPool::stop_all()
	{
		if (!stopSource.stop_requested())
		{
			stopSource.request_stop();
		}
	}

	// -----------------------------------------------------------------------


}


