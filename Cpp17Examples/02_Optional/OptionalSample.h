#pragma once
#include <optional>
#include <vector>
#include <string>
#include <charconv>

namespace OptionalSamples
{
	std::optional<std::string> toStringIfPositive(int value);
	std::optional<size_t> getLengthIfHasValue(const std::optional<std::string>& strOpt);
	std::string getValueOrDefault(const std::optional<std::string>& strOpt, const std::string& defaultValue);

	std::optional<int> makeOptionalInt(int value);
	void reEmplaceValue(std::optional<std::string>& opt, const std::string& newValue);
	void resetOptional(std::optional<std::string>& opt);
	std::optional<size_t> findInVector(const std::vector<int>& vec, int target);

	std::optional<int> parseInt(const std::string& text);
	struct Config
	{
		std::optional<int> port;
	};
	struct Settings
	{
		std::optional<bool> enableLogging;
	};
}

