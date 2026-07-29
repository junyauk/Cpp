#include "pch.h"
#include "LambdaCaptureExamples.h"
#include <sstream>

namespace LambdaImprovements
{
	std::string LambdaCaptureExamples::copyCaptureExample()
	{
		int value = 42;
		auto lambda = [value]() // when the line is compiled the value is captured
			{
				std::ostringstream oss;
				oss << "Captured value (copy):" << value;
				return oss.str();
			};

		value = 100; // this value will never affect
		return lambda();
	}
	std::string LambdaCaptureExamples::referenceCaptureExample()
	{
		int value = 42;
		auto lambda = [&value]()
			{
				std::ostringstream oss;
				oss << "Captured value (ref):" << value;
				return oss.str();
			};
		value = 100;
		return lambda(); // The updated value 100 wil be used
	}
	std::string LambdaCaptureExamples::moveCaptureExample()
	{
		std::vector<int> data = { 1,2,3 };
		auto lambda = [moved = std::move(data)]()
			{
				std::ostringstream oss;
				oss << "Captured value (move):";
				for (auto n : moved)
				{
					oss << n << " ";
				}
				return oss.str();
			};

		// Note
		// Elements in the data have already been moved
		// after the lambda was compiled.

		std::ostringstream oss;
		oss << lambda();
		oss << " | Original size: " << data.size();
		return oss.str();
	}
}

