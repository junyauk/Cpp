#pragma once
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <functional>

class ChatSession
{
public:
	ChatSession(
		SOCKET clientSocket, 
		const std::string& sessionId,
		std::function<bool(const std::string&, const std::string&)> onAuthorized,
		std::function<void(const std::string&, const std::string&)> onMessageReceived,
		std::function<void(const std::string&)> onDisconnected);
	~ChatSession();

	ChatSession() = delete;
	ChatSession(const ChatSession&) = delete;
	ChatSession(ChatSession&&) = delete;
	ChatSession& operator=(const ChatSession&) = delete;
	ChatSession& operator=(ChatSession&&) = delete;

	bool Start();
	void Shutdown(int how);
	void Stop();

	bool IsPeerAlive() const { return m_running.load(); }
	const std::string& GetUserId() const { return m_userId; }

	bool SendMessage(const std::string& message) const;

private:
	enum class SessionState
	{
		Handshaking,
		Chatting
	};
	SessionState m_state = SessionState::Handshaking;

	void MonitorLoop(std::stop_token st);

	bool HandleHandshake(const std::string& newUserId);
	bool HandleLobyMessage(const std::string& message);

	std::function<bool(const std::string&, const std::string&)> m_onAuthorized;
	std::function<void(const std::string&, const std::string&)> m_onMessageReceived;
	std::function<void(const std::string&)> m_onDisconnected;

	const std::string m_sessionId;
	std::string m_userId;
	std::atomic<SOCKET> m_socket = INVALID_SOCKET;

	std::atomic<bool> m_running = false;

	std::jthread m_thread;
};
