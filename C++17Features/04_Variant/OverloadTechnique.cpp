#include "pch.h"
#include "OverloadTechnique.h"

namespace OverloadTechniqueExamples
{
	std::string UsingIndexAndGet(const InputType& v)
	{
		switch (v.index())
		{
		case 0: // must be int in the InputType
			return "Value is int (" + std::to_string(std::get<int>(v)) + ")";
			break;
		case 1: // must be double in the InputType
			return "Value is double (" + std::to_string(std::get<double>(v)) + ")";
			break;
		case 2: // must be std::string in the InputType
			return "Value is std::string (" + std::get<std::string>(v) + ")";
			break;
		}
		// Note:
		// std::get<> will return std::bad_variant_access, if the type is not correct

		return "Unknown";
	}

	std::string UsingGetIf(const InputType& v)
	{
		if (const int* pVal = std::get_if<int>(&v))
		{
			return "Value is int (" + std::to_string(*pVal) + ")";
		}
		else if (const double* pVal = std::get_if<double>(&v))
		{
			return "Value is double (" + std::to_string(*pVal) + ")";
		}
		else if (const std::string* pVal = std::get_if<std::string>(&v))
		{
			return "Value is std::string (" + *pVal + ")";
		}
		return "Unknown";
	}

	std::string UsingHoldsAlternative(const InputType& v)
	{
		// Note:
		// std::holds_alternative was designed and used for std::variant only.
		// 
		// std::holds_alternative and std::get will check the type.
		// So type checking is done twice.
		//
		// Consider using std::get_if instead of using the combination of std::holds_alternative & std::get
		//
		// But ideally, using std::visit and functor is the best practice.

		if (std::holds_alternative<int>(v))
		{
			return "Value is int (" + std::to_string(std::get<int>(v)) + ")";
		}
		else if (std::holds_alternative<double>(v))
		{
			return "Value is double (" + std::to_string(std::get<double>(v)) + ")";
		}
		else if (std::holds_alternative<std::string>(v))
		{
			return "Value is std::string (" + std::get<std::string>(v) + ")";
		}
		return "Value is unknown type";
	}


	// Note:
	// Generally "std::visit" is used for retrieve the stored value in appropriate type.
	// Then the overload structure has lambda functions corresponding to the types set in std::variant.
	// Therefore the visitor (or functor) SHOULD RETURN THE SAME VALUE TYPE FOR ALL INPUT.
	// 
	// However it can return various types if the return type is std::variant.
	// It means that it will use "std::visit" again. It's redundant!
	// So that's why visitor (or functor) should return the same value type.
	// 
	// std::visit can return a value that the lambda stored in the overload struct returns.
	// The lambdas can return various different value, and std::visit will return std::variant.

