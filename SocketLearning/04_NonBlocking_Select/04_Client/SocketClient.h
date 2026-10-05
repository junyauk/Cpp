#pragma once
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <thread>

class SocketClient
{
public:
	// Constructor and destructor
	SocketClient() = default;
	~SocketClient();

	// Delete copy and move constructors and operators
	SocketClient(const SocketClient&) = delete;
	SocketClient(SocketClient&&) = delete;
	SocketClient& operator=(const SocketClient&) = delete;
	SocketClient& operator=(SocketClient&&) = delete;

	// Connect to the server at the specified IP and port
	bool Connect(const std::string& ip, const int port);
	// Run the main loop for sending and receiving messages
	void RunLoop();
	// Disconnect from the server and clean up resources
	void Disconnect();

private:
	// Loop that continuously receives messages from the server
	void ReceiveLoop(std::stop_token st);

	// The socket used for communication with the server
	SOCKET m_socket = INVALID_SOCKET;
	bool m_running = true;
	// Thread for receiving messages from the server
	std::jthread m_receiveThread;
};
