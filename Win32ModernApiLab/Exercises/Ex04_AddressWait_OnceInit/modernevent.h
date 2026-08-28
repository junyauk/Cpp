#pragma once
#pragma comment(lib, "Synchronization.lib")
#include <atomic>
#include <Windows.h>

namespace Ex04_AddressWait_OnceInit
{
	class ModernEvent
	{
	public:
		DWORD Wait(const DWORD dwMilliseconds = INFINITE) const
		{
			while (true)
			{
				uint32_t expected = 1;
				uint32_t suspendState = 0;

				// m_state(before) | CAS result | m_state(after) | expected(after)
				// 0 (unsignaled)  | failed     | 0              | 0
				// 1 (signaled)    | successed  | 0              | 1
				// 1 (signaled)    | suprious   | 1              | 1

				// Note:
				// m_state can be 0(unsignal) or 1(signal).
				if (m_state.compare_exchange_weak(expected, suspendState)) // CAS
				{
					// Successed to exchange
					
					// Case 1 (m_state was 1)
					// m_state: overritten with suspendState(0)
					// expected (1): no change
					return WAIT_OBJECT_0;
				}
				else
				{
					// Failed to exchange.

					// Case 1 (m_state was 1)
					// m_state: no change
					// expected: overritten with m_state(1) -> go to the Spurious failure block

					// Case 0 (m_state was 0) exchange was not happen
					// Because m_state(0) was different from expected(1)


					if (expected == 0)
					{
						BOOL ret = WaitOnAddress((VOID*)&m_state, (PVOID)&expected, sizeof(uint32_t), dwMilliseconds);
						if (!ret)
						{
							if (GetLastError() == ERROR_TIMEOUT)
							{
								return WAIT_TIMEOUT;
							}
						}
					}
					else
					{
						// Spurious failure block
						// Try CAS again
					}
				}
			}
		}

		BOOL Set() const
		{
			m_state.store(1, std::memory_order_release);
			WakeByAddressSingle(&m_state);
			return true;
		}

		BOOL Reset() const
		{
			m_state.store(0, std::memory_order_release);
			return true;
		}
	private:
		mutable std::atomic<uint32_t> m_state;
	};
}
