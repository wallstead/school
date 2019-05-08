// array - move - done

#include "stack.h"

Stack::Stack(int size) {
    max = size;
    top = -1;
    data = new char[size];
}

Stack::Stack(const Stack &toCopy) {
    max = toCopy.max;
    top = toCopy.top;
    data = new char[toCopy.max];
    for (int i = 0; i < toCopy.max; i++) {
        data[i] = toCopy.data[i];
    }
}

Stack::~Stack() {
    max = 0;
    top = -1;
    delete [] data;
    data = NULL;
}

bool Stack::push(char letter) {
    if (full() == false) {
        data[++top] = letter;
        return true;
    } else { // too full
        return false;
    }
}

bool Stack::pop(char &topLetter) {
    if (empty() == false) {
        topLetter = data[top];
        top--;
        return true;
    } else { // nothing to pop
        return false;
    }
}

bool Stack::empty() const {
    return top < 0;
}

bool Stack::full() const {
    return top == max-1;
}

bool Stack::clear() {
    if (empty() == false) {
        for (int i = 0; i < max; i++) {
            data[i] = '\0';
        }
        top = -1;
        return true;
    } else { // nothing to clear
        return false;
    }
}

bool Stack::operator==(const Stack &toCompare) const {
    if (toCompare.top == top) {
        for (int i = 0; i < toCompare.top; i++) {
            if (data[i] != toCompare.data[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream &fout, const Stack &stackToPrint) {
    fout << "[ ";
    for (int i = 0; i <= stackToPrint.top; i++) {
        fout << stackToPrint.data[i] << " ";
    }

    fout << "]";
    return fout;
}
