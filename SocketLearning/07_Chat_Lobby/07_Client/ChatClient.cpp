#include <iostream>
#include <WS2tcpip.h>
#include <string_view>
#include "ChatClient.h"

ChatClient::ChatClient(const std::string& ip, const int port)
	: m_ip(ip)
	, m_port(port)
{}

ChatClient::~ChatClient()
{}

bool ChatClient::Connect()
{
	if (m_running.load()) return false;

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) return false;

	sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(m_port) };
	inet_pton(AF_INET, m_ip.c_str(), &hint.sin_addr);
	if (connect(m_socket, (sockaddr*)(&hint), sizeof(hint)) == SOCKET_ERROR)
	{
		std::cout << "[ChatClient] Connection failed. Error: " << WSAGetLastError() << std::endl;
		auto s = m_socket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
		return false;
	}

	// Handshaking to get the session ID
	char buffer[1024];
	int bytes = recv(m_socket, buffer, sizeof(buffer), 0);
	if (bytes == 0)
	{
		std::cout << "[ChatClient] Disconnected from the server.\n";
		auto s = m_socket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
		return false;
	}
	else if (bytes < 0)
	{
		std::cout << "[ChatClient] Handshaking failed. Error: " << WSAGetLastError() << std::endl;
		auto s = m_socket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
		return false;
	}

	// Store the session ID
	m_sessionId = std::string(buffer, bytes);
	// Start HeartBeating
	m_hbClient = std::make_unique<HeartBeatClient>(m_socket, m_ip, m_port + 1, m_sessionId);
	m_hbClient->Start();

	// Spawn the receiving loop
	m_running.store(true);
	m_thread = std::jthread([this](std::stop_token st)
		{
			this->ReceiveLoop(st);
		});

	return true;
}

void ChatClient::Disconnect()
{
	if (!m_running.load()) return;

	SOCKET s = m_socket.load();
	if (s != INVALID_SOCKET)
	{
		shutdown(s, SD_SEND);	// ChatSession will receive 0 bytes
	}

	m_thread.request_stop();

	if (m_thread.joinable())
	{
		m_thread.join();
	}

	if (m_hbClient)
	{
		m_hbClient->Stop();
	}

	s = m_socket.exchange(INVALID_SOCKET);
	if (s != INVALID_SOCKET)
	{
		closesocket(s);
	}
}

bool ChatClient::SendMessage(const std::string & message)
{
	if (m_socket.load() == INVALID_SOCKET) return false;

	if (!m_hbClient->IsPeerAlive()) return false;

	if (send(m_socket.load(), message.c_str(), static_cast<int>(message.size()), 0) == SOCKET_ERROR)
	{
		std::cout << "[ChatClient] Sending the message failed. Error: " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}

void ChatClient::ReceiveLoop(std::stop_token st)
{
	char buffer[4096];

	while (!st.stop_requested())
	{
		ZeroMemory(buffer, sizeof(buffer));

		int bytes = recv(m_socket, buffer, sizeof(buffer), 0);	// recv will block until received a message
		if (bytes == 0)
		{
			std::cout << "[ChatClient] Disconnected from the server. Please press Enter key.\n" << std::flush;
			break;
		}
		else if (bytes < 0)
		{
			int err = WSAGetLastError();
			if (err == WSAECONNRESET)
			{
				std::cout << "[ChatClient] Server forcibly terminated. Please press Enter key.\n" << std::flush;

			}
			else if (err == WSAESHUTDOWN)
			{
				std::cout << "[ChatClient] Connection error occurred. Error: " << err << std::endl;
			}
			break;
		}

		// Expect the message format is something like this.
		// For the 1st time...
		//   "[ChatServer] Please input your user ID: "
		// After authorized...
		//   "[userid] blah blah blah..."

		std::cout << std::string(buffer, bytes) << std::endl;
		std::cout << "> ";
		std::cout.flush();
	}
	m_running.store(false);

	if (!st.stop_requested())
	{
		// Disconnected
		auto s = m_socket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
	}
}
