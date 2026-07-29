#include "pch.h"
#include "framework.h"
#include "UserManager.h"

namespace MapSetExamples
{
	bool UserManager::RegisterUser_Insert(const std::string& name)
	{
		auto [it, inserted] = users.insert({ name, 0 });
		return inserted;
	}
	bool UserManager::RegisterUser_TryEmplace(const std::string& name)
	{
		auto [it, inserted] = users.try_emplace(name, 0);
		return inserted;
	}
	void UserManager::RecodeLogin(const std::string& name)
	{
		auto [it, inserted] = users.insert_or_assign(name, users[name]+1);
	}

	std::optional<int> UserManager::GetLoginCount(const std::string& name) const
	{
		if (auto it = users.find(name); it != users.end())
		{
			return it->second;
		}
		return std::nullopt;
	}
}

