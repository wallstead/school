#include <iostream>
using namespace std;

template <typename T>
class ListArray {
public:
    ListArray(int=10);
    ListArray(const ListArray<T>&);
    ~ListArray();

    bool insertBefore(const T&);
    bool insertAfter(const T&);
    bool get(T&) const;
    bool remove(T&);

    void clear();

    bool goToBeginning();
    bool goToEnd();

    bool goToNext();
    bool goToPrior();

    bool isEmpty() const;
    bool isFull() const;

    ListArray<T>& operator = (const ListArray<T>&);

    template <typename S>
    friend ostream& operator << (ostream&, const ListArray<S>&);

private:
    T *data;
    int cursor;
    int actual;
    int size;
};

template <typename T>
ListArray<T>::ListArray(int size) {
    this->data = new T[size];
    this->size = size;
    this->cursor = -1;
    this->actual = 0;
}

template <typename T>
ListArray<T>::ListArray(const ListArray<T> &toCopy) {
    if (this != &toCopy) {
        this->data = new T[toCopy.size];
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

template <typename T>
ListArray<T>::~ListArray() {
    delete [] this->data;
    this->size = 0;
    this->cursor = -1;
    this->actual = 0;
}

template <typename T>
bool ListArray<T>::insertBefore(const T &toInsert) {
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

template <typename T>
bool ListArray<T>::insertAfter(const T &toInsert) {
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

template <typename T>
bool ListArray<T>::get(T &toReturn) const {
    if (!isEmpty()) {
        toReturn = data[cursor];
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool ListArray<T>::remove(T &removed) {
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

template <typename T>
bool ListArray<T>::goToBeginning() {
    if (!isEmpty()) {
        cursor = 0;
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool ListArray<T>::goToEnd() {
    if (!isEmpty()) {
        cursor = actual-1;
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool ListArray<T>::goToNext() {
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

template <typename T>
bool ListArray<T>::goToPrior() {
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

template <typename T>
bool ListArray<T>::isEmpty() const {
    return (actual == 0);
}

template <typename T>
bool ListArray<T>::isFull() const {
    return (actual == size);
}

template <typename T>
ListArray<T>& ListArray<T>::operator=(const ListArray<T> &toCopy) {
        delete [] this->data;
        this->data = new T[toCopy.size];
        this->size = toCopy.size;
        this->cursor = toCopy.cursor;
        this->actual = toCopy.actual;
        for (int i = 0; i < toCopy.actual; i++) {
            this->data[i] = toCopy.data[i];
        }

    return *this;
}

template <typename S>
ostream& operator << (ostream &fin, const ListArray<S> &toPrint) {
    for (int i = 0; i < toPrint.actual; i++) {
        if (i == (toPrint.cursor)) {
            fin << "[" << toPrint.data[i] << "] ";
        } else {
            fin << "|" << toPrint.data[i] << "| ";
        }
    }
    return fin;
}
