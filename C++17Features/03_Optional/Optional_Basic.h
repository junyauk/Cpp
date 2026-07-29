#pragma once
#include <optional>
#include <string>
#include <map>

namespace OPTIONAL_Basic
{
	class Optional_Basic
	{
	private:
		std::map<std::string, int> m_lookupTable;
		std::optional<int> m_pendingId;

	public:
		Optional_Basic();
		void clear();
		// 1. Basic Usage: Search a map and return an optional int
		// Returns the integer value associated with the key if found, or std::nullopt otherwise.
		std::optional<int> findValue(const std::string& key) const;

		// 2. Value Or: Retrieve a value and provide a default if it's not present
		// Returns the value if present, or the provided default value if absent.
		int getValueOrDefault(const std::string& key, int defaultValue) const;

		// 3. Setter for a potentially uninitialized member
		// An optional member to track a "pending" ID.
		void setPendingId(std::optional<int> id);

		// 4. Check status and access (value() vs operator*)
		// Returns true if the pending ID is set and equal to the expected value.
		bool isPendingId(int expectedId) const;
	};
}
