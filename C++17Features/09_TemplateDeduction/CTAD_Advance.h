#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <initializer_list>

namespace CTAD_Advance
{
	// --- 1. Applications in User-Defined Classes : MyVector ---
	// A simplified template class to manage a dynamic array.
	template<typename T>
	class MyVector
	{
	private:
		std::vector<T> m_data;
	public:
		// Constructor 1: Takes an initial capacity (T must be default constructible)
		explicit MyVector(size_t capacity) : m_data(capacity) {}

		// Constructor 2: Takes an initializer list (T must be copyable/moveable)
		MyVector(std::initializer_list<T> list) : m_data(list) {}

		// Constructor 3: Takes a pointer and a size
		MyVector(const T* ptr, size_t size) : m_data(ptr, ptr + size) {}

		// Constructor 4: Take a standard map (to utilize the deduction guide)
		template <typename Iterator>
		MyVector(Iterator first, Iterator last) : m_data(first, last) {}

		size_t size() const { return m_data.size(); }
		const T& get(size_t index) const { return m_data.at(index); }
		const std::vector<T>& data() const { return m_data; }
	};

	// --- 1. User define deduction guide ---
	// Enables CTAD for MyVector when initialized with different types.
	// Case A: Initializer List of T's
	template<typename T>
	MyVector(std::initializer_list<T>) -> MyVector<T>;

	// Case B: Explicitly deduce type T from a pointer and size_t
	template<typename T>
	MyVector(const T*, size_t) -> MyVector<T>;

	// Case C: For a map (demonstrating deduction for nested types)
	template <typename Iterator>
	MyVector(Iterator first, Iterator last)
		-> MyVector<typename std::iterator_traits<Iterator>::value_type>;

	class CTAD_Advance
	{
	public:
		// 2. Application: Standard Library Check
		// Shows how std::map is initialized without explicit template arguments.
		static std::map<int, std::string> createStandardMap();

		// 1. Application: User-Defined Class Check
		// Returns an instance of MyVector initialized via CTAD.
		static MyVector<int> createCustomVector();

		// 3. Application: Partial Deduction and Constraint Check (Tested directly in unit tests)
	};
}
