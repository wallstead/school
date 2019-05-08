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

#ifndef FLIGHTMAP_H // make sure we don't redefine class
#define FLIGHTMAP_H

#include <iostream>
#include "City.h"

using namespace std;

class FlightMap {
public:
    FlightMap(City cities[100], int cityCount); // custom construcor for the class
    int getIndexFromName(string name); // returns index of a city with a name
    void markVisited(City &aCity); // markes a supplied city as visited
    void unvisitAll(); // markes all cities as unvisited
    City getNextCity(City fromCity); // (supposed) to get next unviseted city and go to it
    bool isPath(string originName, string destinationName);

private:
    City availableCities[100];
    int numCities; // actual number of cities
};

#endif
