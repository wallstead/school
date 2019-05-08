/**
 * @file Merge.cpp
 *
 * @brief Implementation file for the Merge sorting class
 *
 * @author Willis Allstead
 *
 * @details Specifies the functions of the Merge sorting class
 *
 * @version 1.0
 *
 */

#include "Merge.h"

Merge::Merge(int toSort[], long count) {
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

void Merge::merge(long first, long mid, long last) {
    int tempArray[count]; // Temporary array
                                // Initialize the local indices to indicate the subarrays
    long first1 = first;           // Beginning of first subarray
    long last1 = mid;              // End of first subarray
    long first2 = mid + 1;         // Beginning of second subarray
    long last2 = last;             // End of second subarray

    // While both subarrays are not empty, copy the
    // smaller item into the temporary array
    long index = first1;           // Next available location in tempArray
    while ((first1 <= last1) && (first2 <= last2)) {
        // At this point, tempArray[first..index–1] is in order
        if (data[first1] <= data[first2]) {
            tempArray[index] = data[first1];
            first1++;
        } else {
            tempArray[index] = data[first2];
            first2++;
        }  // end if

        comparisonCount++; // for comparisons in if-statement
        comparisonCount++; // for comparisons in while-loop
        index++;
    }  // end while

    // Finish off the first subarray, if necessary
    while (first1 <= last1) {
        // At this point, tempArray[first..index–1] is in order
        tempArray[index] = data[first1];
        first1++;
        index++;
        comparisonCount++; // for comparisons in while-loop
    }

    // Finish off the second subarray, if necessary
    while (first2 <= last2) {
        // At this point, tempArray[first..index–1] is in order
        tempArray[index] = data[first2];
        first2++;
        index++;
        comparisonCount++; // for comparisons in while-loop
    }

    // Copy the result back into the original array
    for (index = first; index <= last; index++) {
        data[index] = tempArray[index];
        swapCount++; // swapped
        comparisonCount++; // for comparisons in for-loop (as stated by Shehryar Khattak)
    }

}  // end merge

void Merge::sort(long first, long last) {

    clock_t start = clock(); // start timer

    if (first < last) {
        // Sort each half
        long mid = first + (last - first) / 2; // Index of midpoint

        // Sort left half theArray[first..mid]
        sort(first, mid);

        // Sort right half theArray[mid+1..last]
        sort(mid + 1, last);

        // Merge the two halves
        merge(first, mid, last);


    }  // end if

    clock_t finish = clock(); // end timer
    elapsedTime = double(finish - start); // set elapsed CPU time
}

ostream& operator<<(ostream& out, const Merge& merge) {
    /* print contents of array (debug only) */
    // for (int i = 0; i < merge.count; i++) {
    //     out << i << ": " << merge.data[i] << endl;
    // }
    /* print time elapsed to sort */
    out << "Elapsed CPU time: " << merge.elapsedTime << endl;
    out << "Swap Count: " << merge.swapCount << endl;
    out << "Comparison Count: " << merge.comparisonCount << endl;
    return out;
}
