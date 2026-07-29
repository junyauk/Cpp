#pragma once
#include <string>

namespace PerfectForwardingExplanation
{
	// Explanation of perfect forwarding (using T&& and std::forward<T> in template)
	class Explanation
	{
	private:
		// handle lvalue ref
		static void printType(const std::string& s) { std::cout << "lvalue reference: " << s << std::endl; }
		// handle rvalue ref
		static void printType(std::string&& s) { std::cout << "rvalue reference (moved): " << s << std::endl; }

	public:
		template<typename T>
		static void forwardToPrintNG(T arg)
		{
			printType(arg); // !!! This is the problem !!!
			// Note:
			// This "(T arg)" can't identify if it's lvalue or rvalue.
		}

		template<typename T>
		static void forwardToPrintBetter(T&& arg) // using T&& is good to pass both lvalue & rvalue
		{
			// Note:
			// The "arg" will be passed as rvalue.
			printType(arg); // but the "arg" is treated lvalue here.
		}

		template<typename T>
		static void forwardToPrintOK(T&& arg)
		{
			// The type of T is checked if it's rvalue, and forwarded as same as the original.
			printType(std::forward<T>(arg));
		}

		static void run()
		{
			std::string str = "Alice";	// this "str" is lvalue

			forwardToPrintNG(str); // lvalue
			forwardToPrintNG(std::string("Bob")); // call with rvalue, BUT it is processed as lvalue (copy)

			// Results
			// lvalue reference: Alice
			// lvalue reference: Bob			<= !!! NG !!!

			// Note:
			// The result of template argument deduction,
			// std::string("Bob") is copied as lvalue
			// So "(T arg)" is not clear enough, it needs to be explicit

			forwardToPrintBetter(str); // lvalue
			forwardToPrintBetter(std::string("Bob")); // call with rvalue, BUT it is still processed as lvalue (copy)

			// Results
			// lvalue reference: Alice
			// lvalue reference: Bob			<= !!! NG !!!

			forwardToPrintOK(str); // lvalue
			forwardToPrintOK(std::string("Bob")); // call with rvalue, it is processed as rvalue (move)

			// Results
			// lvalue reference: Alice
			// rvalue reference (moved): Bob	<= !!! OK !!!
		}
	};

	// Key points:
	// - use auto&& or T&& (for template)
	// - std::forward<T>(arg), that forwarding the original lvalue/rvalue type
	// - std::move(arg), that always move arg as rvalue


	inline void print(const char* tag, std::true_type, std::ostream& os)  { os << tag << " (lvalue)"; }
	inline void print(const char* tag, std::false_type, std::ostream& os) { os << tag << " (rvalue)"; }

	template<typename T>
	void analyzeForwarding(T&& arg, const char* name, std::ostream& os)
	{
		// checking directly arg whether if arg is lvalue or rvalue
		constexpr bool isLvalue = std::is_lvalue_reference_v<decltype(arg)>; // using decltype(arg)
		print(name, std::bool_constant<isLvalue>{}, os);
	}

	template<typename T>
	void analyzeStdForward(T&& arg, const char* name, std::ostream& os)
	{
		// checking the type after forwarded arg whether if arg is lvalue or rvalue
		constexpr bool isLvalue = std::is_lvalue_reference_v<decltype(std::forward<T>(arg))>; // using decltype(std::forward<T>(arg))
		print(name, std::bool_constant<isLvalue>{}, os);
	}

	// Note:
	// The following 2 methods will return the same value but meaning or purpose is different.
	// 
	// - using decltype(arg)
	//    What is the actual argument that this function is currently receiving?
	//    For checking whether if the current arg is lvalue or rvalue.
	// 
	// - using decltype(std::forward<T>(arg))
	//	  How std::forward reconstructs value categories based on type T.
	//    For checking whether what the transfered type will be.
}


namespace LambdaImprovements
{
	class LambdaPerfectForwardExample
	{
	public:
		static std::string compareCopyAndPerfectForward();
	};
}

