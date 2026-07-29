#pragma once
#include <string>
#include <variant>
#include <vector>

namespace Variant_Basic
{
	using DataValue = std::variant<int, double, std::string>;

	class Variant_Basic
	{
	public:
		// 1. Storage of variants (vector of variants)
		std::vector<DataValue> m_dataList;

		Variant_Basic();
		void clear();

		// 2. Add a value to the list
		// Uses perfect forwarding to accept any type that DataValue can hold.
		template<typename T>
		void addValue(T&& value);

		// 3. Check the type of the value at a specific index using std::holds_alternative
		// Returns the string name of the type held at the given index.
		std::string getTypeAtIndex(size_t index) const;

		// 4. Access the value using std::get<T>
		// Attempts to get the value as an integer. Throws if the held type is not int.
		int getIntAt(size_t index) const;

		// 5. Processing using std::visit (a basic visitor)
		// Uses std::visit to double the value if it's an int or double, or append '!!!' if it's a string.
		void processAllValues();

		// 6. Processing using std::visit to get a return value
		// Uses std::visit with a lambda (visitor) to convert the held value to a string representation.
		std::string convertValueToString(size_t index) const;
	};

	// Helper template implementation (must be in the header or before use)
	template<typename T>
	void Variant_Basic::addValue(T&& value)
	{
		m_dataList.emplace_back(std::forward<T>(value));
	}
}

