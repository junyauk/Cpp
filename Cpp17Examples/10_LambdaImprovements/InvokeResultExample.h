#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <functional>
#include <utility>

namespace InvokeResultExample
{
	// Note:
	// decltype() vs declval<>()
	// 
	// - decltype()
	//   For getting type of formula or function.
	// - declval<>()
	//   For virtually generate a "value of that type" without creating an object

	// Examples of decltype():
	// 
	// int a = 5;			// a is int
	// decltype(a) b = 2;	// b is int
	// decltype((a)) c = a;	// (a) is int&, c is int&
	// 
	// int f();
	// decltype(f()) val;	// The return value of f() is int, so val is int;

	// Examples of declval<>()
	// This is defined as function template, and it is not called.
	// 
	// std::declval<T>()	// Returning "T&&" (rvalue of T)
	// 
	// struct NoDefault // This struct doesn't have default constructor
	// {
	//		NoDefault(int){}
	//		int get() const {return 42;}
	// }
	// 
	// This struct can't create an instance like this "NoDefault obj".
	// But only you need is type, then you can use declval<NoDefault>().
	//
	// decltype(declval<NoDefault>().get()) val;
	// - declval<NoDefault>()
	//		It is treated as "a virtually generated right-hand side value of type NoDefault."
	// - .get()
	//		Use the type returned by declval<NoResult>() virtually and check the return value of get() method.
	// - decltype(...)
	//		Check the result type of NoDefault.get()
	// Then the type of val is int.
	//
	// So...
	// std::invoke_result_t<F, Args...> is internally
	// 
	// template<typename F, typename... Args>
	// using invoke_result_t = decltype(std::declval<F>()(std::declval<Args>()...));
	// 
	// 1. std::declval<F>()			: Makes a function object(F) "callable" without actually creating it.
	// 2. (std::declval<Args>()...) : Prepares virtual arguments.
	// 3. decltype(...)				: Infers the type of the call result.



	// Func 1
	int add(int a, int b) { return a + b; }
	// Func 2
	auto concat = [](const std::string& a, const std::string& b) { return a + b; };

	template<typename F, typename... Args>
	void checkInvokeResult(F&& func, Args&&...)
	{
		// 1. Using std::invoke_result_t<>
		using InvokeResult = std::invoke_result_t<F, Args...>;

		// 2. Using decltype(std::invoke(...))
		// Note:
		// std::invoke_result_t<> is internally doing this.
		using DecltypeResult = decltype(std::invoke(std::declval<F>(), std::declval<Args>()...));

		// Check if they are the same
		std::cout << std::boolalpha
			<< "Is same type?"
			<< std::is_same_v<InvokeResult, DecltypeResult>
			<< std::endl;
	}

	void Run_CheckInvokeResult()
	{
		// Using typical function
		checkInvokeResult(add, 1, 2);
		// Using lambda
		checkInvokeResult(concat, std::string("Hello"), std::string("World"));

		// Results
		// 
		// Is same type? true
		// Is same type? true
	}
}
