#include "pch.h"
#include <iostream>
#include <typeinfo>
#include "Any_Basic.h"

namespace ANY_Basic
{
	Any_Basic::Any_Basic()
	{
		// Initialize with some diverse configuration data
		setConfigValue("MaxThreads", 8);
		setConfigValue("DatabaseURL", std::string("localhost:5432"));
		setConfigValue("EnableLogging", true);
	}

	void Any_Basic::clear()
	{
		m_config.clear();
	}

	// 3. Unsafe Access: Retrieve a value using std::any_cast<T> (throws on type mismatch)
	std::string Any_Basic::getStringConfigValueUnsafe(const std::string& key) const
	{
		auto it = m_config.find(key);
		if (it == m_config.end() || !it->second.has_value())
		{
			throw std::runtime_error("Config key not found");
		}
		// Use std::any_cast<T>() - if the type is not std::string, it throws std::bad_any_cast.
		return std::any_cast<std::string>(it->second);
	}

	// 4. Check if a value is present and get its type
	std::string Any_Basic::getConfigType(const std::string& key) const
	{
		auto it = m_config.find(key);
		if (it == m_config.end() || !it->second.has_value())
		{
			return "empty";
		}

		// Use type() to retrieve the stored type info.
		// type().name() is implementation-defined, so we check against expected types.
		const std::type_info& type_info = it->second.type();

		if (type_info == typeid(int))
		{
			return "int";
		}
		else if (type_info == typeid(double))
		{
			return "double";
		}
		else if (type_info == typeid(std::string))
		{
			return "std::string";
		}
		else
		{
			return type_info.name(); // Fallback for other types
		}
	}



}
