#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

class SocketServer
{
public:
	static SocketServer& GetInstance();
	SocketServer(const SocketServer&) = delete;
	SocketServer(SocketServer&&) = delete;
	SocketServer& operator=(const SocketServer&) = delete;
	SocketServer& operator=(SocketServer&&) = delete;

	bool Start(const std::string& ip, const int port);
	void Stop();

private:
	SocketServer() = default;
	~SocketServer();

	void RunLoop();
	static bool WINAPI ConsoleCtrlHandler(DWORD ctrlType);

	void HandleWebRequest(SOCKET clientSocket, const std::string& request);

	SOCKET m_listenSocket = INVALID_SOCKET;
	std::vector<SOCKET> m_clientSockets;
	bool m_running = false;

	static inline  SocketServer* m_instance = nullptr;
};

