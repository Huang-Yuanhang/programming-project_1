#include <iostream>
#include <stdexcept>
#include "Debugger.h"
#include "Database.h"
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <algorithm>


using namespace std;

namespace Records {
			
	Employee& Database::addEmployee(const string& firstName,
	const string& middleName,const string& lastName)
		{
			log("started");
			Employee theEmployee(firstName,middleName, lastName);
			theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
			theEmployee.hire();
			mEmployees.push_back(theEmployee);
			log("end");
			return mEmployees[mEmployees.size() - 1];
		}


	Employee& Database::getEmployee(int employeeNumber)
		{
			for (auto& employee : mEmployees) {
				if (employee.getEmployeeNumber() == employeeNumber) {
					return employee;
				}
			}
			throw logic_error("No employee found.");
		}

	Employee& Database::getUserFromId(int userId)
	{
		for (auto& user : mUsers) {
			if (user.getId()==userId) {
				return user;
			}
		}
		throw logic_error("No User found.");
	}


	Employee& Database::getEmployee(const string& firstName, const string& lastName)
		{
			for (auto& employee : mEmployees) {
				if (employee.getFirstName() == firstName &&
					employee.getLastName() == lastName) {
						return employee;
				}
			}
			throw logic_error("No employee found.");
		}

	void Database::displayAll() const
		{
			for (const auto& employee : mEmployees) {
				employee.display();
			}
		}

	void Database::displayCurrent() const
		{
			for (const auto& employee : mEmployees) {
				if (employee.isHired())
					employee.display();
			}
		}

	void Database::displayFormer() const
		{
			for (const auto& employee : mEmployees) {
				if (!employee.isHired())
					employee.display();
			}
		}

	void Database::removeEmployee(int employeeNumber) {
        auto it = std::remove_if(mUsers.begin(), mUsers.end(),
            [employeeNumber](const Employee& emp) { return emp.getId() == employeeNumber; });

        if (it != mUsers.end()) {
            mUsers.erase(it, mUsers.end());
        } else {
            throw std::logic_error("Employee not found");
        }
    }

	string getSearchString(){
		string searchTag;
		cout << "Enter search string here-->" << endl;
		cin >> searchTag;
		return searchTag;

	}
	

	int displayseachMenu()
		{
			int selection;

			cout << endl;
			cout << "Search Employee Database" << endl;
			cout << "-----------------" << endl;
			cout << "1) Search by first name" << endl;
			cout << "2) Search by middle name" << endl;
			cout << "3) Search by last name" << endl;
			cout << "4) Search by address" << endl;
			cout << "0) Quit" << endl;
			cout << endl;
			cout << "---> ";
			
			cin >> selection;
			
			return selection;
		}

void Database::searchEmployee() const {
    bool done = false;
    Database searchResults;
    int selection; 
    while (!done) {
        selection = displayseachMenu(); // Assign 'selection' a value here
        switch (selection) {
            case 0:
                log("case 0");
                done = true;
                break;
            case 1:
                searchResults = searchBy(SearchOption::BY_FIRST);
                break;
            case 2:
                searchResults = searchBy(SearchOption::BY_MIDDLE);
                break;
            case 3:
                searchResults = searchBy(SearchOption::BY_LAST);
                break;
            case 4:
                searchResults = searchBy(SearchOption::BY_ADDRESS);
                break;
            default:
                cerr << "Unknown command." << endl;
                log("case default");
                break;
        }
    }

    string searchTag = getSearchString();
    bool foundMatch = false;

    for (const auto& e : mEmployees) {
        string target;
        switch (selection) {
            case 1:
                target = e.getFirstName();
                break;
            case 2:
                target = e.getMiddleName();
                break;
            case 3:
                target = e.getLastName();
                break;
            case 4:
                target = e.getAddress();
                break;
        }

        size_t pos = target.find(searchTag, 0);

        if (pos != string::npos) {
            cout << target << endl;
            e.display();
            foundMatch = true;
        }
    }

    if (!foundMatch) {
        cout << "No match" << endl;
    }
}


void Database::saveDBToFile() const {
    std::string filename;
    std::cout << "Enter the file name to save the employee database: ";
    std::cin >> filename;

    bool is_overwrite = false;
    std::cout << "Do you want to overwrite the existing file? Enter 1 for Yes, 0 for No: ";
    std::cin >> is_overwrite;

    try {
        std::ofstream outFile;
        if (is_overwrite) {
            outFile.open(filename, std::ios_base::trunc);
            if (!outFile.is_open()) {
                throw std::runtime_error("Error: Cannot open the file for overwriting.");
            }
        } else {
            outFile.open(filename, std::ios_base::app);
            if (!outFile.is_open()) {
                throw std::runtime_error("Error: Cannot open the file for appending.");
            }
        }

        for (const auto& employee : mEmployees) {
            outFile << std::quoted(employee.getFirstName()) << " "
                    << std::quoted(employee.getMiddleName()) << " "
                    << std::quoted(employee.getLastName()) << std::endl;
        }

        std::cout << (is_overwrite ? "File overwritten successfully." : "Data appended to the file. No overwriting.") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


	void Database::loadDBFromFile() 
		{
			string loadFile;
			vector<Employee> nEmployees;  // Create vector type employees container
			cout << "Enter the name of load file: " << endl;
			cin >> loadFile;
			ifstream inFile{ loadFile.data() };
			if (!inFile) {
				string errorString = "Cannot open file: ";
				throw runtime_error(errorString);
				}

			while (inFile) 
				{
					// Read line by line
					//skip empty lines.
					string line;
					getline(inFile, line);
					if (!inFile && !inFile.eof()) {
						throw runtime_error{ "Failed to read line from file." };
						}

					if (line.empty()) { // Skip empty lines
						continue;
						}
					// Make a string stream and parse it.
					
					istringstream inLine(line);
					string nfirstName, nmiddleName, nlastName;
					inLine >> quoted(nfirstName) >> quoted(nmiddleName) >> quoted(nlastName);

					if (inLine.bad()) {
							throw runtime_error{ "Error reading person. Ignoring." };
							continue;
						}
						// Create a employee and add it to the database nEmployees.
					nEmployees.push_back(Employee{nfirstName, nmiddleName, nlastName});
				}

			if (inFile.bad()) 
				{
					throw runtime_error{ "Error reading employee. Ignoring." };
				}
			
			int count=0; // Loading index
			// loading all the employees
			for (const auto& employee : nEmployees) 
				{
					count+=1;
					cout << "Employee Loading "<<count<<": "<< employee.getFirstName() << " " 
					<< employee.getMiddleName() << " " << employee.getLastName() << endl;
				}

		} 


		


}
