#include "pch.h"
#include "RemovePrefixSuffix.h"
#include <string>
#include <string_view>

namespace StringViewExamples
{
	std::string_view getFileName(std::string_view path)
	{
		size_t pos = path.find_last_of("/\\");
		if (pos != std::string_view::npos)
		{
			path.remove_prefix(pos + 1);
		}

		auto dot = path.find_last_of('.');
		if (dot != std::string_view::npos)
		{
			path.remove_suffix(path.size() - dot);
		}
		return path; // return the modified view
	}

	std::string_view getExtension(std::string_view path)
	{
		auto dot = path.find_last_of('.');
		if (dot != std::string_view::npos && dot + 1 < path.size())
		{
			path.remove_prefix(dot + 1);
			return path;
		}

		return {}; // return empty view if no extension
	}
}
