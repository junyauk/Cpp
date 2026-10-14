#include <iostream>
#include <string>
#include "WinsockManager.h"
#include "ChatClient.h"

using namespace SocketCommon;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    ChatClient client("127.0.0.1", 54000);

    if (!client.Connect())
    {
        std::cout << "[Main] Connecting failed.\n";
        return -1;
    }

    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit") break;
        if (!client.IsRunning()) break;
        if (command.empty()) continue;
        if (!client.SendMessage(command)) break;

        std::cout << "> ";
        std::cout.flush();
    }

    client.Disconnect();

    return true;

}
