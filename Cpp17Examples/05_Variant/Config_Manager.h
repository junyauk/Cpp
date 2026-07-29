#pragma once
#include <optional>
#include <variant>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <any>

namespace ConfigManagerUsingVisitExample
{
	using ConfigValue = std::variant<std::monostate, int, double, std::string, bool>;

	class ConfigManager
	{
		using ConfigMap = std::unordered_map<std::string, ConfigValue>;
	public:
		void set(const std::string& key, const ConfigValue& value)
		{
			configData_[key] = value;
		}

		template<typename T>
		std::optional<T> get(const std::string& key) const
		{
			for (auto &[k,v] : configData_)
			{
				if (getKey(k) == key)
				{
					if (auto p = std::get_if<T>(&v)) // direct type match
					{
						return *p;
					}
					return convert<T>(v); // try type conversion
				}
			}
		}

		template<typename T>
		std::map<std::string, T> getSectionMap(const std::string& section) const
		{
			std::map<std::string, T> result;
			for (auto &[k,v] : configData_)
			{
				if (auto s = getSection<T>(k); s.has_value() && *s == section)
				{
					if constexpr (std::is_same_v<T, ConfigValue>)
					{
						result[getkey(k)] = v;
					}
					else
					{
						if (auto converted = convert<T>(v); converted.has_value())
						{
							result[getKey(k)] = *converted;
						}
					}
				}
			}
			eturn result;
		}

		std::string toString(const ConfigValue& value) const
		{
			return std::visit([](auto&& arg) -> std::string
				{
					using u = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<u, std::monostate>)
					{
						return "null";
					}
					else if constexpr (std::is_same_v<u, std::string>)
					{
						return arg;
					}
					else if constexpr (std::is_same_v<u, bool>)
					{
						return arg ? "true" : "false";
					}
					else
					{
						return std::to_string(arg);
					}
				}, value);
		}

		template<typename T>
		static std::optional<T> convert(const ConfigValue& value)
		{
			return std::visit([&value](auto&& arg) -> std::optional<T>
				{
					using u = std::decay_t<decltype(arg)>;

					if constexpr (std::is_same_v<u, std::monostate>)
					{ // null value
						return std::nullopt;
					}

					if constexpr (std::is_same_v<u, T>)
					{ // same type
						return std::optional<T>{arg};
					}

					if constexpr (std::is_same_v<T, int>)
					{ // convert to int
						if constexpr (std::is_same_v<u, double>)
						{ // double to int
							return std::optional<T>{static_cast<int>(arg)};
						}
						else if constexpr (std::is_same_v<u, std::string>)
						{ // string to int
							try
							{
								return std::optional<T>{std::stoi(arg)};
							}
							catch (...)
							{
								return std::nullopt;
							}
						}
						else if constexpr (std::is_same_v<u, bool>)
						{ // bool to int
							return std::optional<T>{arg ? 1 : 0};
						}
						return std::nullopt;
					}
					else if constexpr (std::is_same_v<T, double>)
					{ // convert to double
						if constexpr (std::is_same_v<u, int>)
						{ // int to double
							return std::optional<T>{static_cast<double>(arg)};
						}
						else if constexpr (std::is_same_v<u, std::string>)
						{ // string to double
							try
							{
								return std::optional<T>{ std::stod(arg) };
							}
							catch (...)
							{
								return std::nullopt;
							}
						}
						else if constexpr (std::is_same_v<u, bool>)
						{ // bool to double
							return std::optional<T>{arg ? 1.0 : 0.0};
						}
						return std::nullopt;
					}
					else if constexpr (std::is_same_v<T, std::string>)
					{ // convert to string
						if constexpr (std::is_same_v<u, int>)
						{ // int to string
							return std::optional<T>{std::to_string(arg)};
						}
						else if constexpr (std::is_same_v<u, double>)
						{ // double to string
							return std::optional<T>{std::to_string(arg)};
						}
						else if constexpr (std::is_same_v<u, bool>)
						{ // bool to string
							return std::optional<T>{arg ? "true" : "false"};
						}
						return std::nullopt;
					}
					else if constexpr (std::is_same_v<T, bool>)
					{ // convert to bool
						if constexpr (std::is_same_v<u, int>)
						{ // int to bool
							return std::optional<T>{arg != 0};
						}
						else if constexpr (std::is_same_v<u, double>)
						{ // double to bool
							return std::optional<T>{arg != 0.0};
						}
						else if constexpr (std::is_same_v<u, std::string>)
						{ // string to bool
							if (arg == "true" || arg == "1") return std::optional<T>{true};
							if (arg == "false" || arg == "0") return std::optional<T>{false};
							return std::nullopt;
						}
						return std::nullopt;
					}
					return std::nullopt;
				}, value);
		}

