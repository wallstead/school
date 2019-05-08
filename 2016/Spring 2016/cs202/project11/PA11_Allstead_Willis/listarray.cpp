#include "listarray.h"

ListArray::ListArray(int size) {
    this->data = new int[size];
    this->size = size;
    this->cursor = -1;
    this->actual = 0;
}

ListArray::ListArray(const ListArray &toCopy) {
    if (this != &toCopy) {
        this->data = new int[toCopy.size];
        this->size = toCopy.size;
        this->cursor = toCopy.cursor;
        this->actual = toCopy.actual;
        for (int i = 0; i < toCopy.actual; i++) {
            this->data[i] = toCopy.data[i];
        }
    } else {
        cout << "cannot copy self" << endl;
    }
}

ListArray::~ListArray() {
    delete [] this->data;
    this->size = 0;
    this->cursor = -1;
    this->actual = 0;
}

bool ListArray::insertBefore(const int &toInsert) {
    if (!isFull()) {
        if (isEmpty()) {
            cursor++;
            data[cursor] = toInsert;
            actual++;
        } else {
            //shift everything to the right of cursor right one
            for (int i = actual; i > cursor; i--) {
                data[i] = data[i-1];
            }
            //set value of this one
            data[cursor] = toInsert;
            actual++;
        }
        return true;
    } else {
        return false;
    }
}

bool ListArray::insertAfter(const int &toInsert) {
    if (!isFull()) {
        //shift everything to the right of cursor right one
        for (int i = actual; i > cursor; i--) {
            data[i] = data[i-1];
        }
        //move cursor
        cursor++;
        //set value of this one
        data[cursor] = toInsert;
        actual++;
        return true;
    } else {
        return false;
    }
}

bool ListArray::get(int &toReturn) const {
    if (!isEmpty()) {
        toReturn = data[cursor];
        return true;
    } else {
        return false;
    }
}

bool ListArray::remove(int &removed) {
    if (!isEmpty()) {
        removed = data[cursor];
        //move everything right of cursor to the left one
        for (int i = cursor; i < actual; i++) {
            data[i] = data[i+1];
        }
        actual--;
        // if cursor is now out of bounds move it left one
        if (cursor == actual) {
            cursor--;
        }
        return true;
    } else {
        return false;
    }
}

bool ListArray::goToBeginning() {
    if (!isEmpty()) {
        cursor = 0;
        return true;
    } else {
        return false;
    }
}

bool ListArray::goToEnd() {
    if (!isEmpty()) {
        cursor = actual-1;
        return true;
    } else {
        return false;
    }
}

bool ListArray::goToNext() {
    if (!isEmpty()) {
        if (cursor < actual-1) {
            cursor++;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ListArray::goToPrior() {
    if (!isEmpty()) {
        if (cursor > 0) {
            cursor--;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ListArray::isEmpty() const {
    return (actual == 0);
}

bool ListArray::isFull() const {
    return (actual == size);
}

ListArray& ListArray::operator=(const ListArray &toCopy) {
        delete [] this->data;
        this->data = new int[toCopy.size];
        this->size = toCopy.size;
        this->cursor = toCopy.cursor;
        this->actual = toCopy.actual;
        for (int i = 0; i < toCopy.actual; i++) {
            this->data[i] = toCopy.data[i];
        }

    return *this;
}

ostream& operator << (ostream &fin, const ListArray &toPrint) {
    for (int i = 0; i < toPrint.actual; i++) {
        if (i == (toPrint.cursor)) {
            fin << "[" << toPrint.data[i] << "] ";
        } else {
            fin << "|" << toPrint.data[i] << "| ";
        }
    }
    return fin;
}
