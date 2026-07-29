#include "pch.h"
#include "framework.h"
#include <iostream>
#include <stdexcept>
#include "Variant_Basic.h"

namespace Variant_Basic
{
	// A simple visitor struct/functor (C++17 doesn't require the generic lambda or C++20's Concepts for this basic form)
	// This is defined inside the cpp file for implementation details related to processAllValues.
	struct ValueProcesser
	{
		void operator()(int& i) const
		{
			i *= 2;
		}
		// Overload for double
		void operator()(double& d) const
		{
			d *= 2.0;
		}
		// Overload for std::string
		void operator()(std::string& s) const
		{
			s += "!!!";
		}
	};

	Variant_Basic::Variant_Basic()
	{
		// Initialize with some data
		addValue(42);						// int
		addValue(3.14);						// double
		addValue(std::string{ "Hello" });	// std::string
	}

	void Variant_Basic::clear()
	{
		m_dataList.clear();
	}

	// 3. Check the type of the value
	std::string Variant_Basic::getTypeAtIndex(size_t index) const
	{
		if (index >= m_dataList.size())
		{
			throw std::out_of_range("Index out of bounds");
		}

		const DataValue& v = m_dataList.at(index);
		if (std::holds_alternative<int>(v))
		{
			return "int";
		}
		else if (std::holds_alternative<double>(v))
		{
			return "double";
		}
		else if (std::holds_alternative<std::string>(v))
		{
			return "std::string";
		}

		// Should not happen for this variant type
		return "Unknown";
	}

	// 4. Access the value using std::get<T>
	int Variant_Basic::getIntAt(size_t index) const
	{
		if (index >= m_dataList.size())
		{
			throw std::out_of_range("Index out of bounds");
		}

		// std::get<T>() throws std::bad_variant_access if the type T is not held.
		return std::get<int>(m_dataList.at(index));
	}

	// 5. Processing using std::visit
	void Variant_Basic::processAllValues()
	{
		ValueProcesser vp;

		for (DataValue& v : m_dataList)
		{
			// std::visit calls the appropriate overload in the ValueProcessor functor based on the type held by 'v'.
			std::visit(vp, v);
		}
	}

	// 6. Processing using std::visit to get a return value
	std::string Variant_Basic::convertValueToString(size_t index) const
	{
		if (index >= m_dataList.size())
		{
			throw std::out_of_range("Index out of bounds");
		}

		const auto& v = m_dataList.at(index);

		// Define a C++17 generic lambda as the visitor.
		// The lambda's return type is deduced as std::string (the common return type of the branches).
		auto visitor = [](const auto& arg) -> std::string
			{
				using T = std::decay_t<decltype(arg)>;

				// You will ned to list all supported cases here usin if/else
				if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>)
				{
					// Convert int or double to string
					return std::to_string(arg);
				}
				else if constexpr (std::is_same_v<T, std::string>)
				{
					// Return string directly
					return arg;
				}
				else
				{
					// Fallback (should not happen with this variant definition)
					return "Unsupported Type";
				}
			};

		// std::visit calls the lambda with the currently held value.
		// The return value of the lambda is the return value of std::visit.
		return std::visit(visitor, v);
	}


}

