#pragma once
#include <windows.h>
#include <unordered_map>
#include <string>
#include "ICache.h"

namespace Ex01_SRWLock_CondVar
{
	class ModernSrwCache : public ICache
	{
	public:
		ModernSrwCache(const uint32_t capacity);
		bool Get(const std::string& key, std::string& value) const override;
		void Put(const std::string& key, const std::string& value) override;
		void Remove(const std::string& key) override;
		uint32_t GetCount() const override;
		uint32_t GetCapacity() const override;

	private:
		CONDITION_VARIABLE m_cv;
		mutable SRWLOCK m_lock;
		std::unordered_map<std::string, std::string> m_cache;
		uint32_t m_capacity;
	};
}
