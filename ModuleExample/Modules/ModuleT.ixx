export module ModuleT;

import <string>;
import <sstream>;
import <memory>;

namespace moduleexample::modulet
{
	// ------------------------------------------------------------------------
	// Simple function template
	export template<typename T> T twice(T v);

	// ------------------------------------------------------------------------
	// Simple Box template
	export template<typename T>
	class Box
	{
	private:
		T m_value;
	public:
		Box(const T& value);

		T get() const;
		void set(const T& value);
	};

	// ------------------------------------------------------------------------
	// Generic Pair template
	export template<typename T, typename U>
		class Pair
	{
	private:
		T m_first;
		U m_second;
	public:
		Pair(T& first, U& second) : m_first(first), m_second(second) {}
		T getFirst() const { return m_first; }
		U getSecond() const { return m_second; }
		void setFirst(T value) { m_first = value; }
		void setSecond(U value) { m_second = value; }

		std::string to_string() const
		{
			std::ostringstream oss;
			oss << m_first << ", " << m_second;
			return oss.str();
		}
	};

	// ------------------------------------------------------------------------
	// Generic NumberBox template
	export template<typename T>
	class NumberBox
	{
	private:
		T m_value;
	public:
		NumberBox(T value);
		T get() const;
	};

	// Specialization of NumberBox for std::string
	export template<>
	class NumberBox<std::string>
	{
	private:
		std::string m_value;
	public:
		NumberBox(std::string value);
		size_t get() const;
	};

	// interface for providing a number
	export class INumberProvider
	{
	public:
		virtual ~INumberProvider() = default;
		virtual size_t getValue() const = 0;
	};

	// Adapter to use NumberBox with INumberProvider
	export template<typename T>
	class NumberBoxAdapter : public INumberProvider
	{
	private:
		NumberBox<T> m_numberBox;
	public:
		NumberBoxAdapter(T value);
		size_t getValue() const override;
	};

	// ------------------------------------------------------------------------
	export std::unique_ptr<INumberProvider> CreateIntNumberProvider(int value);
	export std::unique_ptr<INumberProvider> CreateStringNumberProvider(const std::string& value);

}
