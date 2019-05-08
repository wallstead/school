/**
 * @file FlightMap.v1.cpp
 *
 * @brief Implementation file for the FlightMap Class
 *
 * @author Willis Allstead
 *
 * @details Implements functions for the FlightMap Class
 *
 * @version 0.50
 *
 */

#include "FlightMap.v1.h"

using namespace std;

/**
  * @brief Default constructor for the class
  *
  * @details constructs the class
  */
FlightMap::FlightMap(City cities[100], int cityCount) {
    for (int i = 0; i < cityCount; i++) {
        availableCities[i] = cities[i];
    }
    numCities = cityCount;
}

/**
  * @brief getIndexFromName function
  *
  * @details returns the index of the city, given a name
  */
int FlightMap::getIndexFromName(string name) {
    int cityIterator = 0;
    while((cityIterator < numCities) && (availableCities[cityIterator].getName() != name)) { // find the source city
        cityIterator++;
        // cout << cityIterator << endl;
    }
    return cityIterator;
}

/**
  * @brief markVisited function
  *
  * @details sets a city's visited boolean as true
  */
void FlightMap::markVisited(City &aCity) {
    aCity.visited = true;
}

/**
  * @brief unvisitAll function
  *
  * @details iterates through cities array and marks all as unvisited
  */
void FlightMap::unvisitAll() {
    int cityIterator = 0;
    while((cityIterator < numCities)) {
        availableCities[cityIterator].visited = false;
        cityIterator++;
    }
}

/**
  * @brief getNextCity function
  *
  * @details (supposed to return the next (unvisited) city)
  */
City FlightMap::getNextCity(City fromCity) {
    if (fromCity.adjacentCities.isEmpty()) {
        return fromCity; // return self if no others
    } else {
        return fromCity.adjacentCities.peek(); // Can't iterate through stack without losing elements.. how do I do this?
    }
}


/**
  * @brief isPath function
  *
  * @details (supposed to return a true if a destination can be visited, false otherwise)
  */
bool FlightMap::isPath(string originName, string destinationName) {

    City originCity = availableCities[getIndexFromName(originName)];
    City destinationCity = availableCities[getIndexFromName(destinationName)];
    cout << "Requested:\t" << originCity << "->" << destinationCity <<  endl;

    Stack<City> cityStack;

    unvisitAll(); // Clear marks on all cities

    // Push origin city onto cityStack and mark it as visited
    cityStack.push(originCity);

    cout << "Top of cityStack: " << cityStack.peek() << endl;
    markVisited(originCity);

    City topCity = cityStack.peek();

    // cout << topCity.getName() << "|" << destinationCity.getName() << endl;
    while (!cityStack.isEmpty() && (topCity.getName() != destinationCity.getName())) {
        // The stack contains a directed path from the origin city
        // at the bottom of the stack to the city at the top of the stack

        // Find an unvisited city adjacent to the city on the top of the stack
        City nextCity = getNextCity(topCity); // *Can't figure this part out*
        cout << "nextCity: " << nextCity << endl;

        if (nextCity.getName() == topCity.getName()) { // if next city is the same as top city still, we ran out of options
            cout << "*backtracking since same city*" << endl;
            cityStack.pop(); // No city found; backtrack
        } else { // Visit city
            cout << "*visiting next city*" << endl;
            cityStack.push(nextCity);
            cout << "pushing " << nextCity << " to cityStack" << endl;
            markVisited(nextCity);
        } // end if

        if (!cityStack.isEmpty()) {
            topCity = cityStack.peek();
        }
    } // end while

   return !cityStack.isEmpty();
}  // end isPath
