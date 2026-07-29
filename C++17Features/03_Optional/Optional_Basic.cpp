#include "pch.h"
#include "framework.h"
#include "Optional_Basic.h"

namespace OPTIONAL_Basic
{
	Optional_Basic::Optional_Basic()
	{
		// Initialize map with some data
		m_lookupTable =
		{
			{"Alice", 101},
			{"Bob", 202},
			{"Charlie", 303}
		};
		// Initialise optional member to disengaged state
		m_pendingId = std::nullopt;
	}
	void Optional_Basic::clear()
	{
		m_lookupTable.clear();
		m_pendingId = std::nullopt;
	}

	// 1. Basic Usage: Search a map
	std::optional<int> Optional_Basic::findValue(const std::string& key) const
	{
		if (auto it = m_lookupTable.find(key); it != m_lookupTable.end())
		{
			// Value found, return an engaged optional
			return it->second;
		}
		else
		{
			// Value not found, return a disengaged optional
			return std::nullopt;
		}
	}

	// 2. Value Or: Retrieve a value and provide a default
	int Optional_Basic::getValueOrDefault(const std::string& key, int defaultValue) const
	{
		std::optional<int> result = findValue(key);

		// If result has a value, return it; otherwise, return defaultValue.
		// This is safer and more expressive than manually checking has_value().
		return result.value_or(defaultValue);
	}

	// 3. Setter for a potentially uninitialized member
	void Optional_Basic::setPendingId(std::optional<int> id)
	{
		// Assignment directly works, setting m_pendingId to engaged or disengaged
		m_pendingId = id;
	}

	// 4. Check status and access
	bool Optional_Basic::isPendingId(int expectedId) const
	{
		// Check if optional is engaged using operator bool() or has_value()
		if (m_pendingId && *m_pendingId == expectedId)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
