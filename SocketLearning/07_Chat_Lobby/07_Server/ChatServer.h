#pragma once
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include "HeartBeat.h"
#include "ChatSession.h"

using namespace SocketCommon;

class ChatServer
{
public:
	ChatServer(const std::string& ip, int port);
	~ChatServer() { Stop(); }

	ChatServer() = delete;
	ChatServer(const ChatServer&) = delete;
	ChatServer(ChatServer&&) = delete;
	ChatServer& operator=(const ChatServer&) = delete;
	ChatServer& operator=(ChatServer&&) = delete;

	bool Start();
	void Stop();

private:
	void MonitorLoop(std::stop_token st);

	bool onClientAuthorized(const std::string& sessionId, const std::string& userId);
	void onMessageReceived(const std::string& sessionId, const std::string& message);
	void onDisconnected(const std::string& userId);

	std::atomic<uint64_t> m_nextSessionId = 1;

	const uint16_t m_port;
	std::atomic<SOCKET> m_listenSocket;
	std::atomic<bool> m_running = false;
	std::unique_ptr<HeartBeatServer> m_hbServer;

	std::mutex m_mutex;
	std::unordered_map<std::string, std::unique_ptr<ChatSession>> m_sessions;

	std::jthread m_thread;
};

