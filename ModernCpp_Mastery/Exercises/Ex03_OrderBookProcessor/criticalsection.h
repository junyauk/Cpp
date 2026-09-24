#pragma once
#include <Windows.h>

namespace Ex03_OrderBookProcessor
{
	class CriticalSection
	{
	public:
		CriticalSection()
		{
			if (!InitializeCriticalSectionAndSpinCount(&m_cs, 4000))
			{
				// Throw an exception
				DWORD errorCode = ::GetLastError();
				throw std::system_error(
					static_cast<int>(errorCode),
					std::system_category(),
					"Failed to initialize CRITICAL_SECTION"
				);
			}
		}
		~CriticalSection()
		{
			DeleteCriticalSection(&m_cs);
		}

		void Enter()
		{
			EnterCriticalSection(&m_cs);
		}

		void Leave()
		{
			LeaveCriticalSection(&m_cs);
		}

		CriticalSection(const CriticalSection&) = delete;
		CriticalSection(CriticalSection&&) = delete;
		CriticalSection& operator=(const CriticalSection&) = delete;
		CriticalSection& operator=(CriticalSection&&) = delete;
	private:
		CRITICAL_SECTION m_cs;
	};

	class CS
	{
	public:
		CS(CriticalSection& cs) : m_cs(cs) { cs.Enter(); }
		~CS() { m_cs.Leave(); }

		CS() = delete;
		CS(const CS&) = delete;
		CS(CS&&) = delete;
		CS& operator=(const CS&) = delete;
		CS& operator=(CS&&) = delete;
	private:
		CriticalSection& m_cs;
	};
}

