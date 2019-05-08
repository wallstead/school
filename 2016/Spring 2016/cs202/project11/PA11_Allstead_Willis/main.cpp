#include <iostream>
#include <string>
#include "listarray.h"
#include "listnode.h"

using namespace std;

bool sort(ListNode&);
int binarySearch(ListArray, int, int, int);
int fib(int);

int main() {
    ListNode nodelist;
    int removed;

    /* Insert from data file into node list  */
    string fileName;
    cout << "Enter file name for binary search: ";
    cin >> fileName;

    if (nodelist.readFile(fileName)) {
        cout << "Did read file." << endl;
    } else {
        cout << "Failed to read file." << endl;
    }
    cout << "Node list: " << nodelist << endl;

    /* Sort node list */
    sort(nodelist);
    cout << "Sorted node list: " << nodelist << endl;

    /* Copy from node list to array list */
    int arrayCount = nodelist.count();
    ListArray arraylist = ListArray(arrayCount);
    while(!nodelist.isEmpty()) {
        int data;
        nodelist.get(data);
        arraylist.insertAfter(data);
        nodelist.remove(removed);
    }
    cout << "Array list: " << arraylist << endl;

    /* Prompt for search number */
    int searchNum;
    cout << "Enter search number: ";
    cin >> searchNum;

    /* Perform binary search */
    cout << "Index of search number: ";
    cout << binarySearch(arraylist, searchNum, 0, arrayCount-1) << endl;

    /* Prompt for fib index */
    int fibPosition;
    cout << "Enter Fibonacci position: ";
    cin >> fibPosition;

    /* Perform search for fib value */
    cout << "Value at position " << fibPosition << " => " << fib(fibPosition) << endl;


    return 0;
}

bool sort(ListNode &nodelist) {
    int removed;
    if (!nodelist.isEmpty()) {
        bool unsorted = true;
        while(unsorted) {
            unsorted = false;
            nodelist.goToBeginning();

            while(nodelist.goToNext()) { // will be false when it is at the end
                int currentBegin;
                nodelist.get(currentBegin);

                int after;
                nodelist.get(after);
                nodelist.goToPrior();
                int before;
                nodelist.get(before);
                if (before > after) { // if it needs a swap
                    nodelist.remove(removed);
                    nodelist.insertAfter(after);
                    nodelist.goToNext();
                    int current;
                    nodelist.get(current);
                    nodelist.remove(removed);
                    nodelist.insertAfter(before);
                    unsorted = true;
                } else {
                    nodelist.goToNext();
                }

            }
        }
        nodelist.goToBeginning();
        nodelist.remove(removed);
        return true;
    } else {
        return false;
    }
}

int binarySearch(ListArray list, int searchVal, int start, int end) {
    // find value of middle
    int mid = (start+end)/2;
    // compare to searchVal
    list.goToBeginning();
    for (int i = 0; i < mid; i++) {
        list.goToNext();
    }
    int valAtMid;
    list.get(valAtMid);
    if (searchVal > valAtMid) { // search top half
        return binarySearch(list, searchVal,mid+1, end);
    } else if (searchVal < valAtMid) { // search bottom half
        return binarySearch(list, searchVal,start, mid-1);
    } else { // mid is the value
        return mid;
    }
}

int fib(int x) {
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else {
        return fib(x-1)+fib(x-2); // as nancy said
    }
}
