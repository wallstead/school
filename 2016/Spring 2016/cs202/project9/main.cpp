#include <iostream>
#include "queueN.h"

using namespace std;

int main() {
    Queue test;
    int removed;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    if (test.dequeue(removed)) {
        cout << "removed: " << removed << endl;
    } else {
        cout << "failed to remove" << endl;
    }
    cout << test << endl;

    if (test.dequeue(removed)) {
        cout << "removed: " << removed << endl;
    } else {
        cout << "failed to remove" << endl;
    }
    cout << test << endl;


    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    if (test.dequeue(removed)) {
        cout << "removed: " << removed << endl;
    } else {
        cout << "failed to remove" << endl;
    }
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    test.enqueue(1);
    cout << test << endl;

    test.enqueue(2);
    cout << test << endl;

    test.enqueue(3);
    cout << test << endl;

    // if (test.dequeue(removed)) {
    //     cout << "removed: " << removed << endl;
    // } else {
    //     cout << "failed to remove" << endl;
    // }
    // cout << test << endl;
    //
    // if (test.dequeue(removed)) {
    //     cout << "removed: " << removed << endl;
    // } else {
    //     cout << "failed to remove" << endl;
    // }
    // cout << test << endl;
    //

    //
    // test.enqueue(1);
    // cout << test << endl;
    //
    // test.enqueue(2);
    // cout << test << endl;
    //
    // test.clear();
    //
    //
    // if (test.empty()) {
    //     cout << "empty " << endl;
    // }
    return 0;
}
