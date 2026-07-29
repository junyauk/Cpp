#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <vector>

namespace LambdaImprovements
{
	class LambdaCaptureExamples
	{
	public:
		static std::string copyCaptureExample();
		static std::string referenceCaptureExample();
		static std::string moveCaptureExample();
	};
}

