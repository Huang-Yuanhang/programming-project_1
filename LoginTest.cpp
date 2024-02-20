#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>
#include "LogInDataBase.h"

using namespace std;
using namespace Records;
// Function prototypes
int employeeDisplayMenu();
void signUp(LogInDataBase& logInDB);
bool validate(LogInDataBase& logInDB);

int main()
{
    LogInDataBase logInDB;

    while (true)
    {
        int choice = employeeDisplayMenu();

        switch (choice)
        {
            case 1:
                signUp(logInDB);
                break;
            case 2:
                if (validate(logInDB))
                {
                    cout << "Login successful!" << endl;
                }
                else
                {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                break;
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

int employeeDisplayMenu()
{
    int userSelection;

    cout << endl;
    cout << "Select from the following options: " << endl;
    cout << "1) Sign-up" << endl;
    cout << "2) Log-in" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    cin >> userSelection;

    return userSelection;
}

void signUp(LogInDataBase& logInDB)
{
    string user, pass;
    bool manager = false;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;
    cout << "Are you a manager (true or false): ";
    cin >> manager;
    cout << endl;

    logInDB.addNewUser(user, pass, manager);
    cout << "Welcome " << user << endl;
}

bool validate(LogInDataBase& logInDB)
{
    string user, pass;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    try
    {
        LogIn& userToCheck = logInDB.getUser(user, pass);
        return true; // Successful login
    }
    catch (const std::invalid_argument& e)
    {
        return false; // Invalid username or password
    }
}
