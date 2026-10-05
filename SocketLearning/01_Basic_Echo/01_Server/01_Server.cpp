#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "WinsockManager.h"

using namespace SocketCommon;

// Note:
// 
// This file demonstrates how to use Socket as server with minimum code.
// The following functions are essential.
// 
// 0. WSAStartup() : Initialize Winsock (Using the Common Library "WinsockManager" class)
// 1. socket() : Create the service window
// 2. bind() : Bind the port number
// 3. listen() : Tell the OS to start listening.
// 4. accept() : Wait for a client to connect, and create a new socket once the connection is established.
// 5. send() / recv() : Send and receive data.
// 6. closesocket() : Close the service window after use.
// 7. WSACleanup() : Cleanup Winsock (Using the Common Library "WinsockManager" class)

int main()
{
	// ---------------------------------------------------------------------------
	// 0. Initialize Winsock
	WinsockManager winsock;
	if (!winsock.IsInitialized())
	{
		return -1;
	}

	std::cout << "Server [Starting]..." << std::endl;

	// ---------------------------------------------------------------------------
	// 1. Socket
	// Create a socket for listening to incoming connections (IPv4, stream communication/TCP, automatic protocol)
	SOCKET listeningSocket = socket(
		AF_INET,			// Address family [AF_INET: IPv4, AF_INET6: IPv6, AF_BTH: Bluetooth (Windows only)]
		SOCK_STREAM,		// Socket Type [SOCK_STREAM (data guaranteed) , SOCK_DGRM(like packet, the order is not guaranteed)
		0);					// Protocol [0: auto (recommended), IPPROTO_TCP: TCP/IP, IPPROTO_UDP: UDP]
	if (listeningSocket == INVALID_SOCKET)
	{
		std::cerr << "Creating socket failed. Error: " << WSAGetLastError() << std::endl;
	}

	// ---------------------------------------------------------------------------
	// 2. Bind
	// Configure the server information (IP address and port number) to bind to the socket.
	sockaddr_in hint;				// sockaddr_in: IPv4, sockaddr_in6: IPv6
	hint.sin_family = AF_INET;		// 1. Address family 
	hint.sin_port = htons(54000);	// 2. Port number that needs to be converted from host byte order to network byte order
	hint.sin_addr.S_un.S_addr = INADDR_ANY;	// 3. Binary formatted IP address (INADDR_ANY (used by server only): Accepts connections from any network)
	if (bind(
		listeningSocket,				// Socket handle
		(sockaddr*)&hint,				// IP address and port
		sizeof(hint)) == SOCKET_ERROR)	// Size of the IP address and port structure
	{
		std::cerr << "Binding failed. Error: " << WSAGetLastError() << std::endl;
		closesocket(listeningSocket);
		return -1;
	}

	// ---------------------------------------------------------------------------
	// 3. Listen
	// Tell the OS to start listening for incoming connections on the socket.
	if (listen(
		listeningSocket,				// Socket handle
		SOMAXCONN) == SOCKET_ERROR)		// Backlog: Specifies the maximum number of connections in the waiting queue.
	{
		std::cerr << "Listening failed. Error: " << WSAGetLastError() << std::endl;
		closesocket(listeningSocket);
		return -1;
	}

	std::cout << "[Server] Waiting for connections on port 54000..." << std::endl;

	// ---------------------------------------------------------------------------
	// 4. Accept
	// Wait for a client to connect. Once a connection is established, create a new socket for communication.
	sockaddr_in clientInfo;
	int clientSize = sizeof(clientInfo);
	SOCKET clientSocket = accept(
		listeningSocket,
		(sockaddr*)&clientInfo,
		&clientSize);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Accepting connection failed. Error: " << WSAGetLastError() << std::endl;
		closesocket(listeningSocket);
		return -1;
	}

	char clientIp[256];
	ZeroMemory(clientIp, 256);
	inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, 256);
	std::cout << "[Server] Client connected. IP: " << clientIp << std::endl;

	// ---------------------------------------------------------------------------
	// 5r. Receive
	// Receive data from the client. The recv() function will block until data is received or the connection is closed.
	char buffer[4096];
	ZeroMemory(buffer, 4096);

	int bytesReceived = recv(clientSocket, buffer, 4096, 0);
	if (bytesReceived == SOCKET_ERROR)
	{
		std::cerr << "Receiving data failed. Error: " << WSAGetLastError() << std::endl;
	}
	else if (bytesReceived == 0)
	{
		std::cerr << "[Server] Client disconnected." << std::endl;
	}
	else
	{
		// Display received data on the screen.
		std::cout << "[Server] Received Data: " << std::string(buffer, 0, bytesReceived) << std::endl;
	}

	// ---------------------------------------------------------------------------
	// 5s. Send
	// Send data back to the client. The send() function will block until the data is sent or an error occurs.
	closesocket(clientSocket);		// Closing the communication socket
	closesocket(listeningSocket);	// Closing the listening socket
	std::cout << "[Server] Shutdown process complete." << std::endl;

	return 0;
}
