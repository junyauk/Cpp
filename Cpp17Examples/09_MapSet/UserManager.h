#pragma once
#include <map>
#include <string>
#include <optional>

namespace MapSetExamples
{
	class UserManager
	{
	private:
		std::map<std::string, int> users;
	public:
		bool RegisterUser_Insert(const std::string& name);
		bool RegisterUser_TryEmplace(const std::string& name);
		void RecodeLogin(const std::string& name);

		std::optional<int> GetLoginCount(const std::string& name) const;

		size_t Count() const { return users.size(); }
	};
}

