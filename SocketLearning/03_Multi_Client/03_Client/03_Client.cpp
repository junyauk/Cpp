#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "WinsockManager.h"
#include "SocketClient.h"

using namespace SocketCommon;

int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    std::cout << "[Client] Starting..." << std::endl;

    SocketClient client;
    if (client.Connect("127.0.0.1", 54000))
    {
        client.RunEventLoop();
    }

    std::cout << "[Client] Shutdown process complete." << std::endl;
    return 0;
}
