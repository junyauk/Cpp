#pragma once
// Note:
// Windows.h will use the old version of winsock, so WIN32_LEAN_AND_MEAN avoids this problem
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "SocketServer.h"

struct ClientContext
{
	SOCKET socket;
	std::string ip;

	~ClientContext()
	{
		if (socket != INVALID_SOCKET)
		{
			closesocket(socket);
			std::cout << "[RAII] The socket and memory are released. IP: " << ip << std::endl;
		}
	}
};

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
	s_instance = this;
	if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE))
	{
		std::cerr << "Failed to register the control handler." << std::endl;
		return false;
	}

	m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listeningSocket == INVALID_SOCKET) return false;

	int opt = 1;
	setsockopt(m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt));

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(
		m_listeningSocket,
		(sockaddr*)&hint,
		sizeof(hint)) == SOCKET_ERROR ||
		listen(m_listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "[Server] Binding failed." << port << std::endl;
		Stop();
		return false;
	}

	std::cout << "[Server] Started Port: " << port << std::endl;
	RunLoop();
	return true;
}

void SocketServer::Stop()
{
	m_running = false;
	if (m_listeningSocket != INVALID_SOCKET)
	{
		// First, cut off the communication channel to forcibly release the main thread 
		// that is blocked at `accept()`.
		shutdown(m_listeningSocket, SD_BOTH);

		closesocket(m_listeningSocket);
		m_listeningSocket = INVALID_SOCKET;
	}
}

void SocketServer::RunLoop()
{
	while (m_running)
	{
		sockaddr_in clientInfo;
		int clientSize = sizeof(clientInfo);
		SOCKET clientSocket = accept(m_listeningSocket, (sockaddr*)&clientInfo, &clientSize);
		if (clientSocket == INVALID_SOCKET)
		{
			if (!m_running)
			{
				std::cout << "[Server] The wait for accept was cancelled due to a termination request." << std::endl;
				break;
			}
		}

		char clientIp[256]{};
		inet_ntop(
			AF_INET,
			&clientInfo.sin_addr,
			clientIp,
			sizeof(clientIp));
		std::cout << "[Server] Connecting client IP: " << clientIp << std::endl;

		auto ctx = std::make_unique<ClientContext>(clientSocket, std::string(clientIp));
		PVOID rawContext = reinterpret_cast<PVOID>(ctx.release());

		if (!TrySubmitThreadpoolCallback(
			reinterpret_cast<PTP_SIMPLE_CALLBACK>(ClientWorkerThread),
			rawContext,
			nullptr))
		{
			// Freeing the ClientContext and close the socket
			std::unique_ptr<ClientContext> rescue(reinterpret_cast<ClientContext*>(rawContext));
		}
	}
}

// Callback function called from the Win32 thread pool
// When this function completes, the OS automatically returns the thread to a waiting state 
// or performs appropriate cleanup.
DWORD WINAPI SocketServer::ClientWorkerThread(
	PTP_CALLBACK_INSTANCE instance,
	PVOID context,
	PTP_WORK work)
{
	std::unique_ptr<ClientContext> ctx(reinterpret_cast<ClientContext*>(context));
	if (!ctx) return 0;

	char buffer[4096];
	while (s_instance && s_instance->m_running)
	{
		ZeroMemory(buffer, 4096);
		int bytesReceived = recv(ctx->socket, buffer, 4096, 0);
		if (bytesReceived <= 0) break;

		std::string receivedMsg(buffer, 0, bytesReceived);
		if (receivedMsg == "exit") break;

		std::cout << "[Server] Received message: " << receivedMsg << std::endl;

		std::string response = "Echo: " + receivedMsg;
		send(ctx->socket, response.c_str(), static_cast<int>(response.size()), 0);
	}
	return 0;
}

BOOL WINAPI SocketServer::ConsoleCtrlHandler(DWORD dwType)
{
	std::cout << "\n[Handler] Ctrl + C was detected." << std::endl;
	if (dwType == CTRL_C_EVENT || dwType == CTRL_CLOSE_EVENT)
	{
		std::cout << "\n[Handler] Termination signal detected. Stopping class instance." << std::endl;
		s_instance->Stop();

		// Important: 
		// Briefly pause this callback thread to allow the main thread
		// to reach the end of main() (where WinsockManager is released) and exit gracefully.
		Sleep(100);

		return TRUE;
	}
	return FALSE;
}

