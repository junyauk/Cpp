#include "HeartBeat.h"
#include <iostream>
#include <chrono>
#include <mutex>
#include <WS2tcpip.h>

namespace SocketCommon
{
	HeartBeatClient::HeartBeatClient(SOCKET mainSocket, const std::string& ip, const uint16_t port, const std::string sessionId)
		: m_mainSocket(mainSocket)
		, m_ip(ip)
		, m_port(port)
		, m_sessionId(sessionId)
	{}

	HeartBeatClient::~HeartBeatClient() { Stop(); }

	void HeartBeatClient::Start(const uint32_t pingIntervalSec, const uint32_t timeoutSec)
	{
		if (m_running) return;

		m_stopSignal = std::promise<void>();

		m_running.store(true);

		m_pingInterval = pingIntervalSec;
		m_timeout = timeoutSec;
		m_thread = std::jthread([this](std::stop_token st) {this->MonitorLoop(st); });
	}

	void HeartBeatClient::Stop()
	{
		if (!m_running) return;

		std::cout << "[HB Client] Stop() start ->\n";
		// Stop the main loop
		m_thread.request_stop();

		// For exiting stopFuture.wait_for() in the loop.
		try
		{
			// Note:
			// If Stop() might have been called twice, the m_stopSignal might not be available.
			// For avoiding this case, use try-catch.
			m_stopSignal.set_value();
		}
		catch (const std::future_error&)
		{
			// Invalid m_stopSignal was used.
			// Pretend nothing's happened as it's done already.
		}

		if (m_thread.joinable())
		{
			m_thread.join();
		}
		std::cout << "[HB Client] Stop() end <-\n";
	}

	bool HeartBeatClient::IsPeerAlive() const { return m_running; }

	void HeartBeatClient::MonitorLoop(std::stop_token st)
	{
		// Create a socket
		m_socket.store(socket(
			AF_INET,
			SOCK_STREAM,
			0));
		if (m_socket.load() == INVALID_SOCKET) return;

		// Connect
		sockaddr_in hint{ .sin_family = AF_INET, .sin_port = m_port };
		inet_pton(AF_INET, m_ip.c_str(), &hint.sin_addr);
		if (connect(m_socket.load(), (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
		{
			std::cout << "[HB Client] Connection failed Port:" << m_port << std::endl;
			closesocket(m_socket.load());
			m_running.store(false);
			return;
		}

		// Handshake introducing who is connecting
		if (send(m_socket.load(), m_sessionId.c_str(), static_cast<int>(m_sessionId.size()), 0) == SOCKET_ERROR)
		{
			std::cout << "[HB Client] Send (Handshake) failed:" << m_port << std::endl;
			closesocket(m_socket.load());
			m_running.store(false);
			return;
		}

		auto stopFuture = m_stopSignal.get_future();

		std::cout << "[HB Client] MonitorLoop Loop start ->\n";
		while (!st.stop_requested())
		{
			// For controling frequency
			if (stopFuture.wait_for(std::chrono::seconds(m_pingInterval)) == std::future_status::ready)
			{
				std::cout << "[HB Client] Stop signaled by .Stop()\n";
				break;	// Stop signaled by .Stop()
			}

			const char pingChar = '\x02';
			std::cout << "[HB Client] Ping !\n";
			if (send(m_socket, &pingChar, 1, 0) == SOCKET_ERROR)
			{
				std::cout << "\n[HB Client] Sending Ping to the server failed.\n";
				break;
			}
		}
		m_running.store(false);

		auto s = m_socket.exchange(INVALID_SOCKET);
		if (m_socket.load() != INVALID_SOCKET)
		{
			closesocket(m_socket.load());
		}

		if (m_mainSocket.load() != INVALID_SOCKET)
		{
			shutdown(m_mainSocket.load(), SD_BOTH);
		}
	}
}
