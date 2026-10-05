#pragma once

namespace SocketCommon
{
	class WinsockManager
	{
	public:
		WinsockManager();
		~WinsockManager();

		WinsockManager(const WinsockManager&) = delete;
		WinsockManager(WinsockManager&&) = delete;
		WinsockManager& operator=(const WinsockManager&) = delete;
		WinsockManager& operator=(WinsockManager&&) = delete;

		bool IsInitialized() const { return m_initialized; }
	private:
		bool m_initialized = false;
	};
}

