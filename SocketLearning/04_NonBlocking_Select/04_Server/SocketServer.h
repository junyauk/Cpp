#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <Windows.h>
#include <vector>

class SocketServer
{
public:
	// Singleton pattern: Get the single instance of SocketServer
	static SocketServer& GetInstance();

	// Delete copy and move constructors and operators
	SocketServer(const SocketServer&) = delete;
	SocketServer(SocketServer&&) = delete;
	SocketServer& operator=(const SocketServer&) = delete;
	SocketServer& operator=(SocketServer&&) = delete;

	// Start the server on the specified port
	bool Start(int port);
	// Stop the server and clean up resources
	void Stop();

private:
	// Private constructor and destructor to enforce singleton pattern
	SocketServer() = default;
	~SocketServer();

	// Main loop that runs the server, accepting and handling client connections
	void RunEventLoop();
	// Handler for console control events (like Ctrl+C)
	static bool WINAPI ConsoleCtrlHandler(DWORD ctrlType);

	// The listening socket for incoming client connections
	SOCKET m_listeningSocket = INVALID_SOCKET;
	// List of client sockets currently connected to the server
	std::vector<SOCKET> m_clientSockets;
	bool m_running = true;

	// Note:
	// A static pointer pointing to the instance itself,
	// used to bridge to Win32 API callbacks.
	static inline SocketServer* s_instance = nullptr;
};

