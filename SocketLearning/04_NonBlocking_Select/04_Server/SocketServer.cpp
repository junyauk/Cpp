#pragma comment(lib, "ws2_32.lib")
#include "SocketServer.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <WS2tcpip.h>
#include <windows.h>

// Note:
// select: Monitors multiple sockets for activity. 
// It blocks until one or more sockets are ready for reading, writing, or have an error.
// The select function is used to implement non-blocking I/O by allowing the program 
// to wait for events on multiple sockets without blocking the entire program.
// - fd_set:		A data structure used to represent a set of sockets. 
//					It is used with the select function to monitor multiple sockets for activity.
// - timeval:		A structure that specifies the maximum time to wait for an event in the select function. 
//					It contains two fields: tv_sec (seconds) and tv_usec (microseconds).
// - setsockopt:	Configures options for a socket, 
//					such as enabling address reuse (SO_REUSEADDR) to allow the socket 
//					to bind to an address that is already in use.
// - ioctlsocket:	Configures a socket to operate in non-blocking mode. 
//					When a socket is in non-blocking mode, operations like accept() 
//					and recv() return immediately instead of waiting for an event.
// 
// Macros for non-blocking sockets are defined in <winsock2.h> and <ws2tcpip.h>.
// - FD_ZERO:	Initializes a socket set to an empty state.
// - FD_SET:	Adds a socket to the set.
// - FD_ISSET:	Checks if a socket is part of the set (indicating activity).
// - FD_CLR:	Removes a socket from the set.

SocketServer& SocketServer::GetInstance()
{
	static SocketServer instance;
	return instance;
}

SocketServer::~SocketServer()
{
	Stop();
}

bool SocketServer::Start(int port)
{
	// Registering a handler for handling CTRL + C
	s_instance = this;
	if (!SetConsoleCtrlHandler(
		reinterpret_cast<PHANDLER_ROUTINE>(SocketServer::ConsoleCtrlHandler),
		TRUE)) return false;

	// Create a socket for listening
	m_listeningSocket = socket(
		AF_INET,
		SOCK_STREAM,
		0);
	if (m_listeningSocket == INVALID_SOCKET) return false;

	int opt = 1;
	setsockopt(
		m_listeningSocket,				// Target socket
		SOL_SOCKET,						// Socket level option (SOL_SOCKET: socket-level option, IPPROTO_TCP: TCP-level option, IPPROTO_UDP: UDP-level option)
		SO_REUSEADDR,					// Option to allow address reuse
		reinterpret_cast<char*>(&opt),	// Pointer to the option value
		sizeof(opt));					// Size of the option value

	// Important: 
	// Switch the listening socket to "non-blocking mode."
	// This ensures that when accept() is called, 
	// the program does not freeze if no client is present; 
	// instead, it immediately returns an error and proceeds.
	ULONG mode = 1;
	ioctlsocket(
		m_listeningSocket,
		FIONBIO,
		&mode);

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(
		m_listeningSocket, 
		(sockaddr*)&hint,
		sizeof(hint)) == SOCKET_ERROR ||

		listen(
			m_listeningSocket,
			SOMAXCONN) == SOCKET_ERROR)
	{
		Stop();
		return false;
	}

	std::cout << "[Server] Started Server. Port: " << port << std::endl;
	RunEventLoop();
	return true;
}

void SocketServer::Stop()
{
	m_running = false;
	if (m_listeningSocket != INVALID_SOCKET)
	{
		// Important:
		// Shutdown the listening socket to stop accepting new connections.
		// This is necessary to ensure that the select() call in the event loop can exit gracefully.
		// SD_BOTH: Disables both sending and receiving on the socket.
		// This will cause any blocking calls (like accept) to return with an error, 
		// allowing the server to clean up.
		//
		// Note: 
		// This is a critical step to ensure that the server can shut down cleanly 
		// without leaving any resources hanging.
		// After shutdown, the socket can be closed with closesocket().
		// This is especially important in a non-blocking server 
		// where select() is used to monitor multiple sockets.
		// If shutdown is not called, the server may hang on select() 
		// or accept() calls, preventing a clean exit.
		// In summary, shutdown() is used to signal the end of communication on the socket,
		// allowing the server to exit its event loop and clean up resources properly.
		// This is a common pattern in network programming to ensure that resources are released properly.
		shutdown(m_listeningSocket, SD_BOTH);
		closesocket(m_listeningSocket);
		m_listeningSocket = INVALID_SOCKET;
	}

	for (SOCKET s : m_clientSockets)
	{
		shutdown(s, SD_SEND);
		closesocket(s);
	}
	m_clientSockets.clear();
}

