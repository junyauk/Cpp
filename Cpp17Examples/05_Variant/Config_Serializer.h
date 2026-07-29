#pragma once
#include <variant>
#include <unordered_map>
#include <string>
#include <sstream>
#include <optional>
#include <stdexcept>

namespace ConfigSerializerSample
{
	using ConfigValue = std::variant<int, double, std::string, bool>;

	class ConfigSerializer
	{
	public:
		using ConfigMap = std::unordered_map<std::string, ConfigValue>;

		static std::string serialize(const ConfigMap& config)
		{
			std::ostringstream oss;
			oss << "{";
			bool first = true;
			for (const auto& [key, value] : config)
			{
				if (!first) oss << ",";
				oss << "\"" << key << "\":";
				std::visit([&oss](auto&& v)
					{
						using T = std::decay_t<decltype(v)>;
						if constexpr (std::is_same_v<T, std::string>)
						{
							oss << "\"" << v << "\":";
						}
						else if constexpr (std::is_same_v<T, bool>)
						{
							oss << (v ? "true" : "false");
						}
						else
						{
							oss << v;
						}
					}, value);
				first = false;
			}
			oss << "}";
			return oss.str();
		}

		static std::optional<ConfigValue> parseValue(const std::string& str)
		{
			if (str == "true") return true;
			if (str == "false") return false;

			size_t start = (str[0] == '+' || str[0] == '-') ? 1 : 0;

			bool isNumeric = str.find_first_not_of("0123456789.", start) == std::string::npos;

			if (std::count(str.begin(), str.begin() + str.size(), '.') > 1)
			{
				isNumeric = false;
			}

			if (isNumeric)
			{
				// numbers
				if (str.find('.') != std::string::npos)
				{
					return std::stod(str);
				}
				else
				{
					return std::stoi(str);
				}
			}
			else
			{
				// strings
				if (str.size() > 2 && str.front() == '"' && str.back() == '"')
				{
					return str.substr(1, str.size() - 2);
				}
			}
			return std::nullopt;
		}

		static ConfigMap deserialize(const std::string& str)
		{
			ConfigMap map;
			size_t pos = 0;

			while (true)
			{
				pos = str.find('"', pos);
				if (pos == std::string::npos) break;

				size_t endKey = str.find('"', pos + 1);
				std::string key = str.substr(pos+1, endKey - pos - 1);

				size_t colon = str.find(':', endKey);
				size_t comma = str.find_first_of(',', colon);
				if (comma == std::string::npos)
				{
					comma = str.size() - 1;
				}
				std::string valueStr = str.substr(colon + 1, comma - colon - 1);

				valueStr.erase(0, valueStr.find_first_not_of(" \t\n\r"));
				valueStr.erase(valueStr.find_last_not_of(" \t\n\r") + 1);

				auto val = parseValue(valueStr);
				if (val)
				{
					map[key] = *val;
				}

				pos = comma;
			}
			return map;
		}
	};

	class ConfigManager
	{
	public:
		using ConfigMap = std::unordered_map<std::string, ConfigValue>;

		void set(const std::string& key, ConfigValue value)
		{
			configData_[key] = std::move(value);
		}

		template<typename T>
		std::optional<T> get(const std::string& key) const
		{
			auto it = configData_.find(key);
			if (it == configData_.end()) return std::nullopt;
			auto& val = it->second; // reference to the variant
			if (auto p = std::get_if<T>(&val)) // direct type match
			{
				return *p;
			}
			return convert<T>(val); // try type conversion
		}

		template<typename T>
		T getOrDefault(const std::string& key, const T& defaultValue) const
		{
			auto val = get<T>(key); // try to get the value
			return val.has_value() ? *val : defaultValue; // return value or default
		}

		template<typename T>
		std::map<std::string, T> getSection(const std::string& section)const
		{
			std::map<std::string, T> result{};
			for (auto&[key, value] : configData_)
			{
				if (key.rfind(section + ".", 0) == 0)
				{
					if (auto strVal = convert<T>(value))
					{
						result[key.substr(section.size() + 1)] = *strVal;
					}
				}
			}
			return result;
		}

