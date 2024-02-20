#include <iostream>
#include <stdexcept>
#include <exception>
#include "Debugger.h"
#include "Database.h"

#include <cstddef>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);
void doEdit(Database& db);
Database generateNewDB();

int main()
{
	Database employeeDB;

	bool done = false;
	while (!done) {
		int selection = displayMenu();
		switch (selection) {
		case 0:
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
            	case 7:
                	employeeDB=generateNewDB();
                	break;
            	case 8:
                	employeeDB.saveDBToFile();
                	break;
            	case 9:
	                employeeDB.loadDBFromFile();
	                break;
		case 10:
	                doEdit(employeeDB);
	                break;
                case 11:
	                employeeDB.searchEmployee();
	                break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Make new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl;
    cout << "11) Search employee" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
}

void doHire(Database& db)
{
    log("start");
    string firstName;
    string lastName;

    cout << "First name? ";
    cin >> firstName;
    cout << "Last name? ";
    cin >> lastName;
    
    db.addEmployee(firstName, lastName);
    log("end");
}

void doFire(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
}

void doEdit(Database& db)
{
    int employeeNumber;
    cout << "Enter employee number: ";
    cin >> employeeNumber;

    try 
    {
        Employee& emp = db.getEmployee(employeeNumber);
        bool done = false;

        while (!done)
        {
            emp.display();
            int intOption;
            cout << "1) Edit Salary" << endl;
            cout << "2) Edit Address" << endl;
            cout << "3) Edit Hire Status" << endl;
            cout << "0) Quit" << endl;
            cin >> intOption;
            int newSalary;
            string newAddress; 
            bool hireStatus;            
            switch (intOption)
            {
                case 0:
                    cout << "Quit editing" << endl;
                    done = true;
                    break;
                case 1:   
                    cout << "Enter new salary: ";
                    cin >> newSalary;         
                    emp.setSalary(newSalary);
                    break; 

                case 2:
                    cout << "Enter new address: "; 
                    cin.ignore();
                    getline(cin, newAddress);                  
                    emp.setAddress(newAddress);
                    break;  
                case 3: 
                    cout << "Edit hire status: Enter '1' to hire or '0' to fire: ";
                    cin >> hireStatus; 
                    if (hireStatus) {
                        emp.hire();
                        cout << "Hire Status Updated to: Hired" << endl;
                    } else {
                        emp.fire();
                        cout << "Hire Status Updated to: Fired" << endl;
                    }  
                    break;
                    
                emp.display();
            }
        }
    } 
    catch (const std::logic_error& exception) 
    {
        cerr << "Unable to edit employee: " << exception.what() << endl;
    }
}

Database generateNewDB()
    {
    vector<string> arrFirst{
        "Ann", "Bob", "Cathy", "Ann2", "Bob2", "Cathy2", "3Ann3", "Bob3", "Cathy3", "Ann4", "Bob4", "Cathy4"
    };
    vector<string> arrMiddle{
        "Don", "Bob", "Cathy", "Don2", "Bob2", "Cathy2", "Don3", "Bob3", "Cathy3", "Don4", "Bob4", "Cathy4"
    };
    vector<string> arrLast{
        "Smith", "Lily", "Steven", "Jim", "Smith2", "Lily1", "Steven1", "Jim1", "Smith3", "Lily2", "Steven2", "Jim2"
    };

        Database db;
        int count=0;

        for (const string& firstName:arrFirst){
            for (const string& middleName:arrMiddle){
                for (const string& lastName:arrLast){
                count++;
                Employee& empl = db.addEmployee(firstName, middleName, lastName);


                stringstream addressBuilder;
                addressBuilder << count << " street# Cairns";
                empl.setAddress(addressBuilder.str());

                cout<< "your employee database is ready" << endl;
                
   
                }
            }
        }
        return db;
    }
