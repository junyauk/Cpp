#pragma once
#include <Windows.h>
#include <string>
#include "loganalysisresult.h"

namespace Ex05_ThreadPool_IO
{
	class ILogProcessor
	{
	public:
		virtual ~ILogProcessor() = default;
		virtual LogAnalysisResult Process(const std::wstring& filePath) = 0;
	};
}
