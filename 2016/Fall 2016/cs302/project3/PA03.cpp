/**
 * @file PA03.cpp
 *
 * @brief Implementation file for the the main driver
 *
 * @author Willis Allstead
 *
 * @details Runs all the code in the project
 *
 * @version 0.50
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Stack.cpp"
#include "City.h"
#include "FlightMap.v1.h"

using namespace std;

int main () {
    City cities[100];

    /* Get all available cities */

    ifstream cityFile("cityFile.txt");
    string cityName;
    int cityCounter = 0;
    if (cityFile.is_open()) {
        while (getline(cityFile, cityName)) {
            string fixedName = cityName.substr(0, cityName.length()-1); // getting rid of weird character that breaks everything
            cities[cityCounter] = City(fixedName);
            cityCounter++;
        }
        cityFile.close();
    } else {
        cout << "Cannot open file";
    }

    /* Get all available flight paths and add them to their corresponding cities */
    
    ifstream flightFile("flightFile.txt");
    string line;
    if (flightFile.is_open()) {
        while(getline(flightFile, line) ) {
            string commaDelim = ", ";
            string source = line.substr(0, line.find(commaDelim));
            // cout << source << endl;
            line.erase(0, line.find(commaDelim) + commaDelim.length());

            string tabDelim = "\t";
            string destination = line.substr(0, line.find(tabDelim));
            // cout << destination << endl;
            line.erase(0, line.find(tabDelim) + tabDelim.length());

            string spaceDelim = " ";
            string number = line.substr(0, line.find(spaceDelim));
            // cout << number << endl;
            line.erase(0, line.find(spaceDelim) + spaceDelim.length());

            string endDelim = "\n";
            string price = line.substr(0, line.find(endDelim));
            // cout << price << endl;
            line.erase(0, line.find(endDelim) + endDelim.length());

            /* Add this info to each city */
            int cityIterator = 0;
            while((cityIterator < cityCounter) && (cities[cityIterator].getName() != source)) { // find the source city
                // cout <<  cities[cityIterator].getName() << endl;
                cityIterator++;
            }

            cities[cityIterator].addAdjacentCity(destination);

            cout << "Added " << destination << " to adjacent cities of " << cities[cityIterator] << endl;
        }
        flightFile.close();
    } else {
        cout << "Cannot open file";
    }

    /* Get all requested flights and calculate if the are possible */

    ifstream requestFile("requestFile.txt");
    string requestLine;
    if (requestFile.is_open()) {
        while(getline(requestFile, requestLine) ) {
            string commaDelim = ", ";
            string source = requestLine.substr(0, requestLine.find(commaDelim));
            requestLine.erase(0, requestLine.find(commaDelim) + commaDelim.length());

            string endDelim = "\n";
            string dest = requestLine.substr(0, requestLine.find(endDelim));
            requestLine.erase(0, requestLine.find(endDelim) + endDelim.length());
            string fixedDest = dest.substr(0, dest.length()-1);

            FlightMap map = FlightMap(cities, cityCounter);
            cout << map.isPath(source, fixedDest) << endl; // use this bool to show if the path is possible
        }
        requestFile.close();
    } else {
        cout << "Cannot open file";
    }
    return 0;
}
