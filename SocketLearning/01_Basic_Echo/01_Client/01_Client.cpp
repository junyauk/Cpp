#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "WinsockManager.h"

using namespace SocketCommon;

// Note:
// 
// This file demonstrates how to use Socket as client with minimum code.
// The following functions are essential.
// 
// 0. WSAStartup() : Initialize Winsock (Using the Common Library "WinsockManager" class)
// 1. socket() : Create the service window
// 2. connect() : Specify the server's IP address and port, and perform the connection handshake.
// 3. send() / recv() : Send and receive data.
// 4. closesocket() : Close the service window after use.
// 5. WSACleanup() : Cleanup Winsock (Using the Common Library "WinsockManager" class)

int main()
{
    // ---------------------------------------------------------------------------
	// 0. Initialize Winsock
	// The WinsockManager class automatically calls WSAStartup() in its constructor and WSACleanup() in its destructor.
    WinsockManager winsock;
    if (!winsock.IsInitialized())
    {
        return -1;
    }

    std::cout << "[Client] Starting..." << std::endl;

    // ---------------------------------------------------------------------------
    // 1. Socket
	// Create a socket for connecting to the server (IPv4, stream communication/TCP, automatic protocol)
    SOCKET connectSocket = socket(
        AF_INET,        // Address family [AF_INET: IPv4, AF_INET6: IPv6, AF_BTH: Bluetooth (Windows only)]
        SOCK_STREAM,    // Socket Type [SOCK_STREAM (data guaranteed) , SOCK_DGRM(like packet, the order is not guaranteed)
        0);             // Protocol [0: auto (recommended), IPPROTO_TCP: TCP/IP, IPPROTO_UDP: UDP]
    if (connectSocket == INVALID_SOCKET)
    {
        std::cerr << "Creating Scoket failed. Error: " << WSAGetLastError() << std::endl;
        return -1;
    }

    // ---------------------------------------------------------------------------
	// 2. Connect
	// Specify the server's IP address and port number to connect to.
    std::string serverIp = "127.0.0.1"; // localhost address
    int port = 54000;                   // The port number on which the server is listening

    // sockaddr_in: For Managing a set of IP address and port
    sockaddr_in hint;               // sockaddr_in: IPv4, sockaddr_in6: IPv6
    hint.sin_family = AF_INET;      // 1. Address family 
    // htons : Host To Network Short(16bit) for converting little -> big endian
    hint.sin_port = htons(port);    // 2. Port number
    // hint.sin_addr                // 3. IP address (should be the following binary format)
    // inet_pton : Internet Network Presentation To Network
    // Convert an IP address string ("127.0.0.1") to binary format (4 bytes) and store it in a structure.
    inet_pton(
        AF_INET, 
        serverIp.c_str(),   // IP address
        &hint.sin_addr);    // The binary formatted IP address is stored here
    std::cout << "[Client] Trying to connect to (" << serverIp << ":" << port << ")...\n";
    int connectResult = connect(
                            connectSocket,      // The target socket
                            (sockaddr*)&hint,   // The hint contains a set of IP address and port
                            sizeof(hint));
    if (connectResult == SOCKET_ERROR)
    {
        std::cerr << "Connecting to the server failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        return -1;
    }

    std::cout << "[Client] Connecting to the server succeeded." << std::endl;

	// ---------------------------------------------------------------------------
	// 3. Send
	// Send a message to the server
    std::string message = "Hello, VisualStudio 2026 Socket!";
    int sendResult = send(
                        connectSocket,                          // Target socket
                        message.c_str(),                        // The buffer contains data for sending
                        static_cast<int>(message.size()), 0);   // The buffer size
    if (sendResult == SOCKET_ERROR)
    {
        std::cerr << "Sending data error. Error: " << WSAGetLastError() << std::endl;
    }
    else
    {
        std::cout << "[Client] Sent the message : " << message << std::endl;
    }
    closesocket(connectSocket);
    std::cout << "[Client] Shutdown process complete." << std::endl;

    return 0;
}
