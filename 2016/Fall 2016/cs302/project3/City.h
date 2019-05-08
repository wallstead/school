/**
 * @file City.h
 *
 * @brief Header file for the City Class
 *
 * @author Willis Allstead
 *
 * @details Defines functions for the City Class
 *
 * @version 0.50
 *
 */
 
#ifndef CITY_H // make sure we don't redefine class
#define CITY_H

#include <iostream>
#include "Stack.cpp"

using namespace std;

class City {
public:
    bool visited; // if the city has been visited
    Stack<City> adjacentCities; // holds cities reachable from this city (This is where I had issues)

    City(); // default constructor
    City(string); // custom constructor
    City(const City &toCopy); // copy constructor
    void addAdjacentCity(City adjacent); // pushes a city to the stack
    string getName() const; // returns the name
    friend ostream& operator<<(ostream& out, const City& city); // for printing

private:
    string name; // name of the city
};

#endif
