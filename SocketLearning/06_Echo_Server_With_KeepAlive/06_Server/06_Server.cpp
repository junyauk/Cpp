#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include "WinsockManager.h"
#include "HeartBeat.h"

#pragma comment(lib, "ws2_32.lib")

using namespace SocketCommon;

// Note:
// Purpose of 06_Echo_Server_With_KeepAlive is for testing basic features of HeartBeat classes.

int main()
{
    WinsockManager winsock;

    // HeartBeatServer
    HeartBeatServer hbServer(54001);
    hbServer.Start();

    // Socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) return -1;

    // Bind & listen
    sockaddr_in hint{ .sin_family = AF_INET, .sin_port = htons(54000) };
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(listenSocket, (sockaddr*)(&hint), sizeof(hint)) == SOCKET_ERROR ||
        listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        return -1;
    }

    std::cout << "[Main Server] Echo Server Started on Port: 54000..." << std::endl;

    // Accept one clinet only
    while (true)
    {
        // Accept
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) break;

        std::cout << "[Main Server] Client connected." << std::endl;

        std::string userId = "UserId";

        char buffer[4096];
        while (true)
        {
            ZeroMemory(buffer, sizeof(buffer));

            // Receive
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) break;

            // Heart beat
            hbServer.SetActiveTime(userId);

            std::string message(buffer, bytesReceived);
            std::cout << "[Main Server] Echo received data: " << message << std::endl;

            // Send
            send(clientSocket, buffer, bytesReceived, 0);
        }

        closesocket(clientSocket);
        std::cout << "[Main Server] Client disconnected." << std::endl;
    }

    closesocket(listenSocket);
    hbServer.Stop();

    return 0;
}
