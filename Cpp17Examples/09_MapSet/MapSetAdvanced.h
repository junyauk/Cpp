#pragma once
#include <map>
#include <string>
#include <vector>

namespace MapSetAdvanced
{
	using EmployeeMap = std::map<int, std::string>;

	void setEmployeeName(EmployeeMap& m, int id, const std::string& name);

	std::string getEmployeeNameAt(const EmployeeMap& m, int id);

	void changeEmployeeId(EmployeeMap& m, int oldId, int newId);
	bool changeEmployeeIdWithExtract(EmployeeMap& m, int oldId, int newId);
	bool changeEmployeeIdWithoutExtract(EmployeeMap& m, int oldId, int newId);

	std::vector<std::pair<int, std::string>> getAllEmployees(const EmployeeMap& m);
}
