#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "LogInDataBase.h"

namespace Records {

    LogIn& LogInDataBase::addNewUser(const std::string& userName,
                                     const std::string& password,
                                     bool employeeLevel) {
        LogIn newUser(userName, password, employeeLevel);
        mLogInDB.push_back(newUser);
        return mLogInDB.back(); 
    }

    LogIn& LogInDataBase::getUser(const std::string& userName,
                                  const std::string& password) {
        for (LogIn& user : mLogInDB) {
            if (user.validate(userName, password)) {
                std::cout << "Access granted" << std::endl;
                return user;
            }
        }
        std::cout << "Access denied" << std::endl;
        throw std::runtime_error("Access denied"); 
    }
    // Displays all users in the database.
    void LogInDataBase::displayAll() const {
        for (const LogIn& user : mLogInDB) {
            user.display();
        }
    }

} 
