/**
 * @file Counting.cpp
 *
 * @brief Implementation file for the Counting sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the functions of the Counting sorting class
 *
 * @version 1.0
 *
 */

#include "Counting.h"

Counting::Counting(int toSort[], int count) {
    this->count = count; // set count
    data = new int[count]; // create array of size count
    for (int i = 0; i < count; i++) {
        data[i] = toSort[i]; // copy elements of int array
    }

    elapsedTime = 0;
    comparisonCount = 0;
    swapCount = 0;
    countingArray = new int[1000000]; // initialize with a million buckets, because that is our high bound
}

void Counting::sort() {

    /* Resets for safety */
    comparisonCount = 0;
    swapCount = 0;
    for (int i = 0; i < 1000000; i++) {
        countingArray[i] = 0; // clearing count array in case already used.
    }

    clock_t start = clock(); // start timer

    /* place elements in counting array based on value as index */
    for (int j = 0; j < count; j++) {
        countingArray[data[j]]++; // increment the value at the index of the value of the data at j
        // cout << data[j] << ": " << countingArray[data[j]] << endl;
    }

    /* replace elements in data array in the order of counting array */
    int countingArrayIndex = 0;
    for (int k = 0; k < 1000000; k++) { // 1000000 is the upperbound
        while (countingArray[k] > 0) { // while there is more than 0 elements at the index
            countingArray[k]--; // decrement the count stored there
            data[countingArrayIndex] = k;
            swapCount++; // "If you are just overwriting data without need to store it some where else then it isn't a swap, [otherwise swapCount++]".

            countingArrayIndex++; //increment index
        }
    }

    clock_t finish = clock(); // end timer
    elapsedTime = double(finish - start); // set elapsed CPU time
}

ostream& operator<<(ostream& out, const Counting& Counting) {
    /* print contents of array (debug only) */
    // for (int i = 0; i < Counting.count; i++) {
    //     out << i << ": " << Counting.data[i] << endl;
    // }
    /* print time elapsed to sort */
    out << "Elapsed CPU time: " << Counting.elapsedTime << endl;
    out << "Swap Count: " << Counting.swapCount << endl;
    out << "Comparison Count: " << Counting.comparisonCount << endl;
    return out;
}
