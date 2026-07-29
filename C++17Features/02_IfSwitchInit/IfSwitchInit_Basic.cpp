#include "pch.h"
#include "framework.h"
#include "IfSwitchInit_Basic.h"

namespace IFSWITCHINIT_Basic
{
	// A helper function to simulate retrieving a status code
	int getStatusCode(int input)
	{
		if (input < 0) return -1;
		if (input == 0) return 0;
		if (input == 1) return 10;
		return 20;
	}

	IfSwitchInit_Basic::IfSwitchInit_Basic()
	{
		m_lookupTable =
		{
			{1, "One"},
			{5, "Five"},
			{10, "Ten"}
		};
	}
	void IfSwitchInit_Basic::clear()
	{
		m_lookupTable.clear();
	}

	// 1. Example using if-initializer with map::find
	std::optional<std::string> IfSwitchInit_Basic::getValueIfKeyExists(int key)
	{
		// C++17 if-initializer: 'it' is declared and initialized, and its scope is limited to the if/else block.
		if (auto it = m_lookupTable.find(key); it != m_lookupTable.end())
		{
			// it is accessible here
			return it->second;
		}
		else
		{
			// 'it' is also accessible in the else block, but here we just return nothing.
			return std::nullopt;
		}
		// 'it' goes out of scope here.
	}

	// 2. Example using if-initializer with an object that needs limited scope
	std::optional<int> IfSwitchInit_Basic::calculateMetricIfValid(int rawValue, int threshold)
	{
		// C++17 if-initializer: 'metric' is initialized and its scope is limited.
		if (ComplexMetric metric(rawValue); metric.getValue() > threshold)
		{
			// metric is alive and accessible here
			return metric.getValue();
		}
		else
		{
			return std::nullopt;
		}
		// 'metric' is destroyed here (RAII benefit).
	}

	// 3. Example using switch-initializer
	std::string IfSwitchInit_Basic::processStatusCode(int initialValue)
	{
		// C++17 switch-initializer: 'code' is declared, initialized, and its scope is limited to the switch block.
		switch (int code = getStatusCode(initialValue); code)
		{
		case -1:	return "Error: Negative Input";
		case 0: 	return "Status: OK";
		case 10: 	return "Warning: High Value";
		default: 	return "Unknown Status: " + std::to_string(code);
		}
		// 'code' goes out of scope here.

	}
}

