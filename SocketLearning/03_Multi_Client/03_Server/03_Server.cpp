#include "winsockmanager.h"
#include "SocketServer.h"

using namespace SocketCommon;

int main()
{
    WinsockManager winsock;
    if (!winsock.IsInitialized()) return -1;

    SocketServer& server = SocketServer::GetInstance();
    server.Start(54000);
    return 0;
}
