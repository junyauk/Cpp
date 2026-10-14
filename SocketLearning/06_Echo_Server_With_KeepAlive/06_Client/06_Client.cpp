#include <iostream>
#include <WS2tcpip.h>
#include "WinsockManager.h"
#include "heartbeat.h"

#pragma comment(lib, "ws2_32.lib")

using namespace SocketCommon;

int main()
{
	WinsockManager winsock;

	std::string ip = "127.0.0.1";
	int port = 54000;
	std::string userId = "UserId";

	// Main socket
	SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mainSocket == INVALID_SOCKET) return -1;

	sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(port) };
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	std::cout << "[Main Client] Echo Connecting to Server... " << std::endl;
	if (connect(mainSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		std::cerr << "[Main Client] Connecting to Server failed." << std::endl;
		closesocket(mainSocket);
		return -1;
	}

	// HeartBeatClient
	HeartBeatClient hbClient(mainSocket, ip, port + 1, userId);
	hbClient.Start();

	std::cout << "[Main Client] Connecting to Server successed." << std::endl;

	// Main loop
	std::string input;
	while (true)
	{
		// Input
		std::cout << "> ";
		std::getline(std::cin, input);
		if (input == "exit") break;

		if (!hbClient.IsPeerAlive())
		{
			std::cout << "\n[Main Client] Something happened on the Heart Beat socket." << std::endl;
			break;
		}

		if (input.empty()) continue;

		// Send
		if (send(mainSocket, input.c_str(), static_cast<int>(input.size()), 0) <= 0)
		{
			std::cout << "[Main Client] send failed. Error: " << WSAGetLastError() << std::endl;
		}

		char buffer[1024];
		ZeroMemory(buffer, sizeof(buffer));
		int bytesReceived = recv(mainSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0)
		{
			std::cout << "[Main Client] Disconnected by Server." << std::endl;
			break;
		}

		std::string message(buffer, bytesReceived);
		std::cout << "[Main Client] Echo from Server: " << message << std::endl;
	}

	hbClient.Stop();
	closesocket(mainSocket);

	return 0;
}
