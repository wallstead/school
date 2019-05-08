// array - stay - done

#include "stack.h"
#include <iostream> // remove after testing

Stack::Stack(int size) {
    max = size;
    top = -1;
    actual = 0;
    data = new char[size];
}

Stack::Stack(const Stack &toCopy) {
    max = toCopy.max;
    top = toCopy.top;
    actual = toCopy.actual;
    data = new char[toCopy.max];
    for (int i = 0; i < toCopy.max; i++) {
        data[i] = toCopy.data[i];
    }
}

Stack::~Stack() {
    max = 0;
    top = -1;
    actual = 0;
    delete [] data;
    data = NULL;
}

bool Stack::push(char letter) {

    if (full() == false) {
        top = 0;
        actual++;

        // move every other object right one
        for (int i = actual-1; i > 0; i--) {
            data[i] = data[i-1];
        }
        data[top] = letter;

        return true;
    } else {
        return false;
    }


}

bool Stack::pop(char &topLetter) {
    if (empty() == false) {
        // move every object left one
        topLetter = data[top];
        for (int i = top; i < actual-1; i++) {
            data[i] = data[i+1];
        }
        if (--actual == 0) {
            top = -1;
        }

        return true;
    } else { // nothing to pop
        return false;
    }
}

bool Stack::empty() const {
    return top < 0;
}

bool Stack::full() const {
    return actual == max;
}

bool Stack::clear() {
    if (empty() == false) {
        for (int i = 0; i < max; i++) {
            data[i] = '\0';
        }
        actual = 0;
        top = -1;
        return true;
    } else { // nothing to clear
        return false;
    }
}

ostream& operator<<(ostream &fout, const Stack &stackToPrint) {
    fout << "[ ";
    for (int i = stackToPrint.top; i < stackToPrint.actual; i++) {
        fout << stackToPrint.data[i] << " ";
    }
    fout << "]";
    return fout;
}

bool Stack::operator==(const Stack &toCompare) const {
    if (toCompare.actual == actual) {
        for (int i = 0; i < toCompare.actual; i++) {
            if (data[i] != toCompare.data[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