void SocketServer::RunEventLoop()
{
	while (m_running)
	{
		// 1. Prepare and initialize an `fd_set`, a "socket monitoring set" (or "bag").
		fd_set readfds;
		FD_ZERO(&readfds);

		// 2. Insert a "listening socket" into the monitoring network 
		// (to monitor for incoming connections).
		FD_SET(m_listeningSocket, &readfds);

		// 3. Add the sockets of all currently connected clients to the monitoring network 
		// (to track whether messages have been delivered).
		for (SOCKET s : m_clientSockets)
		{
			FD_SET(s, &readfds);
		}

		// Timeout setting (if nothing is received from anyone after one second, 
		// exit `select` and return to the beginning of the loop)
		timeval timeout{ .tv_sec = 1, .tv_usec = 0 };

		// 4. ★Request a batch check from the OS kernel (select)
		// Execution pauses here until there is a change 
		// (such as a connection request or data reception) in *any one* of the sockets in the set.
		int socketCount = select(
			0,
			&readfds,
			nullptr,
			nullptr,
			&timeout);

		if (socketCount <= 0)
		{
			// If timeout or error occurs, return to the beginning of the loop 
			// and check the flag and rebuild the network
			continue;
		}

		// 5. Breakdown Analysis: 
		// [Pattern A] When a new customer (connection request) arrives
		if (FD_ISSET(m_listeningSocket, &readfds))
		{
			sockaddr_in clientInfo;
			int clientSize = sizeof(clientInfo);
			SOCKET clientSocket = accept(m_listeningSocket, (sockaddr*)&clientInfo, &clientSize);
			if (clientSocket != INVALID_SOCKET)
			{
				// Set the client socket to non-blocking mode as well.
				ULONG clientMode = 1;
				ioctlsocket(
					clientSocket,	// Target socket
					FIONBIO,		// Command to set non-blocking mode
					&clientMode);	// 1: Enable non-blocking mode, 0: Disable non-blocking mode

				char clientIp[256]{};
				inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, sizeof(clientIp));
				std::cout << "[Server] Accepted a new connection: " << clientIp << std::endl;

				// Management is complete simply by adding it to the list (do not create a thread!)
				m_clientSockets.push_back(clientSocket);
			}
		}

		// 6. Breakdown Investigation: 
		// [Pattern B] Data received from (or disconnection by) an existing client
		// Use C++20/23's std::erase_if to safely remove (clean up) sockets 
		// with receive errors or disconnections from the list in-place.
		std::erase_if(m_clientSockets, [&readfds](SOCKET s)
			{
				// Check if there was any activity (firing) on ​​this socket.
				if (FD_ISSET(s, &readfds))
				{
					char buffer[4096];
					ZeroMemory(buffer, sizeof(buffer));
					int bytesReceived = recv(s, buffer, sizeof(buffer), 0);

					if (bytesReceived <= 0)
					{
						// Disconnected or error
						std::cout << "[Server] The client has disconnected. Cleaning up socket resources." << std::endl;
						closesocket(s);
						return true;	// Remove the socket automatically from the vector
					}

					std::string receivedMsg(buffer, 0, bytesReceived);
					std::cout << "[Server] Reception successful on 1 thread : " << receivedMsg << std::endl;

					if (receivedMsg == "exit")
					{
						closesocket(s);
						return true;	// Remove the socket automatically from the vector
					}

					std::string response = "Echo: " + receivedMsg;
					send(s, response.c_str(), static_cast<int>(response.size()), 0);
				}
				return false;
			});
	}
}

bool WINAPI SocketServer::ConsoleCtrlHandler(DWORD ctrlType)
{
	if ((ctrlType == CTRL_C_EVENT || ctrlType == CTRL_CLOSE_EVENT) && s_instance)
	{
		std::cout << "Exit request detected. Shutting down the single-threaded server safely." << std::endl;
		s_instance->Stop();
		Sleep(100);
		return true;
	}
	return false;
}
