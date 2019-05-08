#include <iostream>
#include "listnode.h"

using namespace std;

int main() {
    ListNode list;
    int removed;
    cout << list << endl;
    list.insertAfter(1);
    cout << list << endl;
    list.insertBefore(2);
    cout << list << endl;
    list.insertAfter(3);
    cout << list << endl;
    list.clear();
    cout << list << endl;
    list.insertAfter(3);
    cout << list << endl;
    list.insertBefore(2);
    cout << list << endl;











    // list.insertBefore(1);
    // cout << list << endl;
    // list.insertBefore(2);
    // cout << list << endl;
    // list.insertAfter(3);
    // cout << list << endl;
    // list.insertAfter(4);
    // cout << list << endl;
    // list.insertBefore(5);
    // cout << list << endl;
    // list.goToNext();
    // cout << list << endl;
    // list.goToNext();
    // cout << list << endl;
    // list.goToNext();
    //
    // ListArray<int> list2 = ListArray<int>(5);
    // cout << list2 << endl;
    // list2 = list;
    // cout << list2 << endl;
    // list2.goToNext();
    // cout << list2 << endl;
    // list2.goToBeginning();
    // cout << list2 << endl;
    // list2.remove(removed);
    // cout << list2 << endl;
    //
    // ListArray<int> list3 = list2;
    // cout << list3 << endl;

    return 0;
}
