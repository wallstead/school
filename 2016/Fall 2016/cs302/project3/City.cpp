/**
 * @file City.cpp
 *
 * @brief Implementation file for the City Class
 *
 * @author Willis Allstead
 *
 * @details Implements functions for the City Class
 *
 * @version 0.50
 *
 */

#include "City.h"

/**
  * @brief Default constructor for the class
  *
  * @details constructs the class
  */
City::City() {}

/**
  * @brief Copy constructor for the class
  *
  * @details constructs the class from a copy
  */
City::City(const City &toCopy) {
    name = toCopy.name;
    visited = toCopy.visited;
    adjacentCities = toCopy.adjacentCities;
}

/**
  * @brief Custom constructor for the class
  *
  * @details constructs the class from the name of a city
  */
City::City(string cityName) {
    name = cityName;
}

/**
  * @brief getName function
  *
  * @details returns the name of the city
  */
string City::getName() const {
    return name;
}

/**
  * @brief addAdjacentCity function
  *
  * @details pushes a city to the adjacentCities stack
  */
void City::addAdjacentCity(City adjacent) {
    adjacentCities.push(adjacent);
}

/**
  * @brief ostream << overloader
  *
  * @details enables printing with cout
  */
ostream& operator<< (ostream& out, const City& city) {
    out << city.name;
    return out;
}
