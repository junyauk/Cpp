#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <WinSock2.h>

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
	void RunLoop();

	// Callback function called from the Win32 thread pool
	// When this function completes, the OS automatically returns the thread to a waiting state 
	// or performs appropriate cleanup.
	static DWORD WINAPI ClientWorkerThread(
		PTP_CALLBACK_INSTANCE instance,	// Pointer to the thread pool callback instance
		PVOID context,					// Pointer to the context data passed to the callback function
		PTP_WORK work);					// Pointer to the work object associated with the callback

	// Handler for console control events (like Ctrl+C)
	static BOOL WINAPI ConsoleCtrlHandler(DWORD dwType);

	// List of client sockets currently connected to the server
	SOCKET m_listeningSocket = INVALID_SOCKET;
	bool m_running = true;

	// Note:
	// A static pointer pointing to the instance itself, 
	// used to bridge to Win32 API callbacks.
	static inline SocketServer* s_instance = nullptr;
};

