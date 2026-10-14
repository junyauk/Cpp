#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <WS2tcpip.h>
#include "ChatServer.h"

ChatServer::ChatServer(const std::string& ip, int port)
	: m_port(port)
{}
bool ChatServer::Start()
{
	if (m_running.load()) return false;

	m_hbServer = std::make_unique<HeartBeatServer>(m_port + 1);
	if (!m_hbServer->Start()) return false;

	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenSocket == INVALID_SOCKET) return false;

	sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(m_port) };
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(m_listenSocket.load(), (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		auto s = m_listenSocket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
			return false;
		}
	}
	if (listen(m_listenSocket.load(), SOMAXCONN) == SOCKET_ERROR)
	{
		auto s = m_listenSocket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
			return false;
		}
	}

	m_running.store(true);
	m_thread = std::jthread([this](std::stop_token st)
		{
			this->MonitorLoop(st);
		});

	return true;
}

void ChatServer::Stop()
{
	if (!m_running.load()) return;

	auto s = m_listenSocket.exchange(INVALID_SOCKET);
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

	std::lock_guard<std::mutex> lock(m_mutex);

	for (auto& [id, session] : m_sessions)
	{
		if (session)
		{
			session->Shutdown(SD_SEND);
		}
	}

	m_sessions.clear();

	if (m_hbServer)
	{
		m_hbServer->Stop();
	}
}

void ChatServer::MonitorLoop(std::stop_token st)
{
	while (!st.stop_requested())
	{
		SOCKET clientSocket = accept(m_listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "[Chat Server] Connection failed. Error: " << WSAGetLastError() << std::endl;
			break;
		}

		// Get the ID number and increment for next
		uint64_t idNum = m_nextSessionId.load();

		std::stringstream ss;
		// Build the session ID
		ss << "CS-" << std::setw(4) << std::setfill('0') << idNum;
		std::string sessionId = ss.str();

		// Associate the sessionId with the client socket, and let HBServer use it for creating HBSession
		if (m_hbServer)
		{
			m_hbServer->RegisterTargetSocket(sessionId, clientSocket);
		}

		// Create ChatSession instance and set it with the temp Session ID first
		auto session = std::make_unique<ChatSession>(
			clientSocket,
			sessionId,
			[this](const std::string& sId, const std::string& uId) { return this->onClientAuthorized(sId, uId); },
			[this](const std::string& uId, const std::string& msg) { return this->onMessageReceived(uId, msg); },
			[this](const std::string& uId) {this->onDisconnected(uId); });

		// Remove dead ChatSessions
		{
			// Use lock_guard in a loop, instead of unique_lock with lock/unlock for avoiding warnings
			std::lock_guard<std::mutex> lock(m_mutex);
			std::erase_if(m_sessions, [](const auto& item)
				{
					return !item.second->IsPeerAlive();
				});

			// Set the empty ChatSession with the temp session ID 
			// so that OnClientAuthorized can find it and replace it with the actual user ID
			m_sessions[sessionId] = nullptr;
		}

		// Note:
		// ChatSesion::Start will spawn MonitorLoop thread for start handshaking.
		// It might return before the valid user ID is authorized,
		// But whether if it was authorized doesn't matter.
		// Because asociating the key with the session can be done 
		// regardless of whether it is still the temp one.
		bool success = session->Start();

		if (!success)
		{
			std::cerr << "[Chat Server] Create the chat session failed. Error: " << WSAGetLastError() << std::endl;
			// Remove the temp session from the map
			{
				// Use lock_guard in a loop, instead of unique_lock with lock/unlock for avoiding warnings
				std::lock_guard<std::mutex> lock(m_mutex);
				m_sessions.erase(sessionId);
			}
			// Close the client socket
			closesocket(clientSocket);
			break;
		}

		{
			// Use lock_guard in a loop, instead of unique_lock with lock/unlock for avoiding warnings
			std::lock_guard<std::mutex> lock(m_mutex);
			// The userId might be either the temp one or the valid ID user input, but it doesn't matter.
			// Even if the userId is the same as the temp one, it will be replaced with the valid one by OnClientAuthorized.
			m_sessions[sessionId] = std::move(session);
		}
		// The new session was stored successfully.
		m_nextSessionId.store(idNum + 1);
	}
	m_running.store(false);
}

bool ChatServer::onClientAuthorized(const std::string & sessionId, const std::string & userId)
{
	if (sessionId.empty() || userId.empty()) return false;

	std::lock_guard<std::mutex> lock(m_mutex);

	// Check if the user ID has already been used.
	for (auto& [id, session] : m_sessions)
	{
		if (session && session->GetUserId() == userId)
		{
			return false;	// Already in use.
		}
	}

	// Check if the session ID is valid and the session is available
	auto it = m_sessions.find(sessionId);
	if (it == m_sessions.end() || !it->second) return false;

	// Let Heart Beat Server know that the main connection is active
	if (m_hbServer)
	{
		m_hbServer->SetActiveTime(sessionId);
	}

	// Now ready to let other uses know the user joined the lobby
	std::string message = "[Chat Server] User: " + userId + " joined the lobby.\n";

	for (auto& [id, session] : m_sessions)
	{
		// Note: 
		// nullptr means that the session is still associated with the temp session ID 
		// (not replaced with the valid User ID yet). 
		if (id == sessionId || !session) continue;

		if (session->IsPeerAlive())
		{
			session->SendMessage(message);
		}
	}
	return true;
}

void ChatServer::onMessageReceived(const std::string& sessionId, const std::string& message)
{
	if (sessionId.empty() || message.empty()) return;

	std::lock_guard<std::mutex> lock(m_mutex);

	// Check if the session ID is valid and the session is available
	auto it = m_sessions.find(sessionId);
	if (it == m_sessions.end() || !it->second) return;

	// Let Heart Beat Server know that the main connection is active
	if (m_hbServer)
	{
		m_hbServer->SetActiveTime(sessionId);
	}

	std::string msg = "[User: " + it->second->GetUserId() + "]: " + message;

	for (auto& [id, session] : m_sessions)
	{
		if (id == sessionId || !session) continue;
		if (session->IsPeerAlive())
		{
			session->SendMessage(msg);
		}
	}
}

void ChatServer::onDisconnected(const std::string& sessionId)
{
	if (sessionId.empty()) return;

	std::lock_guard<std::mutex> lock(m_mutex);

	// Check if the session ID is valid and the session is available
	auto it = m_sessions.find(sessionId);
	if (it == m_sessions.end() || !it->second) return;

	// Let users know the user left the lobby
	std::string message = "[Chat Server] User: " + it->second->GetUserId() + " left the lobby.\n";
	for (auto& [id, session] : m_sessions)
	{
		if (id == sessionId || !session) continue;
		if (session->IsPeerAlive())
		{
			session->SendMessage(message);
		}
	}
}
