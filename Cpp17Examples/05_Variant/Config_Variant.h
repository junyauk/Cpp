#pragma once
#include <optional>
#include <vector>
#include <string>
#include <variant>
#include <map>

namespace ConfigVariantExample
{
	using ConfigValue = std::variant<int, double, std::string, bool>;

	class Config
	{
	public:
		void set(const std::string& key, ConfigValue value)
		{
			data_[key] = std::move(value);
		}

		template<typename T>
		std::optional<T> get(const std::string& key) const
		{
			auto it = data_.find(key);
			if (it == data_.end()) return std::nullopt;

			if (auto val = std::get_if<T>(&it->second))
			{
				return *val;
			}
			return std::nullopt;
		}
	private:
		std::map<std::string, ConfigValue> data_;
	};
}