	private:
		ConfigMap configData_;

		template<typename T>
		std::optional<std::string> getSection(const std::string& key) const
		{
			auto pos = key.find(".");
			if (pos != std::string::npos && key.find(".", pos+1) == std::string::npos)
			{
				return std::optional<std::string>(key.substr(0, pos));
			}
			return std::nullopt;
		}

		std::string getKey(const std::string& key) const
		{
			auto pos = key.find(".");
			if (pos != std::string::npos)
			{
				return key.substr(pos + 1);
			}
			return key;
		}

	};

	// Helper for std::visit with multiple lambdas
	template<class... Ts>
	struct Overloaded : Ts...{ using Ts::operator()...; };
	// CTAD(Class Template Argument Deduction) for Overloaded
	template<class... Ts> 
	Overloaded(Ts...) -> Overloaded<Ts...>;

	struct MoveOnly
	{
		std::string data;

		MoveOnly(std::string d) : data(std::move(d)) {}

		// copy constructor deleted
		MoveOnly(const MoveOnly&) = delete;
		MoveOnly& operator=(const MoveOnly&) = delete;

		// move constructor
		MoveOnly(MoveOnly&& other) noexcept : data(std::move(other.data)) {}
		MoveOnly& operator=(MoveOnly&& other) noexcept
		{
			if (this != &other)
			{
				data = std::move(other.data);
			}
			return *this;
		}
	};

	void sample_holds_alternative()
	{
		std::cout << "[1] holds_alternative example\n";

		std::variant<int, std::string> v = 42;
		if (std::holds_alternative<int>(v))
		{
			std::cout << "variant holds int: " << std::get<int>(v) << "\n";
		}

		v = std::string("hello");
		if (std::holds_alternative<std::string>(v))
		{
			std::cout << "variant holds string: " << std::get<std::string>(v) << "\n";
		}
	}

	void sample_visit_overloaded()
	{
		std::cout << "\n[2] visit with overloaded lambdas example\n";
		std::variant<int, std::string, double> v;

		v = 3.14;
		std::visit(Overloaded{
			[](int arg) { std::cout << "int: " << arg << "\n"; },
			[](const std::string& arg) { std::cout << "string: " << arg << "\n"; },
			[](double arg) { std::cout << "double: " << arg << "\n"; }
			}, v);

		v = std::string("hi");
		std::visit(Overloaded{
			[](int arg) { std::cout << "int: " << arg << "\n"; },
			[](const std::string& arg) { std::cout << "string: " << arg << "\n"; },
			[](double arg) { std::cout << "double: " << arg << "\n"; }
			}, v);
	}

	void sample_any()
	{
		std::cout << "\n[3] std::any example\n";
		std::any a = 42;
		std::cout << "any holds int: " << std::any_cast<int>(a) << "\n";

		a = std::string("world");
		try
		{
			std::cout << "any holds string: " << std::any_cast<std::string>(a) << "\n";
		}
		catch (const std::bad_any_cast& e)
		{
			std::cout << "bad any cast: " << e.what() << "\n";
		}
	}

	void sample_moveonly_variant()
	{
		std::cout << "\n[4] variant with MoveOnly\n";
		std::variant<int, MoveOnly> v{ MoveOnly("data") };
		v = MoveOnly( "new data" );

		std::visit(Overloaded{
			[](int arg) { std::cout << "int: " << arg << "\n"; },
			[](const MoveOnly& arg) { std::cout << "MoveOnly: " << arg.data << "\n"; }
			}, v);

		// This would cause a build error
		// std::variant<int, MoveOnly> v2 = v; // copy not allowed
	}
}

