#pragma once
#include <string>
#include <map>
#include <optional>
#include <vector>

namespace IFSWITCHINIT_Basic
{
	class IfSwitchInit_Basic
	{
	public:
		IfSwitchInit_Basic();
		void clear();

		// 1. Example using if-initializer with map::find
		// Checks if a key exists in m_lookupTable and returns the corresponding value if found.
		std::optional<std::string> getValueIfKeyExists(int key);

		// 2. Example using if-initializer with an object that needs limited scope
		// Calculates a complex metric and returns it only if it meets a threshold.
		// The metric object is destroyed upon exiting the if block.
		std::optional<int> calculateMetricIfValid(int rawValue, int threshold);

		// 3. Example using switch-initializer
		// Processes a status code based on a value retrieved from a function call.
		std::string processStatusCode(int initialValue);
	private:
		std::map<int, std::string> m_lookupTable;
	};

	// A simple class to demonstrate RAII and scope limitation
	class ComplexMetric
	{
	private:
		int m_value;
	public:
		ComplexMetric(int rawValue) : m_value(rawValue * 2) {}
		int getValue() const { return m_value; }
	};
}

