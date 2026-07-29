#pragma once
#include <unordered_map>
#include <string>

namespace MapSetExamples
{
	inline float getLoadFactor(size_t numElements, size_t reserveHint)
	{
		std::unordered_map<int, std::string> um;

		um.reserve(reserveHint);

		for (size_t i = 0; i < numElements; ++i)
		{
			um.emplace(static_cast<int>(i), "value");
		}
		return um.load_factor();
	}

	inline std::vector<std::string> ExampleOfUnorderedMapBuckets()
	{
		std::vector<std::string> ret;
		std::unordered_map<int, std::string> um;

		{
			std::stringstream ss;
			ss << "Initial size= " << um.size()
				<< ", bucket_count= " << um.bucket_count()
				<< ", load_factor= " << um.load_factor();
			ret.push_back(ss.str());
		}

		for (int i = 0; i < 2; ++i)
		{
			um.emplace(i, "val" + std::to_string(i));
		}

		{
			std::stringstream ss;
			ss << "After insert 20: size= " << um.size()
				<< ", bucket_count= " << um.bucket_count()
				<< ", load_factor= " << um.load_factor();
			ret.push_back(ss.str());
		}

		um.rehash(50);
		{
			std::stringstream ss;
			ss << "After rehash(50): size=" << um.size()
				<< ", bucket_count= " << um.bucket_count()
				<< ", load_factor= " << um.load_factor();
			ret.push_back(ss.str());
		}

		um.reserve(200);
		{
			std::stringstream ss;
			ss << "After reserve(200): size=" << um.size()
				<< ", bucket_count= " << um.bucket_count()
				<< ", load_factor= " << um.load_factor();
			ret.push_back(ss.str());
		}

		return ret;
	}
}

