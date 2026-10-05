#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <sstream>
#include <fstream>
#include "SocketServer.h"

SocketServer& SocketServer::GetInstance()
{
	static SocketServer instance;
	return instance;
}

bool SocketServer::Start(const std::string& ip, const int port)
{
	// Set the static instance pointer to this instance
	m_instance = this;

	// ---------------------------------------------------------------------------
	// 0. Set console control handler to handle Ctrl+C event
	if (!SetConsoleCtrlHandler(reinterpret_cast<PHANDLER_ROUTINE>(ConsoleCtrlHandler), TRUE)) return false;

	// ----------------------------------------------------------------------------
	// 1. Socket
	// 1-1. Create a socket for listening
	// Create a socket for listening (IPv4, stream communication/TCP, automatic protocol)
	m_listenSocket = socket(
		AF_INET,		// Address family [AF_INET: IPv4, AF_INET6: IPv6, AF_BTH: Bluetooth (Windows only)]
		SOCK_STREAM,	// Socket Type [SOCK_STREAM (data guaranteed) , SOCK_DGRM(like packet, the order is not guaranteed)
		IPPROTO_TCP);	// Protocol [0: auto (recommended), IPPROTO_TCP: TCP/IP, IPPROTO_UDP: UDP]
	if (m_listenSocket == INVALID_SOCKET) return false;

	// ---------------------------------------------------------------------------
	// 1-2. Set socket options
	// Set the socket option to reuse the address
	int opt = 1;
	setsockopt(
		m_listenSocket, 
		SOL_SOCKET, 
		SO_REUSEADDR, 
		reinterpret_cast<const char*>(&opt), sizeof(opt));
	// 1-3. Set the socket to non-blocking mode
	// Important:
	// Switch the listening socket to "non-blocking mode."
	// This ensures that when accept() is called,
	// the program does not freeze if no client is present;
	// instead, it immediately returns an error and proceeds.
	// Note: The following code is for Windows. For Linux, use fcntl() to set O_NONBLOCK.
	ULONG mode = 1;
	ioctlsocket(
		m_listenSocket, 
		FIONBIO, 
		&mode);

	// ---------------------------------------------------------------------------
	// 2. Bind
	// Configure the server IP address and port number (preparing bind information)
	sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(port) };
	hint.sin_addr.S_un.S_addr = INADDR_ANY;	// Accept connections from any IP address
	if (bind(m_listenSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR ||
		listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		Stop();
		return false;
	}

	std::cout << "[Server] C++ Winsock2 Web Server started. Listening on " << ip << ":" << port << std::endl;
	std::cout << "[Server] Open your web browser, and access to " << ip << ":" << port << std::endl;
	m_running = true;

	// ---------------------------------------------------------------------------
	// 3. Start the main loop
	RunLoop();

	return false;
}

void SocketServer::Stop()
{
	// 0. Set the running flag to false to stop the main loop
	m_running = false;

	// 1. Close the listening socket
	if (m_listenSocket != INVALID_SOCKET)
	{
		// Shutdown the listening socket for both sending and receiving
		// It will wake up any blocking calls (like accept) and allow the socket to be closed gracefully.
		shutdown(m_listenSocket, SD_BOTH);
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
	}

	// 2. Close all client sockets
	for (SOCKET s : m_clientSockets)
	{
		// Shutdown the client socket for sending (optional, but good practice)
		shutdown(s, SD_SEND);
		closesocket(s);
	}
	m_clientSockets.clear();
}

SocketServer::~SocketServer()
{
	Stop();
}

