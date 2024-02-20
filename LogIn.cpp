#include <iostream>
#include <string>
#include "LogIn.h"

namespace Records {
    // Constructor for the LogIn class, used to initialize the username and password mappings
    // as well as the user level mapping
    LogIn::LogIn(const std::string& userName,
                 const std::string& password,
                 bool employeeLevel) {
        mapLogIn.insert({userName, password});
        mapUserStatus.insert({userName, employeeLevel});
    }

    bool LogIn::validate(const std::string& user, const std::string& pass) const {
        for (const auto& entry : mapLogIn) {
            if (entry.first == user && entry.second == pass) {
                std::cout << "Access granted" << std::endl;
                return true;
            }
        }
        std::cout << "Access denied" << std::endl;
        return false;
    }

    bool LogIn::checkStatus(const std::string& user) const {
        auto itr = mapUserStatus.find(user);
        if (itr != mapUserStatus.end() && itr->second) {
            std::cout << "You have Manager status" << std::endl;
            return true;
        }
        std::cout << "You only have employee status" << std::endl;
        return false;
    }

    void LogIn::display() const {
        std::cout << "USER\tPASSWORD\n"; 
        for (const auto& entry : mapLogIn) { 
            std::cout << entry.first << '\t' << entry.second << '\n'; 
        }
    }

} 
