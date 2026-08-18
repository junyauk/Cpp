#pragma once
#include <string>
#include <cstdint>

namespace Ex01_SRWLock_CondVar
{
	class ICache
	{
	public:
		virtual ~ICache() = default;
		virtual bool Get(const std::string& key, std::string& value) const = 0;
		virtual void Put(const std::string& key, const std::string& value) = 0;
		virtual void Remove(const std::string& key) = 0;
		virtual uint32_t GetCount() const = 0;
		virtual uint32_t GetCapacity() const = 0;
	};
}
