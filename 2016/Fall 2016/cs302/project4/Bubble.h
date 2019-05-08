/**
 * @file Bubble.h
 *
 * @brief Header file for the Bubble sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Bubble sorting class
 *
 * @version 1.0
 *
 */

#ifndef BUBBLE_H // make sure we don't redefine class
#define BUBBLE_H

#include <iostream>
#include <ctime> // for keeping track of time

using namespace std;

class Bubble {
public:
    /* Decided on these being public for ease of use. In a professional setting I would make these private */
    int count;
    int *data;
    double elapsedTime; // CPU time specifically
    int comparisonCount;
    int swapCount;

    Bubble(int toSort[], int count);

    // Sorts the data.
    // @pre  data member has been filled with data.
    //       count is the amount of items in data.
    // @post  data member is now sorted from low to high.
    void sort();

    friend ostream& operator<<(ostream& out, const Bubble& bubble);
};

#endif
