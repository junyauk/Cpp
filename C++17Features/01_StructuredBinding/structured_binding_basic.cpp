#include "pch.h"
#include "framework.h"
#include "..\01_StructuredBinding\structured_binding_basic.h"

using namespace StructuredBinding;
namespace STRUCTUREDBINDING_Basic
{
	StructuredBinding_Basic::StructuredBinding_Basic()
	{
		// Initialize with some default data
		m_dataMap.insert({ 1, "One" });
		m_dataMap.insert({ 2, "Two" });
	}
	void StructuredBinding_Basic::clear()
	{
		// Clear the map
		m_dataMap.clear();
	}

	// 1. Structured Binding with std::pair (from std::map insertion)
	bool StructuredBinding_Basic::insertToMap(int key, const std::string& value)
	{
		// std::map::insert returns std::pair<iterator, bool>
		// The structured binding extracts both the iterator (element_it) and the boolean (inserted).
		auto [element_it, iterated] = m_dataMap.insert({ key, value });

		// Although element_it is not used here, the core concept is demonstrated:
		// simultaneously extracting multiple return values into named variables.
		return iterated;
	}

	// 2. Structured Binding with a custom struct
	std::string StructuredBinding_Basic::getLabelFromStruct(int x, int y, const std::string& label)
	{
		Point pt{ x, y, label };

		// Structured binding extracts members of the struct 'p' into new variables x_val, y_val, and label_val.
		// The order in the binding must match the order of declaration in the struct.
		auto [x_val, y_val, label_val] = pt;

		// Return the label value
		return label_val;
	}

	// 3. Structured Binding with a std::tuple
	std::string StructuredBinding_Basic::procssTuple(const std::tuple<std::string, int>& dataTuple)
	{
		// Structured binding extracts elements of the tuple into new variables
		auto [text, number] = dataTuple;

		// Combine the extracted values
		return text + "," + std::to_string(number);
	}
}
