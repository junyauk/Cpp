#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "winsockmanager.h"

using namespace SocketCommon;

int main()
{
	// 0. Call WSAStartup() to initialize Winsock (Using the Common Library "WinsockManager" class)
	WinsockManager winsock;
	if (!winsock.IsInitialized()) return -1;

	std::cout << "[Server] starting..." << std::endl;

	// ---------------------------------------------------------------------------
	// 1. Socket
	// Create a socket for listening (IPv4, stream communication/TCP, automatic protocol)
	SOCKET listeningSocket = socket(
		AF_INET,		// Address family [AF_INET: IPv4, AF_INET6: IPv6, AF_BTH: Bluetooth (Windows only)]
		SOCK_STREAM,	// Socket Type [SOCK_STREAM (data guaranteed) , SOCK_DGRM(like packet, the order is not guaranteed)
		0);				// Protocol [0: auto (recommended), IPPROTO_TCP: TCP/IP, IPPROTO_UDP: UDP]
	if (listeningSocket == INVALID_SOCKET) return -1;

	// ---------------------------------------------------------------------------
	// 2. Bind
	// Configure the server IP address and port number (preparing bind information)
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(
		listeningSocket,				// Socket handle
		(sockaddr*)&hint,				// IP address and port
		sizeof(hint)) == SOCKET_ERROR)	// Bind the socket to the specified IP address and port number
	{
		closesocket(listeningSocket);
		return -1;
	}

	// ---------------------------------------------------------------------------
	// 3. Listen
	// Start listening for incoming connections (SOMAXCONN: maximum number of pending connections)
	if (listen(
		listeningSocket,				// Socket handle
		SOMAXCONN) == SOCKET_ERROR)		// Start listening for incoming connections (SOMAXCONN: maximum number of pending connections)
	{
		closesocket(listeningSocket);
		return -1;
	}

	std::cout << "[Server] waiting for a connection on port 54000..." << std::endl;

	// ---------------------------------------------------------------------------
	// 4. Accept
	// Accept a connection from a client (blocking call)
	sockaddr_in clientInfo;
	int clientSize = sizeof(clientInfo);
	SOCKET clientSocket = accept(
		listeningSocket,		// Socket handle
		(sockaddr*)&clientInfo,	// Client address information
		&clientSize);			// Size of the client address information structure
	if (clientSocket == INVALID_SOCKET)
	{
		closesocket(listeningSocket);
		return -1;
	}

	// Retrieve the client's IP address and display it
	char clientIp[256];
	ZeroMemory(clientIp, 256);
	inet_ntop(
		AF_INET,				// Address family (IPv4)
		&clientInfo.sin_addr,	// Pointer to the client's IP address
		clientIp,				// Buffer to store the string representation of the IP address
		256);
	std::cout << "[Server] client connected IP: " << clientIp << std::endl;

	// ---------------------------------------------------------------------------
	// Communication Loop
	char buffer[4096];
	while (true)
	{
		ZeroMemory(buffer, 4096);

		// ----------------------------------------------------------------------------
		// 5. Receive
		// Receive data from the client (blocking call)
		int bytesReceived = recv(
			clientSocket,	// Socket handle
			buffer,			// Buffer to store received data
			4096,			// Size of the buffer
			0);				// Flags (0: no special flags)

		if (bytesReceived == SOCKET_ERROR)
		{
			// The app crashes or the connection is lost
			std::cerr << "[Server] A reception error occurred. The connection was forcibly terminated. Error: "
				<< WSAGetLastError() << std::endl;
			break;
		}

		if (bytesReceived == 0)
		{
			// If the app calls `closesocket()` and performs a graceful disconnection procedure 
			// (sending a FIN packet)
			std::cerr << "[Server] The client disconnected normally (connection closed)." << std::endl;
			break;
		}

		// Retrieve received data as a string.
		std::string receivedMsg(buffer, 0, bytesReceived);
		std::cout << "[Server] Received: " << receivedMsg << std::endl;

		// If "exit" is received from the client, exit the loop and proceed to the termination process.
		if (receivedMsg == "exit")
		{
			std::cout << "[Server] Exit command received." << std::endl;
			break;
		}

		// ---------------------------------------------------------------------------
		// 6. Send
		// Send the received data back to the client (echo)
		std::string response = "Echo: " + receivedMsg;
		send(
			clientSocket,						// Socket handle
			response.c_str(),					// Buffer containing the data to send
			static_cast<int>(response.size()),	// Size of the data to send
			0);									// Flags (0: no special flags)
	}

	// Cleanup
	closesocket(clientSocket);
	closesocket(listeningSocket);
	return 0;
}
