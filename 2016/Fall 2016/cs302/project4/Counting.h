/**
 * @file Counting.h
 *
 * @brief Header file for the Counting sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Counting sorting class
 *
 * @version 1.0
 *
 */

#ifndef Counting_H // make sure we don't redefine class
#define Counting_H

#include <iostream>
#include <ctime> // for keeping track of time

using namespace std;

class Counting {
public:
    int count;
    int *countingArray;
    int *data;
    double elapsedTime; // CPU time specifically
    int comparisonCount;
    int swapCount;

    Counting(int toSort[], int count);

    // Sorts the data.
    // @pre  data member has been filled with data.
    //       count is the amount of items in data.
    // @post  data member is now sorted from low to high.
    void sort();

    friend ostream& operator<<(ostream& out, const Counting& Counting);
};

#endif
