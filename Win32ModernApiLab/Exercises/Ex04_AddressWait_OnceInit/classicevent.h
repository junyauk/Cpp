#pragma once
#pragma comment(lib, "Synchronization.lib")
#include <Windows.h>

namespace Ex04_AddressWait_OnceInit
{
	class ClassicEvent
	{
	public:
		ClassicEvent(const bool manualReset = true)
		{
			m_hEvent = CreateEventW(NULL, manualReset, FALSE, NULL);
		}
		~ClassicEvent()
		{
			if (m_hEvent != NULL)
			{
				CloseHandle(m_hEvent);
				m_hEvent = NULL;
			}
		}

		// Rule of Five
		ClassicEvent(const ClassicEvent&) = delete;
		ClassicEvent(ClassicEvent&&) = delete;
		ClassicEvent& operator=(const ClassicEvent&) = delete;
		ClassicEvent& operator=(ClassicEvent&&) = delete;

		DWORD Wait(const DWORD dwMilliseconds = INFINITE) const
		{
			// Return values
			// WAIT_OBJECT_0 (0x00000000) : Success
			// WAIT_TIMEOUT (0x00000102) : Timed out
			// WAIT_ABANDONED (0x00000080) : Thread finished without freeing mutex
			// WAIT_FAILED (0xFFFFFFFF) : Failed (e.g. the handle has already been freed)
			return (m_hEvent == NULL) ? WAIT_FAILED : WaitForSingleObject(m_hEvent, dwMilliseconds);
		}

		BOOL Set() const
		{
			return (m_hEvent == NULL) ? FALSE : SetEvent(m_hEvent);
		}
		
		BOOL Reset() const
		{
			return (m_hEvent == NULL) ? FALSE : ResetEvent(m_hEvent);
		}
	private:
		HANDLE m_hEvent;
	};
}
