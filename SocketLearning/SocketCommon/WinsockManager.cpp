#include "WinsockManager.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace SocketCommon
{
	WinsockManager::WinsockManager()
	{
		WSADATA wsaData;
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // Request Winsock ver2.2

		if (result != 0)
		{
			std::cerr << "Initializing Winsock failed. Error Code: " << result << std::endl;
			m_initialized = false;
		}
		else
		{
			m_initialized = true;
		}
		m_initialized = true;
	}
	WinsockManager::~WinsockManager()
	{
		if (m_initialized)
		{
			WSACleanup();
		}
	}
}

