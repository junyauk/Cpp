#pragma once
#include <map>
#include <string>
#include <iostream>
#include <utility>

namespace StructuredBinding
{
	struct Point
	{
		int x;
		int y;
		std::string label;
	};
}

namespace STRUCTUREDBINDING_Basic
{
	class StructuredBinding_Basic
	{
	public:
		// Member to hold a map for demonstration
		std::map<int, std::string> m_dataMap;
		StructuredBinding_Basic();
		void clear();

		// 1. Structured Binding with a std::pair (e.g., from std::map insertion)
		// Returns true if insertion was successful, false otherwise (key already exists).
		bool insertToMap(int key, const std::string& value);

		// 2. Structured Binding with a custom struct
		// Returns the label of the Point object using structured binding.
		std::string getLabelFromStruct(int x, int y, const std::string& label);

		// 3. Structured Binding with a std::tuple
		// Concatenates the string and integer from the tuple, separated by a comma.
		std::string procssTuple(const std::tuple<std::string, int>& dataTuple);
	};
}