void SocketServer::RunLoop()
{
	// Main loop for handling incoming connections and data
	while (m_running)
	{
		// ---------------------------------------------------------------------------
		// 1. Prepare the socket monitoring set
		// Create an fd_set structure to hold the sockets to monitor for readability
		fd_set readfds;
		FD_ZERO(&readfds);

		// ----------------------------------------------------------------------------
		// 2. Add sockets to the monitoring set
		// Add the listening socket to the set of sockets to monitor for incoming connections
		FD_SET(m_listenSocket, &readfds);
		for (SOCKET s : m_clientSockets)
		{
			FD_SET(s, &readfds);
		}

		// ---------------------------------------------------------------------------
		// 3. Use select to monitor the sockets for readability
		// Set a timeout of 1 second for select
		timeval timeout{ .tv_sec = 1, .tv_usec = 0 };
		int socketCount = select(
			0,			// Ignored on Windows, but required on Linux
			&readfds,	// Set of sockets to monitor for readability
			nullptr,	// Set of sockets to monitor for writability (not used here)
			nullptr,	// Set of sockets to monitor for errors (not used here)
			&timeout);	// Timeout for select (1 second)

		if (socketCount <= 0) continue;

		// ---------------------------------------------------------------------------
		// 4. Check if the listening socket is ready (indicating a new incoming connection)
		if (FD_ISSET(m_listenSocket, &readfds))
		{
			sockaddr_in clientInfo;
			int clientSize = sizeof(clientInfo);
			SOCKET clientSocket = accept(
				m_listenSocket,			// Listening socket
				(sockaddr*)&clientInfo,	// Client address information
				&clientSize);			// Size of the client address information structure
			if (clientSocket != INVALID_SOCKET)
			{
				ULONG clientMode = 1;
				ioctlsocket(
					clientSocket,	// Client socket
					FIONBIO,		// Command to set non-blocking mode
					&clientMode);	// 1: Enable non-blocking mode, 0: Disable non-blocking mode
				// Add the new client socket to the list of client sockets
				m_clientSockets.push_back(clientSocket);
			}
		}

		// ---------------------------------------------------------------------------
		// 5. Check if any client sockets are ready (indicating incoming data)
		std::erase_if(
			m_clientSockets,
			[this, &readfds](SOCKET s)
			{
				// If the client socket is ready for reading, handle the incoming data
				if (FD_ISSET(s, &readfds))
				{
					char buffer[4096];
					ZeroMemory(buffer, sizeof(buffer));

					// Receive data from the client socket
					int bytesReceived = recv(
						s,				// Client socket
						buffer,			// Buffer to store received data
						sizeof(buffer),	// Size of the buffer
						0);				// Flags (0: no special flags)
					if (bytesReceived <= 0)
					{
						closesocket(s);
						return true;
					}

					std::string requestStr(buffer, 0, bytesReceived);

					// Handle the HTTP request and send the appropriate response
					HandleWebRequest(s, requestStr);

					// After sending the response, close the client socket and remove it from the list
					closesocket(s);
					return true;
				}
				return false;
			});
	}
}

void SocketServer::HandleWebRequest(SOCKET clientSocket, const std::string& request)
{
	if (request.empty()) return;

	// Analyze the HTTP request and prepare the response
	// e.g., "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n"
	std::stringstream requestStream(request);
	std::string method;		// e.g., GET, POST
	std::string path;		// e.g., /index.html
	std::string version;	// e.g., HTTP/1.1

	requestStream >> method >> path >> version;

	std::cout << "[Web Server] Received request: " << method << " " << path << " " << version << std::endl;

	// If simply accessing the root path, redirect to index.html
	if (path == "/")
	{
		path = "/index.html";
	}

	// Prevent directory traversal attacks by checking for ".." in the path
	if (path.find("..") != std::string::npos)
	{
		path = "/index.html";
	}

	// Mapping /sub to /sub.html for demonstration purposes
	std::string filePath = "public" + path;

	// Read the requested file and prepare the HTTP response
	std::ifstream file(filePath, std::ios::binary);
	std::ostringstream htmlBody;
	if (file)
	{
		// Read the file content into a string stream
		std::ostringstream oss;
		oss << file.rdbuf();
		htmlBody << oss.str();
		file.close();
	}
	else
	{
		// If the file is not found, return a 404 Not Found response
		htmlBody << "<html><body><h1>404 Not Found</h1></body></html>";
	}

	std::ostringstream response;
	if (file)
	{
		// If the file is found, return a 200 OK response
		response << "HTTP/1.1 200 OK\r\n";
	}
	else
	{
		// If the file is not found, return a 404 Not Found response
		response << "HTTP/1.1 404 Not Found\r\n";
	}
	// Set the Content-Type header to text/html and specify the character encoding
	response << "Content-Type: text/html; charset=UTF-8\r\n";
	response << "Content-Length: " << htmlBody.str().length() << "\r\n";
	response << "Connection: close\r\n";
	response << "\r\n";	// Important: Blank line to separate headers from body
	response << htmlBody.str();

	std::string fullResponse = response.str();
	send(
		clientSocket,							// Client socket
		fullResponse.c_str(),					// Buffer containing the response data
		static_cast<int>(fullResponse.size()),	// Size of the response data
		0);										// Flags (0: no special flags)
}

bool WINAPI SocketServer::ConsoleCtrlHandler(DWORD ctrlType)
{
	// Return value of the handler function:
	// True: The event has been handled, and the process should not terminate.
	// False: The event has not been handled, and the process should terminate.

	// Handle Ctrl+C event
	if (ctrlType == CTRL_C_EVENT || ctrlType == CTRL_CLOSE_EVENT)
	{
		std::cout << "Exit request detected. Shutting down the single-threaded server safely." << std::endl;
		// Call the Stop() method of the SocketServer instance to stop the server gracefully
		m_instance->Stop();
		Sleep(1000); // Wait for a moment to ensure the server stops gracefully)

		// Return true to indicate that the event has been handled and the process should not terminate
		return true;
	}
	// For other events, return false to allow the process to terminate
	return false;
}
