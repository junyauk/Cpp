#pragma once
#include <Windows.h>

namespace Ex03_OrderBookProcessor
{
	class SRWLockWrapper
	{
	public:
		SRWLockWrapper()
		{
			InitializeSRWLock(&m_lock);
		}
		SRWLockWrapper(const SRWLockWrapper&) = delete;
		SRWLockWrapper(SRWLockWrapper&&) = delete;
		SRWLockWrapper& operator=(const SRWLockWrapper&) = delete;
		SRWLockWrapper& operator=(SRWLockWrapper&&) = delete;
		void LockExclusive() { AcquireSRWLockExclusive(&m_lock); }
		void UnlockExclusive() { ReleaseSRWLockExclusive(&m_lock); }
		void LockShared() { AcquireSRWLockShared(&m_lock); }
		void UnlockShared() { ReleaseSRWLockShared(&m_lock); }
	private:
		SRWLOCK m_lock;
	};

	class SRWLE
	{
	public:
		SRWLE(SRWLockWrapper& lock) : m_lock(lock) { m_lock.LockExclusive(); }
		~SRWLE() { m_lock.UnlockExclusive(); }
		SRWLE(const SRWLE&) = delete;
		SRWLE(SRWLE&&) = delete;
		SRWLE& operator=(const SRWLE&) = delete;
		SRWLE& operator=(SRWLE&&) = delete;
	private:
		SRWLockWrapper& m_lock;
	};

	class SRWLS
	{
	public:
		SRWLS(SRWLockWrapper& lock) : m_lock(lock) { m_lock.LockShared(); }
		~SRWLS() { m_lock.UnlockShared(); }
		SRWLS(const SRWLS&) = delete;
		SRWLS(SRWLS&&) = delete;
		SRWLS& operator=(const SRWLS&) = delete;
		SRWLS& operator=(SRWLS&&) = delete;
	private:
		SRWLockWrapper& m_lock;
	};
}

