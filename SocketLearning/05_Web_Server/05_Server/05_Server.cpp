#include <iostream>
#include "WinsockManager.h"
#include "SocketServer.h"

using namespace SocketCommon;

int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    SocketServer& server = SocketServer::GetInstance();
    server.Start("127.0.0.1", 54000);
    
	std::cout << "[Main] Web server has been shut down. Exiting the program." << std::endl;
    return 0;
}

