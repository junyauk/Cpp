#include <iostream>
#include <WS2tcpip.h>
#include "SocketClient.h"

SocketClient::~SocketClient()
{
	Disconnect();
}

bool SocketClient::Connect(const std::string& ip, int port)
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) return false;

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	std::cout << "[Client] Connecting to the server (" << ip << ")..." << std::endl;

	if (connect(m_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		std::cout << "[Client] Failed connecting to the server. Error: " << WSAGetLastError() << std::endl;
		closesocket(m_socket);
		return false;
	}

	std::cout << "Connected to the server! Type a string and press Enter to send." << std::endl;
	std::cout << "Input \"exit\" or close this screen to exit." << std::endl << std::endl;

	// Important: 
	// Register with the OS to set m_socketEvent to the signaled (ON) state
	// when "data received" (FD_READ) or "disconnected" (FD_CLOSE) occurs on the socket.
	// Note:
	// Only one event can be created for one socket, but multiple event types can be associated.
	// If WSAEventSelect() is called twice, the second call will overwrite the first one.
	// So ONE EVENT for ONE SOCKET
	m_socketEvent = WSACreateEvent();
	WSAEventSelect(m_socket, m_socketEvent, FD_READ | FD_CLOSE);

	// Get the handle for standard input (keyboard).
	m_stdInput = GetStdHandle(STD_INPUT_HANDLE);

	m_running = true;
	return true;
}

void SocketClient::RunEventLoop()
{
	HANDLE waitHandles[2] = { m_socketEvent, m_stdInput };

	// Main loop waiting for both Socket and input events
	while (m_running)
	{
		DWORD waitResult = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);
		if (waitResult == WAIT_OBJECT_0)
		{
			// Socket event
			if (!HandleSocketEvent()) break;	// true: keep running, false: exit loop
		}
		else if (waitResult == WAIT_OBJECT_0 + 1)
		{
			// Input event
			if (!HandleInputEvent()) break;		// true: keep running, false: exit loop
		}
	}
}

void SocketClient::Disconnect()
{
	m_running = false;
	if (m_socketEvent != WSA_INVALID_EVENT)
	{
		WSACloseEvent(m_socketEvent);
		m_socketEvent = WSA_INVALID_EVENT;
	}
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool SocketClient::HandleSocketEvent()
{
	WSANETWORKEVENTS networkEvents;
	WSAEnumNetworkEvents(m_socket, m_socketEvent, &networkEvents);

	if (networkEvents.lNetworkEvents & FD_CLOSE)
	{
		std::cout << "\n[Client] The server has shut down or disconnected! Closing the app immediately." << std::endl;
		return false;
	}

	if (networkEvents.lNetworkEvents & FD_READ)
	{
		char buffer[4096];
		ZeroMemory(buffer, sizeof(buffer));
		int bytesReceived = recv(m_socket, buffer, sizeof(buffer), 0);

		if (bytesReceived > 0)
		{
			std::cout << "\n[Client] Server response: " << std::string(buffer, 0, bytesReceived) << std::endl;
			std::cout.flush();
		}
	}

	return true;
}

bool SocketClient::HandleInputEvent()
{
	INPUT_RECORD inputBuffer[128];
	DWORD numRead = 0;

	// Read the contents of the input event.
	if (!ReadConsoleInputA(m_stdInput, inputBuffer, 128, &numRead)) return true;	// Let the main loop keep running

	for (DWORD i = 0; i < numRead; ++i)
	{
		// Isolate only the "keyboard press event" where the "Enter key (VK_RETURN) is pressed"
		if (inputBuffer[i].EventType == KEY_EVENT &&
			inputBuffer[i].Event.KeyEvent.bKeyDown &&
			inputBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
		{
			std::string userInput;
			std::getline(std::cin, userInput);

			if (userInput == "exit") return false;	// for exiting the maing loop

			if (!userInput.empty())
			{
				send(m_socket, userInput.c_str(), static_cast<int>(userInput.size()), 0);
			}

			std::cout << "> ";
			std::cout.flush();
		}
	}

	return true;	// Let the main loop keep running
}
