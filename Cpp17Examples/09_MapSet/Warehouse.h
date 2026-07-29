#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <optional>



// bucket_count() returns a number of buckets
// bucket(xxx) returns a bucket number that xxx contains
// bucket_size(x) returns a number of elements in the bucket specified by the bucket number
// load_factor() returns [the number of elements / the number of buckets] 0.0 ~ 1.0

namespace MapSetExamples
{
	class Warehouse
	{
	private:
		std::unordered_map<std::string, int> m_um;
	public:
		void addProduct(const std::string& name, int count) { m_um[name] += count; }

		std::optional<int> getStock(const std::string& name) const;

		size_t bucketCount() const { return m_um.bucket_count(); }
		size_t bucket(const std::string& name) const { return m_um.bucket(name); }
		size_t bucketSize(size_t b) const { return m_um.bucket_size(b); }

		std::vector<std::string> listBucket(size_t bucketIndex) const;

		std::vector<std::pair<std::string, int>> inspectBucket(size_t b) const;

		void rehash(size_t n) { m_um.rehash(n); }
		void reserve(size_t n) { m_um.reserve(n); }

		// need to be updated
		float getCurrentLoadFactor() const { return m_um.load_factor(); }
		float getMaxLoadFactor() { return m_um.max_load_factor(); }
		void setMaxLoadFactor(float f) { return m_um.max_load_factor(f); }
	};
}
