#pragma comment(lib, "ws2_32.lib")
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

    SocketClient client;

    client.Connect("127.0.0.1", 54000);
    client.RunLoop();

    return 0;
}

