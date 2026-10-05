#include "SocketServer.h"
#include "winsockmanager.h"
#include <iostream>

using namespace SocketCommon;
int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    SocketServer::GetInstance().Start(54000);

    std::cout << "[Main] The single-threaded multiplexing server has shut down safely." << std::endl;

    return 0;
}
