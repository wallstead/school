#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip> // considering this an "IO Library"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Logger {
public:
    Logger();
    Logger(bool, bool, string);
    ~Logger();

    void loadFromConfig(bool, bool, string);
    void log(string);
    void timeStamp(long double);
    void clearStream();

private:
    bool printToFile;
    bool printToScreen;
    string fileName;
    stringstream buffer;
};

#endif
