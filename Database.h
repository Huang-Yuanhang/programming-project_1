#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;
	const int kFirstUerId =0;

	class Database
	{
	public:
		Employee& addEmployee(Employee& emp1);	
			

		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);	

		Employee& createUser(const int& id, const std::string& password);

		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName);


		Employee& getEmployee(int employeeNumber);

		Employee& getUserFromId(int userId);
		
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;
		void saveDBToFile() const;
		void loadDBFromFile();
		void searchEmployee() const;
		
	void removeEmployee(int employeeNumber);
	
	private:
		std::vector<Employee> mEmployees;
		std::vector<Employee> mUsers;
		
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		int mNextUserId = kFirstUerId;


		enum class SearchOption{
			BY_FIRST,BY_MIDDLE,BY_LAST,BY_ADDRESS

		};
		Database searchBy(SearchOption op) const;
	};
}
