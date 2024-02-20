#pragma once

#include <string>

namespace Records {
	const int kDefaultStartingSalary = 30000;
	class Employee
	{
	public:
		Employee() = default;

		Employee(const std::string& firstName, const std::string& lastName);

		Employee(const std::string& firstName, 
				const std::string& middleName,
				const std::string& lastName);


		void promote(int raiseAmount = 1000);
		void demote(int demeritAmount = 1000);
		void hire(); // Hires or rehires the employee
		void fire(); // Dismisses the employee
		void display() const;// Outputs employee info to console


		// Getters and setters
		void setFirstName(const std::string& firstName);
		const std::string& getFirstName() const;

		void setMiddleName(const std::string& middleName);
		const std::string& getMiddleName() const;


		void setLastName(const std::string& lastName);
		const std::string& getLastName() const;

		void setEmployeeNumber(int employeeNumber);
		int getEmployeeNumber() const;

		void setAddress(const std::string& address);
		const std::string& getAddress() const;


		void setSalary(int newSalary);
		int getSalary() const;

		bool isHired() const;

		void setId(const int& id);
		const int& getId() const;
		
	private:
		std::string mFirstName;
		std::string mLastName;
		std::string mMiddleName;
		std::string mAddress;
		int m_id;
		int mEmployeeNumber = -1;
		int mSalary = kDefaultStartingSalary;
		bool mHired = false;

	};
}
