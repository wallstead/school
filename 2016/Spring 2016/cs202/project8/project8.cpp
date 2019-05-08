#include <iostream>
// #include "stack.h"
#include "stackN.h"

using namespace std;

int main() {

    char a = 'a';
    char b = 'b';
    char c = 'c';
    char z = 'z';

    Stack test;

    // cout << test << endl;

    test.push(a);

    cout << test << endl;

    test.push(b);

    cout << test << endl;

    test.push(c);

    cout << test << endl;

    test.push(a);

    cout << test << endl;

    char popped;

    if (test.pop(popped)) {
        cout << "popped out: " << popped << endl;
    }

    cout << test << endl;

    test.clear();

    cout << test << endl;

    test.push(a);

    cout << test << endl;

    test.push(b);

    cout << test << endl;

    test.push(b);

    cout << test << endl;

    test.push(c);

    cout << test << endl;

    Stack test3 = test;

    cout << test3 << endl;

    test3.push(z);

    cout << test3 << endl;




    return 0;
}
