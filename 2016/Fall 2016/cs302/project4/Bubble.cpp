/**
 * @file Bubble.cpp
 *
 * @brief Implementation file for the Bubble sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the functions of the Bubble sorting class
 *
 * @version 1.0
 *
 */

#include "Bubble.h"

Bubble::Bubble(int toSort[], int count) {
    this->count = count; // set count
    data = new int[count]; // create array of size count
    for (int i = 0; i < count; i++) {
        data[i] = toSort[i]; // copy elements of int array
        // cout << i << ": " << data[i] << "->" << toSort[i] << endl;
    }
    elapsedTime = 0;
    comparisonCount = 0;
    swapCount = 0;
}

void Bubble::sort() { // using a lot of code from the book.
    /* Reset comparison and swap count in case */
    comparisonCount = 0;
    swapCount = 0;

    clock_t start = clock(); // start timer

    bool sorted = false; // False when swaps occur
    int pass = 1;
    while (!sorted && (pass < count)) {
        // At this point, data[count+1-pass..count−1] is sorted
        // and all of its entries are > the entries in data[0..count–pass]
        sorted = true; // Assume sorted
        for (int index = 0; index < count - pass; index++){
            // At this point, all entries in data[0..index–1]
            // are <= data[index]
            int nextIndex = index + 1;
            if (data[index] > data[nextIndex]){
                // Exchange entries

                int temp; // for swapping
                temp = data[index];
                data[index] = data[nextIndex];
                data[nextIndex] = temp;
                swapCount++; // increment swap count


                sorted = false; // Set flag
            } // end if

            comparisonCount++; // increment comparison count for the if-statement
        } // end for

        pass++;
    } // end while

    clock_t finish = clock(); // end timer
    elapsedTime = double(finish - start); // set elapsed CPU time
}

ostream& operator<<(ostream& out, const Bubble& bubble) {
    /* print contents of array (debug only) */
    // for (int i = 0; i < bubble.count; i++) {
    //     out << i << ": " << bubble.data[i] << endl;
    // }
    /* print time elapsed to sort */
    out << "Elapsed CPU time: " << bubble.elapsedTime << endl;
    out << "Swap Count: " << bubble.swapCount << endl;
    out << "Comparison Count: " << bubble.comparisonCount << endl;
    return out;
}
