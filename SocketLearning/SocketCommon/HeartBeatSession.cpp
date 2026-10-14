#include <iostream>
#include "HeartBeat.h"

namespace SocketCommon
{
	HeartBeatSession::HeartBeatSession(SOCKET hbSocket, SOCKET mainSocket, std::string userId)
		: m_socket(hbSocket)
		, m_mainSocket(mainSocket)
		, m_userId(userId)
	{}
	HeartBeatSession::~HeartBeatSession()
	{
		std::cout << "[HB Session] destructor ->\n";

		Stop();
		auto s = m_socket.exchange(INVALID_SOCKET);
		if (s != INVALID_SOCKET)
		{
			closesocket(s);
		}
		std::cout << "[HB Session] destructor <-\n";
	}

	void HeartBeatSession::Start(uint16_t timeoutSec)
	{
		if (m_running.load()) return;

		int timeoutMs = static_cast<int>(timeoutSec) * 1000;

		timeval timeout{ .tv_sec = timeoutMs, .tv_usec = 0 };
		if (setsockopt(m_socket.load(), SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeoutMs), sizeof(timeoutMs)) == SOCKET_ERROR)
		{
			std::cerr << "[HeartBeatSession] setsockopt failed. Error: " << WSAGetLastError() << "\n";
			return;
		}

		m_running.store(true);

		m_stopSignal = std::promise<void>();
		m_thread = std::jthread([this](std::stop_token st)
			{
				this->MonitorLoop(st);
			});
	}

	void HeartBeatSession::Stop()
	{
		if (!m_running.load()) return;

		std::cout << "[HB Session] Stop ->\n";

		// Stop the thread
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
		std::cout << "[HB Session] Stop <-\n";

	}

	bool HeartBeatSession::IsPeerAlive() const
	{
		std::cout << "[HB Session] IsPeerAlive() was called.\n";
		return m_running.load();
	}

	void HeartBeatSession::SetActiveTime()
	{
		std::cout << "[HB Session] SetActiveTime() for " << m_userId << " was called.\n";
		m_lastActiveTime.store(std::chrono::steady_clock::now());
	}

	void HeartBeatSession::MonitorLoop(std::stop_token st)
	{
		auto stopFuture = m_stopSignal.get_future();

		char buf = '\0';

		while (!st.stop_requested())
		{
			int bytes = 0;
			bytes = recv(m_socket.load(), &buf, sizeof(buf), 0);
			if (bytes <= 0)
			{
				std::cout << "[HB Session] Time out detected" << m_userId << "\n";
				break;
			}

			// Mark the time
			SetActiveTime();

			// For controling frequency
			if (stopFuture.wait_for(std::chrono::seconds(1)) == std::future_status::ready) break;
		}
		m_running.store(false);

		if (m_mainSocket.load() != INVALID_SOCKET)
		{
			shutdown(m_mainSocket.load(), SD_BOTH);
		}
	}

	void SocketCommon::HeartBeatSession::SetTargetSocket(SOCKET targetSocket)
	{
		if (targetSocket != INVALID_SOCKET)
		{
			m_mainSocket = targetSocket;
		}
	}
}
