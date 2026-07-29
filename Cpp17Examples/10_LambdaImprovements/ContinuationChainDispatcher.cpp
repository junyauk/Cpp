#include "pch.h"
#include <iostream>
#include <string>
#include "ContinuationChainDispatcher.h"

namespace LambdaImprovements
{
	void RunContinuationChainDispatcherExample()
	{
		// 1) Simple chain of continuations
		auto node1 = ContinuationChainDispatcher::submit([]() { return std::string{ "Hello" }; });
		auto node2 = node1.then([](const std::string& msg) { return msg + " world"; });
		auto node3 = node2.then([](const std::string& msg) { return msg + "!"; });
		std::string result = node3.get();
		std::cout << "Result: " << result << std::endl; // Should print "Hello world!"

		// 2) void -> value chain
		auto v0 = ContinuationChainDispatcher::submit([]() { /* do something */});
		auto v1 = v0.then([]() { return 123; });
		int x = v1.get();
		std::cout << "x = " << x << std::endl; // Should print 123

		// 3) exception propagation
		auto bad = ContinuationChainDispatcher::submit([]() -> int {throw std::runtime_error("Boom"); });
		auto con = bad.then([](int val) {return val + 1; });
		try
		{
			con.get();
		}
		catch(const std::exception& e)
		{
			std::cout << "Caught exception from chain: " << e.what() << std::endl; // Should print "Boom"
		}

	}

}
