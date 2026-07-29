#include "pch.h"
#include "MapSetAdvanced.h"

namespace MapSetAdvanced
{
	void setEmployeeName(EmployeeMap& m, int id, const std::string& name)
	{
		m[id] = name;
	}

	std::string getEmployeeNameAt(const EmployeeMap& m, int id)
	{
		return m.at(id);
	}

	void changeEmployeeId(EmployeeMap& m, int oldId, int newId)
	{
		auto handle = m.extract(oldId);
		if (!handle.empty())
		{
			handle.key() = newId;
			m.insert(std::move(handle));
		}
	}

	std::vector<std::pair<int, std::string>> getAllEmployees(const EmployeeMap& m)
	{
		std::vector<std::pair<int, std::string>> result;
		for (const auto& kv: m)
		{
			result.push_back(kv);
		}
		return result;
	}

	bool changeEmployeeIdWithExtract(EmployeeMap& m, int oldId, int newId)
	{
		auto node = m.extract(oldId); // extract will unlink the node from the tree
		if (!node)
		{
			return false;
		}

		node.key() = newId;
		m.insert(std::move(node));
		return true;
	}

	bool changeEmployeeIdWithoutExtract(EmployeeMap& m, int oldId, int newId)
	{
		auto it = m.find(oldId);
		if (it == m.end())
		{
			return false;
		}

		auto v = std::move(it->second);
		m.erase(it);
		m.emplace(newId, std::move(v)); // or m.insert( {newId, std::move(v)} );
		return true;
	}



}
