/**
 * @file Merge.h
 *
 * @brief Header file for the Merge sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Merge sorting class
 *
 * @version 1.0
 *
 */

#ifndef MERGE_H // make sure we don't redefine class
#define MERGE_H

#include <iostream>
#include <ctime> // for keeping track of time

using namespace std;

class Merge {
public:
    int count;
    int *data;
    double elapsedTime; // CPU time specifically
    int comparisonCount;
    int swapCount;

    Merge(int toSort[], long count);

    // merges two halves of an array together
    // @post  The array in the bounds given has been merged.
    void merge(long first, long mid, long last);

    // Sorts the data.
    // @pre  data member has been filled with data.
    //       count is the amount of items in data.
    // @param first  index of the first element in the array to be sorted.
    //        last   index of the last element in the array to be sorted.
    // @post  data member is now sorted from low to high.
    void sort(long first, long last);

    friend ostream& operator<<(ostream& out, const Merge& merge);
};

#endif
