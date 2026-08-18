#pragma once
#include <Windows.h>

namespace Ex01_SRWLock_CondVar
{
	class SrwLockExclusive
	{
	public:
		SrwLockExclusive(SRWLOCK& lock) : m_lock(lock)
		{
			AcquireSRWLockExclusive(&m_lock);
		}
		~SrwLockExclusive()
		{
			ReleaseSRWLockExclusive(&m_lock);
		}

		// Rule of five: delete copy and move constructors and assignment operators
		SrwLockExclusive(const SrwLockExclusive&) = delete;
		SrwLockExclusive& operator=(const SrwLockExclusive&) = delete;
		SrwLockExclusive(SrwLockExclusive&&) = delete;
		SrwLockExclusive& operator=(SrwLockExclusive&&) = delete;
	private:
		SRWLOCK& m_lock;
	};

	class SrwLockShared
	{
	public:
		SrwLockShared(SRWLOCK& lock) : m_lock(lock)
		{
			AcquireSRWLockShared(&m_lock);
		}
		~SrwLockShared()
		{
			ReleaseSRWLockShared(&m_lock);
		}
	private:
		SRWLOCK& m_lock;
	};
}
