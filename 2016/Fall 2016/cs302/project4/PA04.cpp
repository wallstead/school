/**
 * @file PA04.cpp
 *
 * @brief Main driver for project 4
 *
 * @author Willis Allstead
 *
 * @details Runs tests with different sorting algorithms
 *
 * @version 1.0
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Bubble.h"
#include "Merge.h"
#include "Counting.h"

using namespace std;

void populateFile(int count, std::string const& file);

int main() {


    /* Prep rand-num generator */
    srand( time( NULL ) );

    // Populate the files
    for (int i = 0; i < 4; i++) {
        if (i == 0) {
            std::string thousandFileGen("rand_1,000");
            populateFile(1000, thousandFileGen);
        } else if (i == 1) {
            std::string tenThousandFileGen("rand_10,000");
            populateFile(10000, tenThousandFileGen);
        } else if (i == 2) {
            std::string hundredThousandFileGen("rand_100,000");
            populateFile(100000, hundredThousandFileGen);
        } else {
            std::string millionFileGen("rand_1,000,000");
            populateFile(1000000, millionFileGen);
        }
    }

    // O(n^2) -> Bubble
    // O(nlog(n)) -> Merge
    // O(n) -> Counting

    /* get the 1,000 random numbers */
    int randThousand[1000];
    ifstream thousandFile("rand_1,000");
    if (thousandFile.is_open()) {
        int number; // holds number on each line
        int counter = 0; // increment throught randThousand array
        while(thousandFile >> number) {
            // cout << counter << ": " << number << endl;
            randThousand[counter] = number; // add it to array
            counter++;
        }
        thousandFile.close();
    } else {
        cout << "Cannot open thousand integer file";
    }

    /* get the 10,000 random numbers */
    int randTenThousand[10000];
    ifstream tenThousandFile("rand_10,000");
    if (tenThousandFile.is_open()) {
        int number; // holds number on each line
        int counter = 0; // increment throught randTenThousand array
        while(tenThousandFile >> number) {
            // cout << counter << ": " << number << endl;
            randTenThousand[counter] = number; // add it to array
            counter++;
        }
        tenThousandFile.close();
    } else {
        cout << "Cannot open ten thousand integer file";
    }

    /* get the 100,000 random numbers */
    int randHundredThousand[100000];
    ifstream hundredThousandFile("rand_100,000");
    if (hundredThousandFile.is_open()) {
        int number; // holds number on each line
        int counter = 0; // increment throught randHundredThousand array
        while(hundredThousandFile >> number) {
            // cout << counter << ": " << number << endl;
            randHundredThousand[counter] = number; // add it to array
            counter++;
        }
        hundredThousandFile.close();
    } else {
        cout << "Cannot open hundred thousand integer file";
    }

    /* get the 1,000,000 random numbers */
    int *randMillion = new int[1000000]; // to avoid stack overflow
    ifstream millionFile("rand_1,000,000");
    if (millionFile.is_open()) {
        int number; // holds number on each line
        int counter = 0; // increment throught randMillion array
        while(millionFile >> number) {
            randMillion[counter] = number; // add it to array
            counter++;
        }
        millionFile.close();
    } else {
        cout << "Cannot open million integer file";
    }


    /*
        Just have a table listing timing of each algorithm for each run of
        random and sorted inputs. At the bottom of the table average of the
        10 runs. Do this for every algorithm.
    */

    /* Bubble Sort */
    cout << "---BUBBLE SORT (1,000 unsorted)---" << endl;

    unsigned long totalCPUTime = 0;
    unsigned long totalComparisonCount = 0;
    unsigned long totalSwapCount = 0;
    int sortedThousand[1000];

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(randThousand, 1000); // sort random array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 1000; i++) {
                sortedThousand[i] = bubble.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (1,000 sorted)---" << endl;

    /* Reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(sortedThousand, 1000); // sort sorted array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (10,000 unsorted)---" << endl;

    /* Reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;
    int sortedTenThousand[10000];

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(randTenThousand, 10000); // sort random array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 10000; i++) {
                sortedTenThousand[i] = bubble.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (10,000 sorted)---" << endl;

    /* Reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(sortedTenThousand, 10000); // sort sorted array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (100,000 unsorted)---" << endl;

    /* Reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;
    int sortedHundredThousand[100000];

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(randHundredThousand, 100000); // sort random array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 100000; i++) {
                sortedHundredThousand[i] = bubble.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (100,000 sorted)---" << endl;

    /* Reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Bubble bubble = Bubble(sortedHundredThousand, 100000); // sort sorted array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (1,000,000 unsorted)---" << endl;

    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;
    int *sortedMillion = new int[1000000];

    /* only doing two as specified by project description */
    for (int i = 0; i < 2; i++) {
        Bubble bubble = Bubble(randMillion, 1000000); // sort sorted array using bubble sort
        bubble.sort();
        totalCPUTime += bubble.elapsedTime;
        totalComparisonCount += bubble.comparisonCount;
        totalSwapCount += bubble.swapCount;
        cout << "[" << i << "] --- CPU Time: " << bubble.elapsedTime  << "" << endl;
        if (i == 0) {
            for (int i = 0; i < 1000000; i++) {
                sortedMillion[i] = bubble.data[i]; // save the sorted list for use later
            }
        }
    }

    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---BUBBLE SORT (1,000,000 sorted)---" << endl;

    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    /* only doing one as specified by project description */
    Bubble bubbleMillSorted = Bubble(sortedMillion, 1000000); // sort sorted array using bubble sort
    bubbleMillSorted.sort();
    totalCPUTime += bubbleMillSorted.elapsedTime;
    totalComparisonCount += bubbleMillSorted.comparisonCount;
    totalSwapCount += bubbleMillSorted.swapCount;
    cout << "[" << 0 << "] --- CPU Time: " << bubbleMillSorted.elapsedTime  << "" << endl;

    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    /* Merge Sort */
    cout << "---MERGE SORT (1,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(randThousand, 1000); // sort random array using merge sort
        merge.sort(0, 1000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 1000; i++) {
                sortedThousand[i] = merge.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (1,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(sortedThousand, 1000); // sort sorted array using merge sort
        merge.sort(0, 1000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (10,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(randTenThousand, 10000); // sort random array using merge sort
        merge.sort(0, 10000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 10000; i++) {
                sortedTenThousand[i] = merge.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (10,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(sortedTenThousand, 10000); // sort sorted array using merge sort
        merge.sort(0, 10000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (100,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(randHundredThousand, 100000); // sort random array using merge sort
        merge.sort(0, 100000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 100000; i++) {
                sortedHundredThousand[i] = merge.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (100,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(sortedHundredThousand, 100000); // sort sorted array using merge sort
        merge.sort(0, 100000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (1,000,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(randMillion, 1000000); // sort random array using merge sort
        merge.sort(0, 1000000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 1000000; i++) {
                sortedMillion[i] = merge.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---MERGE SORT (1,000,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Merge merge = Merge(sortedMillion, 1000000); // sort sorted array using merge sort
        merge.sort(0, 1000000-1);
        totalCPUTime += merge.elapsedTime;
        totalComparisonCount += merge.comparisonCount;
        totalSwapCount += merge.swapCount;
        cout << "[" << i << "] --- CPU Time: " << merge.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    /* Counting Sort */
    cout << "---COUNTING SORT (1,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(randThousand, 1000); // sort random array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 1000; i++) {
                sortedThousand[i] = counting.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (1,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(sortedThousand, 1000); // sort sorted array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (10,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(randTenThousand, 10000); // sort random array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 10000; i++) {
                sortedTenThousand[i] = counting.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (10,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(sortedTenThousand, 10000); // sort sorted array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (100,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(randHundredThousand, 100000); // sort random array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 100000; i++) {
                sortedHundredThousand[i] = counting.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (100,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(sortedHundredThousand, 100000); // sort sorted array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (1,000,000 unsorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(randMillion, 1000000); // sort random array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
        if (i == 0) { // save one of the sorted lists for use later
            for (int i = 0; i < 1000000; i++) {
                sortedMillion[i] = counting.data[i];
            }
        }
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;

    cout << "---COUNTING SORT (1,000,000 sorted)---" << endl;

    /* reset these */
    totalCPUTime = 0;
    totalComparisonCount = 0;
    totalSwapCount = 0;

    for (int i = 0; i < 10; i++) {
        Counting counting = Counting(sortedMillion, 1000000); // sort sorted array using counting sort
        counting.sort();
        totalCPUTime += counting.elapsedTime;
        totalComparisonCount += counting.comparisonCount;
        totalSwapCount += counting.swapCount;
        cout << "[" << i << "] --- CPU Time: " << counting.elapsedTime  << "" << endl;
    }
    cout << "Average elapsed CPU time: " << long(totalCPUTime/10) << endl;
    cout << "Average comparison count: " << long(totalComparisonCount/10) << endl;
    cout << "      Average swap count: " << long(totalSwapCount/10) << endl;
    cout << "--------------------------------" << endl;


    return 0;
}

void populateFile(int count, std::string const& file) {
    std::ofstream myfile(file);
    if (!myfile) {
       return;
    }

    for(int index=0; index<count; index++) {
        int random_integer = (rand()%1000000)+1;
        myfile << random_integer << "\n";
    }
}
