#pragma once
#include <cstddef>
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
using namespace std;

#define DEBUG_MODE
#ifdef DEBUG_MODE
    class Debugger
    {
    public:
        template<typename... Args>
        static void log(const Args&... args)
        {
            ofstream logfile { msDebugFileName};
            if (logfile.fail()) {
            cerr << "Unable to open debug file!" << endl;
            return;
            }
  
        ((logfile << args),...);
        logfile << endl;

        ((cout << args), ...);
        cout << "\n";
        }

    private:
    static const string msDebugFileName;
    };

const string Debugger::msDebugFileName = "debugLogFile.txt";
    #define log(...) Debugger::log(__func__, "(): ", __VA_ARGS__)
#else
    #define log(...)
#endif