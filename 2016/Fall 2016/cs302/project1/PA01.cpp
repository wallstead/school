/**
 * @file PA01.cpp
 *
 * @brief Main driver for this project
 *
 * @author Willis T. Allstead
 *
 * @details Runs some basic tests on the project as a whole
 *
 * @version 0.10
 *
 */
#include <iostream>
#include "LinkedList.h"
#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"

using namespace std;

int main() {
    LinkedList<int> foo;
    cout << foo.getLength() << endl;
    cout << foo.isEmpty() << endl;
    cout << foo.insert(1,1) << endl;
    cout << foo.getLength() << endl;
    cout << foo.isEmpty() << endl;
    cout << foo.remove(1) << endl;
    cout << foo.isEmpty() << endl;
    cout << foo.insert(1,1) << endl;
    cout << foo.insert(2,2) << endl;
    cout << foo.insert(3,3) << endl;
    cout << foo.getEntry(2) << endl;
    // cout << foo.getEntry(4) << endl; would throw
    cout << foo.getEntry(3) << endl;
    // cout << foo.replace(3, 89) << endl;

    return 0;
}
