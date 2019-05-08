#include "Logger.h"

// Constructor
Logger::Logger() {}

// Parameterized constructor
Logger::Logger(bool file, bool console, string name)
{
    printToFile = file;
    printToScreen = console;

    if (printToFile) {
        fileName = name;
    }
    else {
        fileName = " ";
    }
}

// Destructor
Logger::~Logger()
{
    if (printToFile) {
        clearStream();
    }
}

// Loads in configuration data into the object
void Logger::loadFromConfig(bool file, bool console, string name)
{
    printToFile = file;
    printToScreen = console;

    if (printToFile) {
        fileName = name;
    }
    else {
        fileName = " ";
    }
}

// Logs a string
void Logger::log(string output)
{
    if (printToFile) {
        buffer << output << endl;
    }

    if (printToScreen) {
        cout << output << endl;
    }
}

// Logs a timestamp
void Logger::timeStamp(long double time)
{
    if (printToFile) {
        buffer << fixed;
        buffer << setprecision(6);
        buffer << time << " - ";
    }

    if (printToScreen) {
        cout << fixed;
        cout << setprecision(6);
        cout << time << " - ";
    }
}

// clears the stream
void Logger::clearStream()
{
    if (printToFile) {
        ofstream output;
        output.open(fileName.c_str(), ofstream::out);

        output << buffer.rdbuf();
        output.close();
    }
}
