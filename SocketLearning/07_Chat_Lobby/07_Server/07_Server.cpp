#include <iostream>
#include <string>
#include "WinsockManager.h"
#include "ChatServer.h"

#pragma comment(lib, "ws2_32.lib")

using namespace SocketCommon;

int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    ChatServer server("172.0.0.1", 54000);
    if (!server.Start())
    {
        std::cerr << "[Main] Starting ChatServer failed.\n";
        return -1;
    }

    std::cout << "[Main] ChatServer started on Port 54000...\n";
    std::cout << "[Main] Type 'exit' and press Enter to stop the server.\n\n";

    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit")
        {
            break;
        }
    }
    std::cout << "[Main] Shutting down the ChatServer...\n";

    server.Stop();

    std::cout << "[Main] ChatServer terminated.\n";

    return 0;
}

