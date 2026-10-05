#pragma comment(lib, "ws2_32.lib")

#include "SocketClient.h"
#include <WS2tcpip.h>
#include <conio.h>

SocketClient::~SocketClient()
{
	Disconnect();
}

bool SocketClient::Connect(const std::string& ip, const int port)
{
	// 1. Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) return false;

	// 2. Setting up the sockaddr_in structure for the server address
	sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(port) };
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	std::cout << "[Client] Connecting to the single-threaded multiplexing server..." << "\n> ";

	// 3. Connect to the server
	if (connect(m_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		std::cerr << "Failed connection. Error: " << WSAGetLastError() << std::endl;
		closesocket(m_socket);
		return false;
	}
	m_running = true;

	// 4. Start the receive loop in a separate thread
	m_receiveThread = std::jthread([this](std::stop_token st)
		{
			this->ReceiveLoop(st);
		});

	return true;
}

void SocketClient::RunLoop()
{
	std::string userInput;

	while (m_running)
	{
		// Prompt the user for input
		std::getline(std::cin, userInput);

		// The ReceiveLoop thread may have set m_running to false 
		// if the server disconnected, so we check it here.
		if (!m_running) break;
		if (userInput.empty())
		{
			std::cout << "> ";
			std::cout.flush();
			continue;
		}

		if (userInput == "exit")
		{
			m_running = false;
			break;
		}

		int sendResult = send(m_socket, userInput.c_str(), static_cast<int>(userInput.size()), 0);
		if (sendResult == SOCKET_ERROR)
		{
			std::cerr << "[Client] Failed sending. Error: " << WSAGetLastError() << std::endl;
			break;
		}
	}

	Disconnect();
}

void SocketClient::Disconnect()
{
	m_running = false;

	if (m_receiveThread.joinable())
	{
		m_receiveThread.request_stop();
	}
		
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

void SocketClient::ReceiveLoop(std::stop_token st)
{
	char buffer[4096];

	while (m_running && !st.stop_requested())
	{
		ZeroMemory(buffer, sizeof(buffer));
		
		int bytesReceived = recv(m_socket, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0)
		{
			if (m_running)
			{
				std::cout << "\n[Client] Disconnected by the server." << std::endl;

				m_running = false;

				// To jolt the main thread's std::getline out of its wait (rescue it),
				// we close and destroy our own socket at the fundamental level.
				closesocket(m_socket);
				m_socket = INVALID_SOCKET;

				std::cout << "[Client] Press Enter to exit..." << std::endl;
				std::cout.flush();
			}
			break;
		}

		std::string response(buffer, 0, bytesReceived);
		std::cout << "\n[Client] Server response: Echo: " << response << "\n> ";
		std::cout.flush();
	}
}

