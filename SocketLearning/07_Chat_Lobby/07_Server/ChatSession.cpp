#include <iostream>
#include "ChatSession.h"

ChatSession::ChatSession(
	SOCKET clientSocket, 
	const std::string& sessionId, 
	std::function<bool(const std::string&, const std::string&)> onAuthorized, 
	std::function<void(const std::string&, const std::string&)> onMessageReceived, 
	std::function<void(const std::string&)> onDisconnected)
	: m_sessionId(sessionId)
	, m_socket(clientSocket)
	, m_onAuthorized(onAuthorized)
	, m_onMessageReceived(onMessageReceived)
	, m_onDisconnected(onDisconnected)
{}


ChatSession::~ChatSession()
{
	Stop();
}

bool ChatSession::Start()
{
	if (m_running.load()) return false;

	if (!SendMessage(m_sessionId)) return false;

	m_running.store(true);

	m_thread = std::jthread([this](std::stop_token st)
		{
			this->MonitorLoop(st);
		});
	return true;
}

void ChatSession::Shutdown(int how)
{
	m_onDisconnected = nullptr;

	SOCKET s = m_socket.load();
	if (s != INVALID_SOCKET)
	{
		shutdown(s, how);
	}
}

void ChatSession::Stop()
{
	if (!m_running.load()) return;

	auto s = m_socket.exchange(INVALID_SOCKET);
	if (s != INVALID_SOCKET)
	{
		shutdown(s, SD_BOTH);
		closesocket(s);
	}

	m_thread.request_stop();

	if (m_thread.joinable())
	{
		m_thread.join();
	}
}

bool ChatSession::SendMessage(const std::string& message) const
{
	if (send(m_socket, message.c_str(), static_cast<int>(message.size()), 0) == SOCKET_ERROR)
	{
		std::cerr << "[ChatSession] Sending message [ " << message << "] to " << m_userId << " failed. Error: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

void ChatSession::MonitorLoop(std::stop_token st)
{
	const std::string InputUserId = "[ChatServer] Please input your user ID: "; // Send this message as ChatServer

	if (!SendMessage(InputUserId))
	{
		m_running.store(false);
		return;
	}

	char buffer[4096];
	while (!st.stop_requested())
	{
		ZeroMemory(buffer, sizeof(buffer));

		int bytes = recv(m_socket, buffer, sizeof(buffer), 0);
		if (bytes == 0)
		{
			// "exit" was detected.
			std::cout << "[ChatSession] Client: " << m_userId << "left the lobby\n";
			break;
		}
		else if (bytes < 0)
		{
			std::cerr << "[ChatSession] Receiving message failed. Error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::string message(buffer, bytes);


		if (m_state == SessionState::Handshaking)
		{
			if (!HandleHandshake(message)) break;
		}
		else
		{
			if (!HandleLobyMessage(message)) break;
		}
	}
	m_running.store(false);

	auto s = m_socket.exchange(INVALID_SOCKET);
	if (s != INVALID_SOCKET)
	{
		closesocket(s);
	}

	if (m_onDisconnected)
	{
		m_onDisconnected(m_sessionId);
	}
}

bool ChatSession::HandleHandshake(const std::string & newUserId)
{
	if (newUserId.empty()) return true;	// Will not happen though

	if (!m_onAuthorized(m_sessionId, newUserId))
	{
		if (!SendMessage("[ChatServer] The specified name [ " + newUserId + " ] is already used.\nPlease input your user ID: "))
		{
			return false;	// Finishing loop
		}
		return true;	// Keep running loop
	}

	// Authorized with the userId (replacing the temporaly sessionId with the new User Id
	m_userId = newUserId;
	m_state = SessionState::Chatting;	// Next phase

	// Authorized successed.
	SendMessage("[Chat Server] Welcome to the chat lobby, " + m_userId + "!\n");
	return true;	// Keep running loop with the next phase
}

bool ChatSession::HandleLobyMessage(const std::string & message)
{
	if (message.empty()) return true; // Will not happen though

	if (message == "exit")
	{
		m_running.store(false);
		return false;	// Finishing loop
	}

	if (m_onMessageReceived)
	{
		m_onMessageReceived(m_sessionId, message);
	}
	return true; // Sent the message, keep running loop
}
