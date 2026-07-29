#include "pch.h"
#include "Warehouse.h"

namespace MapSetExamples
{
	std::optional<int> Warehouse::getStock(const std::string& name) const
	{
		auto it = m_um.find(name);
		if (it != m_um.end())
		{
			return { it->second };
		}
		return std::nullopt;
	}

	std::vector<std::pair<std::string, int>> Warehouse::inspectBucket(size_t b) const
	{
		std::vector<std::pair<std::string, int>> result;
		for (auto it = m_um.begin(b); it != m_um.end(b); ++it)
		{
			result.push_back(*it);
		}
		return result;
	}

	std::vector<std::string> Warehouse::listBucket(size_t bucketIndex) const
	{
		std::vector<std::string> result;
		for (auto it = m_um.begin(bucketIndex); it != m_um.end(bucketIndex); ++it)
		{
			result.push_back(it->first + ": " + std::to_string(it->second));
		}
		return result;
	}

}