	// Best practice
	std::string UsingVisitWithSingleLambdaAndConstexpr(const InputType& v)
	{
		auto visitor = [](const auto& arg) -> std::string
			{
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, int>)
				{
					return "Value is int (" + std::to_string(arg) + ")";	// No need to use std::get<int>
				}
				else if constexpr (std::is_same_v<T, double>)
				{
					return "Value is double (" + std::to_string(arg) + ")";	// No need to use std::get<double>
				}
				else if constexpr (std::is_same_v<T, std::string>)
				{
					return "Value is std::string (" + arg + ")";			// No need to use std::get<std::string>
				}
				return "Value is unknown type";
			};
		return std::visit(visitor, v);
	}

	// Best practice ( better )
	std::string UsingVisitWithFunctor(const InputType& v)
	{
		// Note:
		// Using the functor "overload" defined in the header file.
		auto visitor = overload
		{
			[](int n) -> std::string { return "Value is int (" + std::to_string(n) + ")"; },
			[](double d) -> std::string { return "Value is double (" + std::to_string(d) + ")"; },
			// It would be better to use ref type if the parameter is class type
			[](const std::string& s) -> std::string { return "Value is std::string (" + s + ")"; }
		};
		return std::visit(visitor, v);
	}

	void OverloadTechnique_NoReturn()
	{
		std::variant<int, double, std::string> data;

		auto visitor = overload
		{
			[](int n) { std::cout << "int: " << n << std::endl; },
			[](double d) { std::cout << "double: " << d << std::endl; },
			[](std::string s) { std::cout << "std::string: " << s << std::endl; }
		};
		// int
		data = 42;
		std::visit(visitor, data);	// Lambda for int is used

		data = 3.1415;
		std::visit(visitor, data);	// Lambda for double is used

		data = std::string{ "Hello World!" };
		std::visit(visitor, data);	// Lambda for std::string is used
	}

	// Generally visitor (or functor) used by std::visit should return the same value type
	void OverloadTechnique_SameTypeReturn()
	{
		std::variant<int, double, std::string> data;

		auto visitor = overload
		{
			[](int n) -> std::string { return "int"; },
			[](double d) -> std::string { return "double"; },
			[](std::string s) -> std::string { return "std::string"; }
		};

		std::string result;

		data = 42;
		result = std::visit(visitor, data);
		std::cout << "Value is " << result << std::endl;

		data = 3.14;
		result = std::visit(visitor, data);
		std::cout << "Value is " << result << std::endl;

		data = std::string{ "Hello World!" };
		result = std::visit(visitor, data);
		std::cout << "Value is " << result << std::endl;
	}

	// Note:
	// This is possible that visitor (or functor) can return various value type.
	// But it's BAD DESIGN!!
	void OverloadTechnique_VariousTypeReturn()
	{
		std::variant<int, double, std::string> data;

		auto visitor = overload
		{
			[](int n) -> ReturnType { return n; },
			[](double d) -> ReturnType { return d; },
			[](std::string s) -> ReturnType {return s; }
		};

		ReturnType result;

		data = 42;
		result = std::visit(visitor, data);
		if (const int* pInt = std::get_if<int>(&result)) // Using std::get_if. Just for as a different example
		{
			std::cout << "Value is int: " << std::to_string(*pInt) << std::endl;
		}
		else
		{
			std::cout << "Something else" << std::endl;
		}

		data = 3.14;
		result = std::visit(visitor, data);
		if (std::holds_alternative<double>(result)) // Using std::holds_alternative
		{
			std::cout << "Value is double: " << std::to_string(std::get<double>(result)) << std::endl;
		}
		else
		{
			std::cout << "Something else" << std::endl;
		}

		data = std::string{ "Hello World!" };
		result = std::visit(visitor, data);
		if (std::holds_alternative<std::string>(result))
		{
			std::cout << "Value is std::string: " << std::get<std::string>(result) << std::endl;
		}
		else
		{
			std::cout << "Something std::string" << std::endl;
		}
	}

	void OverloadTechnique_ContainVoidReturn()
	{
		std::variant<int, double, std::string> data;

		auto visitor = overload
		{
			// Note:
			// Functor should have the same return value type "ReturnType".
			[](int n) -> ReturnType { return n; },
			[](double d) -> ReturnType { return std::monostate{}; },
			[](std::string s) -> ReturnType {return s; }
		};

		ReturnType result;

		data = 42;
		result = std::visit(visitor, data);
		if (const int* pInt = std::get_if<int>(&result))
		{
			std::cout << "Value is int: " << std::to_string(*pInt) << std::endl;
		}
		else
		{
			std::cout << "Something else" << std::endl;
		}

		data = 3.14;
		result = std::visit(visitor, data);
		if (std::holds_alternative<std::monostate>(result))
		{
			std::cout << "Value is double returning std::monostate.\n";
		}
		else
		{
			std::cout << "Something else" << std::endl;
		}

		data = std::string{ "Hello World!" };
		result = std::visit(visitor, data);
		if (const std::string *pStr = std::get_if<std::string>(&result))
		{
			std::cout << "Value is std::string: " << *pStr << std::endl;
		}
		else
		{
			std::cout << "Something std::string" << std::endl;
		}
	}
}
