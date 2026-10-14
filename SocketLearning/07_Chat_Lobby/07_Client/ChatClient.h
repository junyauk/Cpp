#pragma once
#include <WinSock2.h>
#include <string>
#include <thread>
#include "HeartBeat.h"

using namespace SocketCommon;

class ChatClient
{
public:
	ChatClient(const std::string& ip, const int port);
	~ChatClient();

	ChatClient() = delete;
	ChatClient(const ChatClient&) = delete;
	ChatClient(ChatClient&&) = delete;
	ChatClient& operator=(const ChatClient&) = delete;
	ChatClient& operator=(ChatClient&&) = delete;

	bool Connect();
	void Disconnect();

	bool SendMessage(const std::string& message);
	bool IsRunning() const { return m_running.load(); }

private:
	void ReceiveLoop(std::stop_token st);

	std::atomic<SOCKET> m_socket;
	std::unique_ptr<HeartBeatClient> m_hbClient;

	const std::string m_ip;
	const int m_port = 0;
	const std::string m_userId;
	std::string m_sessionId;

	std::atomic<bool> m_running = false;
	std::jthread m_thread;
};