		bool contains(const std::string& key) const
		{
			for (const auto & [k, v] : configData_)
			{
				if (getKey(k) == key)
				{
					return true;
				}
			}
			return false;
		}

		int getIntOrDefault(const std::string& key, int defaultValue) const
		{
			return getOrDefault<int>(key, defaultValue);
		}
		double getDoubleOrDefault(const std::string& key, double defaultValue) const
		{
			return getOrDefault<double>(key, defaultValue);
		}
		std::string getStringOrDefault(const std::string& key, const std::string& defaultValue) const
		{
			return getOrDefault<std::string>(key, defaultValue);
		}
		bool getBoolOrDefault(const std::string& key, bool defaultValue) const
		{
			return getOrDefault<bool>(key, defaultValue);
		}

		std::vector<std::string> getKeys() const
		{
			std::vector<std::string> keys;
			keys.reserve(configData_.size());
			for (const auto& [key, value] : configData_)
			{
				keys.push_back(getKey(key));
			}
			return keys;
		}

		template<typename T>
		std::map<std::string, T> getSectionMap(const std::string& section) const
		{
			std::map<std::string, T> result;
			for (auto& [k, v] : configData_)
			{
				if (auto s = getSection(k); s.has_value() && *s == section)
				{
					if constexpr ( std::is_same_v<T, ConfigValue>)
					{
						result[getKey(k)] = v;
					}
					else if (auto val = convert<T>(v))
					{
						result[getKey(k)] = *val;
					}
				}
			}
			return result;
		}

	private:
		ConfigMap configData_;

		template<typename T>
		std::optional<T> convert(const ConfigValue& value) const
		{
			if constexpr (std::is_same_v<T, int>)
			{ // convert to int
				if (auto p = std::get_if<double>(&value))
				{ // convert double to int
					return static_cast<int>(*p);
				}
				else if (auto p = std::get_if<std::string>(&value))
				{ // convert string to int
					try
					{
						return std::stoi(*p);
					}
					catch (...)
					{
						return std::nullopt;
					}
				}
			}
			else if constexpr (std::is_same_v<T, double>)
			{ // convert to double
				if (auto p = std::get_if<int>(&value))
				{ // convert int to double
					return static_cast<double>(*p);
				}
				else if (auto p = std::get_if<std::string>(&value))
				{ // convert string to double
					try
					{
						return std::stod(*p);
					}
					catch (...)
					{
						return std::nullopt;
					}
				}
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{ // convert to string
				if (auto p = std::get_if<int>(&value))
				{ // convert int to string
					return std::to_string(*p);
				}
				else if (auto p = std::get_if<double>(&value))
				{ // convert double to string
					return std::to_string(*p);
				}
				else if (auto p = std::get_if<bool>(&value))
				{ // convert bool to string
					return *p ? "true" : "false";
				}
				else if (auto p = std::get_if<std::string>(&value))
				{ // already string
					return *p;
				}
			}
			else if constexpr (std::is_same_v<T, bool>)
			{ // convert to bool
				if (auto p = std::get_if<int>(&value))
				{ // convert int to bool
					return *p != 0;
				}
				if (auto p = std::get_if<std::string>(&value))
				{ // convert string to bool
					if (*p == "true" || *p == "1") return true;
					if (*p == "false"|| *p == "0") return false;
				}
			}
			return std::nullopt;
		}

		std::optional<std::string> getSection(const std::string& key) const
		{
			size_t pos = key.find('.');
			if (pos != std::string::npos)
			{ // section.key
				return key.substr(0, pos);
			}
			else
			{ // plain key
				return std::nullopt;
			}
		}

		std::string getKey(const std::string& fullKey) const
		{ // extract plain key from section.key
			size_t pos = fullKey.find('.');
			if (pos != std::string::npos)
			{ // section.key
				return fullKey.substr(pos + 1);
			}
			else
			{ // plain key
				return fullKey;
			}
		}
	};

}
