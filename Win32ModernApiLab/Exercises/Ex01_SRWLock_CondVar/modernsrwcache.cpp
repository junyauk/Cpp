#include "modernsrwcache.h"
#include "srwlockwrapper.h"

namespace Ex01_SRWLock_CondVar
{
	ModernSrwCache::ModernSrwCache(const uint32_t capacity) : m_capacity(capacity)
	{
		InitializeSRWLock(&m_lock);
		InitializeConditionVariable(&m_cv);
	}
	bool ModernSrwCache::Get(const std::string& key, std::string& value) const
	{
		bool ret = false;
		SrwLockShared lock(m_lock);

		auto it = m_cache.find(key);
		if (it != m_cache.end())
		{
			value = it->second;
			ret = true;
		}

		return ret;
	}
	void ModernSrwCache::Put(const std::string& key, const std::string& value)
	{
		SrwLockExclusive lock(m_lock);
		while (m_cache.find(key) == m_cache.end()	// New key
			&& m_cache.size() >= m_capacity)		// Full
		{
			SleepConditionVariableSRW(&m_cv, &m_lock, INFINITE, 0);
		}
		m_cache[key] = value;
	}
	void ModernSrwCache::Remove(const std::string& key)
	{
		SrwLockExclusive lock(m_lock);
		if (m_cache.erase(key) != 0)
		{
			// Removed, so there must be a free space.
			WakeConditionVariable(&m_cv);
		}
	}

	uint32_t ModernSrwCache::GetCount() const
	{
		SrwLockShared lock(m_lock);
		uint32_t size = static_cast<uint32_t>(m_cache.size());
		return size;
	}
	uint32_t ModernSrwCache::GetCapacity() const
	{
		return m_capacity;
	}
}
