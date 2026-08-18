#include "classicmutexcache.h"

namespace Ex01_SRWLock_CondVar
{
	ClassicMutexCache::ClassicMutexCache(const uint32_t capacity) : m_capacity(capacity){}
	bool ClassicMutexCache::Get(const std::string& key, std::string& value) const
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		auto it = m_cache.find(key);
		if (it != m_cache.end())
		{
			value = it->second;
			return true;
		}
		return false;
	}
	void ClassicMutexCache::Put(const std::string& key, const std::string& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this, key] 
			{
				// Resume if the key exists or enough space
				return m_cache.find(key) != m_cache.end() ||  m_cache.size() < m_capacity;
			});
		m_cache[key] = value;
	}
	void ClassicMutexCache::Remove(const std::string& key)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_cache.erase(key) != 0)
		{
			// Removed, so there must be a free space.
			m_cv.notify_one();
		}
	}
	uint32_t ClassicMutexCache::GetCount() const
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return static_cast<uint32_t>(m_cache.size());
	}
	uint32_t ClassicMutexCache::GetCapacity() const
	{
		return m_capacity;
	}
}
