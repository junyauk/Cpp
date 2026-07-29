#pragma once
#include <any>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <optional>

namespace ANY_Basic
{
	class Any_Basic
	{
	private:
		// Member to store a collection of heterogeneous configuration values
		std::map<std::string, std::any> m_config;

	public:
		Any_Basic();
		void clear();

		// 1. Basic Usage: Store a value of any type
		template<typename T>
		void setConfigValue(const std::string& key, T&& value);

		// 2. Safe Access: Retrieve a value using std::any_cast<T*>
		// Attempts to get the value as T. Returns std::nullopt if the key is not found
		// or the held type does not match T.
		template<typename T>
		std::optional<T> getConfigValueSafe(const std::string& key) const;

		// 3. Unsafe Access: Retrieve a value using std::any_cast<T> (throws on type mismatch)
		// Note: This function throws std::bad_any_cast if the type is wrong.
		std::string getStringConfigValueUnsafe(const std::string& key) const;

		// 4. Check if a value is present and get its type
		// Returns the name of the held type (e.g., "int", "std::string"). Returns "empty" if no value is held.
		std::string getConfigType(const std::string& key) const;
	};

	// Helper template implementation (must be in the header)
	template<typename T>
	void Any_Basic::setConfigValue(const std::string& key, T&& value)
	{
		m_config[key] = std::forward<T>(value);
	}

	template<typename T>
	std::optional<T> Any_Basic::getConfigValueSafe(const std::string& key) const
	{
		auto it = m_config.find(key);
		if (it == m_config.end()		// key not found
			|| !it->second.has_value())	// any is empty
		{
			return std::nullopt;
		}

		// Use std::any_cast<T*> for safe (non-throwing) access
		if (const T* ptr = std::any_cast<T>(&it->second))
		{
			return *ptr; // Return value
		}
		else
		{
			return std::nullopt; // Type mismatch
		}
	}
}

