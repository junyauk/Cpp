#pragma once

#include <WinSock2.h>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <condition_variable>
#include <unordered_map>

namespace SocketCommon
{
	class HeartBeatClient
	{
	public:
		HeartBeatClient(SOCKET mainSocket, const std::string& ip, const uint16_t port, const std::string sessionId);
		HeartBeatClient() = delete;
		~HeartBeatClient();

		HeartBeatClient(const HeartBeatClient&) = delete;
		HeartBeatClient(HeartBeatClient&&) = delete;
		HeartBeatClient& operator=(const HeartBeatClient&) = delete;
		HeartBeatClient& operator=(HeartBeatClient&&) = delete;

		void Start(const uint32_t pingIntervalSec = 5, const uint32_t timeoutSec = 15);
		void Stop();

//		void SetActiveTime();
		bool IsPeerAlive() const;

	private:
		void MonitorLoop(std::stop_token st);

		std::atomic<SOCKET> m_mainSocket = INVALID_SOCKET;

		const std::string m_ip;
		const uint16_t m_port;
		const std::string m_sessionId;

		uint32_t m_pingInterval = 0;
		uint32_t m_timeout = 0;

		std::atomic<SOCKET> m_socket = INVALID_SOCKET;
		std::atomic<std::chrono::steady_clock::time_point> m_lastActiveTime = std::chrono::steady_clock::now();
		std::atomic<bool> m_running = false;
		std::promise<void> m_stopSignal;
		std::jthread m_thread;
	};

	class HeartBeatSession
	{
	public:
		HeartBeatSession(SOCKET hbSocket, SOCKET mainSocket, std::string userId);
		~HeartBeatSession();

		void Start(const uint16_t timeoutSec = 15);
		void Stop();

		bool IsPeerAlive() const;
		void SetActiveTime();

		void SetTargetSocket(SOCKET targetSocket);

	private:
		void MonitorLoop(std::stop_token st);

		std::atomic<SOCKET> m_mainSocket = INVALID_SOCKET;

		uint16_t m_timeout = 0;
		std::atomic<bool> m_running = false;
		std::promise<void> m_stopSignal;
		std::string m_userId;
		std::atomic<std::chrono::steady_clock::time_point> m_lastActiveTime = std::chrono::steady_clock::now();

		std::atomic<SOCKET> m_socket = INVALID_SOCKET;
		std::jthread m_thread;
	};

	class HeartBeatServer
	{
	public:
		HeartBeatServer(const uint16_t port);
		~HeartBeatServer();

		HeartBeatServer() = delete;
		HeartBeatServer(const HeartBeatServer&) = delete;
		HeartBeatServer(HeartBeatServer&&) = delete;
		HeartBeatServer& operator=(const HeartBeatServer&) = delete;
		HeartBeatServer& operator=(HeartBeatServer&&) = delete;

		bool Start();
		void Stop();

		void SetActiveTime(const std::string& userId);

		void RegisterTargetSocket(const std::string& sessionId, SOCKET targetSocket);

	private:
		void ListenLoop(std::stop_token st);

		uint16_t m_port = 0;
		std::atomic<SOCKET> m_listenSocket = INVALID_SOCKET;

		std::atomic<bool> m_running = false;

		std::mutex m_mutex;	// for m_sessions.
		// Important:
		// HeartBeatSession needs to be wrapped with std::unique_ptr.
		// std::unordered_map might cause re-hash, 
		// then the thread ran by the HeartBeatSession might lose its this pointer.
		std::unordered_map<std::string, std::unique_ptr<HeartBeatSession>> m_sessions;
		std::unordered_map<std::string, SOCKET> m_mainSockets;
		std::jthread m_listenThread;
	};
}
