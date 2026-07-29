import ModuleT;
import <string>;

namespace moduleexample::modulet
{
	template<typename T>
	T twice(T v)
	{
		return v * 2;
	}

	template<typename T>
	Box<T>::Box(const T& value) : m_value(value) {}

	template<typename T>
	T Box<T>::get() const { return m_value; }

	template<typename T>
	void Box<T>::set(const T& value) { m_value = value; }

	// Explicit instantiations can be located anywhere in the module implementation unit
	// does't need to be in a header or interface unit
	template class Box<int>;
	template class Box<std::string>;

	template class Pair<int, int>;
	template class Pair<std::string, int>;

	// ------------------------------------------------------------------------
	// Generic NumberBox template
	template<typename T>
	NumberBox<T>::NumberBox(T value) : m_value(value){}
	template<typename T>
	T NumberBox<T>::get() const { return m_value; }

	// Explicit instantiations for NumberBox
	NumberBox<std::string>::NumberBox(std::string value) : m_value(value) {}
	size_t NumberBox<std::string>::get() const { return m_value.size(); }

	// Adapter to use NumberBox with INumberProvider
	template<typename T>
	NumberBoxAdapter<T>::NumberBoxAdapter(T value) : m_numberBox(value) {}
	template<typename T>
	size_t NumberBoxAdapter<T>::getValue() const { return m_numberBox.get(); }

	// ------------------------------------------------------------------------
	std::unique_ptr<INumberProvider> CreateIntNumberProvider(int value)
	{
		return std::make_unique<NumberBoxAdapter<int>>(value);
	}
	std::unique_ptr<INumberProvider> CreateStringNumberProvider(const std::string& value)
	{
		return std::make_unique<NumberBoxAdapter<std::string>>(value);
	}

}

