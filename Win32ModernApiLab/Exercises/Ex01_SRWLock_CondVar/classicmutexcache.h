#pragma once
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include "icache.h"

namespace Ex01_SRWLock_CondVar
{
	class ClassicMutexCache : public ICache
	{
	public:
		ClassicMutexCache(const uint32_t capacity);
		bool Get(const std::string& key, std::string& value) const override;
		void Put(const std::string& key, const std::string& value) override;
		void Remove(const std::string& key) override;
		uint32_t GetCount() const override;
		uint32_t GetCapacity() const override;

	private:
		mutable std::mutex m_mutex;
		std::condition_variable m_cv;
		std::unordered_map<std::string, std::string> m_cache;
		uint32_t m_capacity;
	};
}
