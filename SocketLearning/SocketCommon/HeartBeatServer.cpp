#include <iostream>
#include "HeartBeat.h"

namespace SocketCommon
{
	HeartBeatServer::HeartBeatServer(const uint16_t port)
		: m_port(port)
	{}

	HeartBeatServer::~HeartBeatServer()
	{
		std::cout << "[HB Server] destructor\n";
		Stop();
	}

	bool HeartBeatServer::Start()
	{
		if (m_running.load()) return false;

		std::cout << "[HB Server] Start ->\n";
		// Socket
		m_listenSocket.store(socket(AF_INET, SOCK_STREAM, 0));
		if (m_listenSocket.load() == INVALID_SOCKET) return false;

		// Bind
		sockaddr_in hint{ .sin_family = AF_INET, .sin_port = m_port };
		hint.sin_addr.S_un.S_addr = INADDR_ANY;

		if ((bind(m_listenSocket.load(), (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) ||
			(listen(m_listenSocket.load(), SOMAXCONN) == SOCKET_ERROR))
		{
			std::cout << "[HB Server] bind or listen failed\n";
			auto s = m_listenSocket.exchange(INVALID_SOCKET);
			if (s != INVALID_SOCKET)
			{
				closesocket(s);
			}

			return false;
		}

		// Start the listening thread
		m_listenThread = std::jthread([this](std::stop_token st)
			{
				this->ListenLoop(st);
			});

		std::cout << "[HB Server] Started HeartBeatServer port: " << m_port << std::endl;

		std::cout << "[HB Server] Start <-\n";
		return true;
	}

	void HeartBeatServer::Stop()
	{
		if (!m_running.load()) return;

		std::cout << "[HB Server] Stop ->\n";
		// Disable the listening socket first, so that accept can return immediately with INVALID_SOCKET
		auto s = m_listenSocket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			shutdown(s, SD_BOTH);
			closesocket(s);
		}

		// Stop the thread
		m_listenThread.request_stop();

		if (m_listenThread.joinable())
		{
			m_listenThread.join();	// Make sure new session is not added anymore
		}

		// Each session owns a socket and a thread, they will be terminated automatically
		m_sessions.clear();

		std::cout << "[HB Server] Stop <-\n";
	}

	void HeartBeatServer::ListenLoop(std::stop_token st)
	{
		std::cout << "[HB Server] ListenLoop ->\n";
		m_running.store(true);
		while (!st.stop_requested())
		{
			std::cout << "[HB Sever] loop top\n";
			sockaddr_in hint;
			int sockAddrSize = sizeof(hint);
			SOCKET clientSocket = accept(m_listenSocket.load(), (sockaddr*)&hint, &sockAddrSize);
			if (clientSocket == INVALID_SOCKET) break;
			std::cout << "[HB Sever] accepted\n";

			char name[128];
			ZeroMemory(name, sizeof(name));

			// Handshake, the first recv must be sessionId
			int bytesReceived = recv(clientSocket, name, sizeof(name) - 1, 0);
			if (bytesReceived <= 0)
			{
				std::cout << "[HB Server] Recv (Handshake) failed." << std::endl;
				closesocket(clientSocket);
				continue;
			}
			std::string sessionId(name, bytesReceived);

			std::lock_guard<std::mutex> lock(m_mutex);

			std::erase_if(m_sessions, [](const auto& item)
				{
					return !item.second->IsPeerAlive();
				});

			// Create Heart Beat session
			SOCKET mainSocket;
			auto it = m_mainSockets.find(sessionId);
			if (it == m_mainSockets.end())
			{
				std::cerr << "[HB Server] The main socket associated with the session ID was not found." << std::endl;
				mainSocket = m_listenSocket.load();
			}
			else
			{
				mainSocket = it->second;
			}

			auto session = std::make_unique<HeartBeatSession>(clientSocket, mainSocket, sessionId);
			session->Start();	// default 15 sec
			m_sessions[sessionId] = std::move(session);
		}
		m_running.store(false);
		std::cout << "[HB Server] ListenLoop <-\n";
	}

	void HeartBeatServer::SetActiveTime(const std::string& userId)
	{
		std::cout << "[HB Server] SetActiveTime : " << userId << " ->\n";
		auto it = m_sessions.find(userId);
		if (it != m_sessions.end())
		{
			it->second->SetActiveTime();
		}
		else
		{
			std::cout << "[HB Server] The specified user " << userId << " was not found.\n";
		}
		std::cout << "[HB Server] SetActiveTime <-\n";
	}

	void SocketCommon::HeartBeatServer::RegisterTargetSocket(const std::string& sessionId, SOCKET targetSocket)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_mainSockets[sessionId] = targetSocket;
	}
}

