#include "pch.h"
#include "framework.h"
#include "OptionalSample.h"


namespace OptionalSamples
{
	std::optional<std::string> toStringIfPositive(int value)
	{
		if (value > 0)
		{
			return std::to_string(value);
		}
		return std::nullopt;
	}
	std::optional<size_t> getLengthIfHasValue(const std::optional<std::string>& strOpt)
	{
		if (strOpt)
		{
			return strOpt->size();
		}
		return std::nullopt;
	}
	std::string getValueOrDefault(const std::optional<std::string>& strOpt, const std::string& defaultValue)
	{
		return strOpt.value_or(defaultValue);
	}

	std::optional<int> makeOptionalInt(int value)
	{
		return std::make_optional<int>(value);
	}
	void reEmplaceValue(std::optional<std::string>& opt, const std::string& newValue)
	{
		opt.emplace(newValue);
	}
	void resetOptional(std::optional<std::string>& opt)
	{
		opt.reset();
	}
	std::optional<size_t> findInVector(const std::vector<int>& vec, int target)
	{
		for (auto i = 0; i < vec.size(); ++i)
		{
			if (vec[i] == target)
			{
				return i;
			}
		}
		return std::nullopt;
	}

	std::optional<int> parseInt(const std::string& text)
	{
		int value{};
		auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
		if (ec == std::errc())
		{
			return value;
		}
		return std::nullopt;
	}
}
