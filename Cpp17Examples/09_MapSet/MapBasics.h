#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>

namespace MapSetExamples
{
	class MapBasics
	{
	public:
		static std::map<std::string, int> insertExamples();
		static std::optional<int> findExample(const std::map<std::string, int>& m, std::string& key);
		static std::optional<int> atExample(const std::map<std::string, int>& m, std::string& key);
		static std::map<std::string, int> eraseExamples();
		static std::map<std::string, int> updateExamples();
		static int sumValues(const std::map<std::string, int>& m);
		static bool capacityExamples();
		static std::vector<std::string> orderedKeys();
		static std::vector<std::string> unorderedKeys();
	};
}

