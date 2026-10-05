#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "winsockmanager.h"

using namespace SocketCommon;

int main()
{
	// ---------------------------------------------------------------------------
	// 0. Initialize Winsock
	// The WinsockManager class automatically calls WSAStartup() in its constructor and WSACleanup() in its destructor.
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    std::cout << "[Client] Starting..." << std::endl;

	// ---------------------------------------------------------------------------
	// 1. Socket
	// Create a socket for connecting to the server (IPv4, stream communication/TCP, automatic protocol)
    SOCKET connectSocket = socket(
		AF_INET,        // Address family [AF_INET: IPv4, AF_INET6: IPv6, AF_BTH: Bluetooth (Windows only)]
		SOCK_STREAM,    // Socket Type [SOCK_STREAM (data guaranteed) , SOCK_DGRM(like packet, the order is not guaranteed)
		0);             // Protocol [0: auto (recommended), IPPROTO_TCP: TCP/IP, IPPROTO_UDP: UDP]
    if (connectSocket == INVALID_SOCKET) return -1;

	// ---------------------------------------------------------------------------
	// 2. Connect
	// Specify the server's IP address and port number to connect to.
    std::string serverIp = "127.0.0.1";
    int port = 54000;
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, serverIp.c_str(), &hint.sin_addr);
    std::cout << "[Client] Connecting to the server..." << std::endl;
    int connect_result = connect(
		connectSocket,      // The target socket
		(sockaddr*)&hint,   // The hint contains a set of IP address and port
		sizeof(hint));      // Size of the sockaddr_in structure
    if (connect_result == SOCKET_ERROR)
    {
        std::cerr << "Connection failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        return -1;
    }

    std::cout << "Connected to the server! Type your message and press Enter to send." << std::endl;
    std::cout << "Type \"exit\" to quit.\n" << std::endl;

    std::string userInput;
    char buffer[4096];

	// Main loop for sending user input to the server and receiving responses
    while (true)
    {
		// Prompt the user for input (blocking: waits for the user to press Enter)
        std::cout << ">";
        std::getline(std::cin, userInput);  // Read a full line of input from the keyboard.

        if (userInput.empty())
        {
            continue;   // If the string is empty, do nothing and proceed to the next input.
        }

		// ---------------------------------------------------------------------------
        // 3s. Send
		// Send the user input to the server. The send() function is blocking,
        int sendResult = send(
			connectSocket,                      // The target socket
			userInput.c_str(),                  // The message to send (C-style string)
			static_cast<int>(userInput.size()), // The size of the message
			0);                                 // Flags (0: no special flags)
        if (sendResult == SOCKET_ERROR)
        {
            std::cerr << "A transmission error occurred. Error: " << WSAGetLastError() << std::endl;
            break;
        }

        // If the user has entered "exit," 
        // the program exits the loop and proceeds to the termination process 
        // after sending the input.
        if (userInput == "exit")
        {
            std::cout << "[Client] Received the exit command. Disconnect it." << std::endl;
            break;
        }

		// ---------------------------------------------------------------------------
		// 3r. Receive
		// Receive the echo-back from the server. The recv() function is blocking,
        ZeroMemory(buffer, 4096);
        int bytesReceived = recv(connectSocket, buffer, 4096, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "Error receiving response from server. Error: " << WSAGetLastError() << std::endl;
            break;
        }
        if (bytesReceived == 0)
        {
            std::cout << "The connection was closed by the server." << std::endl;
            break;
        }

        // 3. Display the received echo-back on the screen.
        std::cout << "[Client] Server response: " << std::string(buffer, 0, bytesReceived) << std::endl;
    }

	// ---------------------------------------------------------------------------
	// 4. Termination
    closesocket(connectSocket);
    std::cout << "[Client] Shutdown process complete." << std::endl;

    return 0;

}
