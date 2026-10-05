#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <winsock2.h>

// Note:
// This class wraps the followings
// - socket
// - connect
// - send
// - recv
// - closesocket
//
// And also demonstrates the mechanism of socket event using
// - WSACreateEvent : Create an event
// - WSAEventSelect : Associate the event with event type like FD_READ and FD_CLOSE
// - WaitForMultipleObjects : Win32API waiting for multiple events
// - WSAEnumNetworkEvents : Getting the details of the signaled events
// - WSACloseEvent : Close the event

class SocketClient
{
public:
	SocketClient() = default;
	~SocketClient();

	SocketClient(const SocketClient&) = delete;
	SocketClient(SocketClient&&) = delete;
	SocketClient& operator=(const SocketClient&) = delete;
	SocketClient& operator=(SocketClient&&) = delete;

	bool Connect(const std::string& ip, int port);
	void RunEventLoop();
	void Disconnect();
private:
	bool HandleSocketEvent();
	bool HandleInputEvent();

	SOCKET m_socket = INVALID_SOCKET;
	WSAEVENT m_socketEvent = WSA_INVALID_EVENT;
	HANDLE m_stdInput = INVALID_HANDLE_VALUE;
	bool m_running = false;
};
