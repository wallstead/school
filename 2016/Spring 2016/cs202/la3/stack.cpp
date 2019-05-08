#include <iostream>
#include <string>

using namespace std;

template <class T>
class Stack {
        public:
                Stack(int = 10);
                Stack(const Stack&);
                ~Stack();
                Stack& operator=(const Stack&);
                bool push(T);
                bool pop(T&);
                bool empty() const;
                bool full() const;
                bool clear();
        		bool operator==(const Stack&) const;
                friend ostream& operator<<(ostream&, const Stack&);
        private:
                int max;
                int top;
                int actual; //only used in stack (stay) implementation
                T* data;
};

template <class T>
Stack<T>::Stack(int size) {
    max = size;
    top = -1;
    data = new T[size];
}

template <class T>
Stack<T>::Stack(const Stack &toCopy) {
    max = toCopy.max;
    top = toCopy.top;
    data = new T[toCopy.max];
    for (int i = 0; i < toCopy.max; i++) {
        data[i] = toCopy.data[i];
    }
}

template <class T>
Stack<T>::~Stack() {
    max = 0;
    top = -1;
    delete [] data;
    data = NULL;
}

template <class T>
bool Stack<T>::push(T data) {
    if (full() == false) {
        this->data[++top] = data;
        return true;
    } else { // too full
        return false;
    }
}

template <class T>
bool Stack<T>::pop(T &topData) {
    if (empty() == false) {
        topData = data[top];
        top--;
        return true;
    } else { // nothing to pop
        return false;
    }
}

template <class T>
bool Stack<T>::empty() const {
    return top < 0;
}

template <class T>
bool Stack<T>::full() const {
    return top == max-1;
}

template <class T>
bool Stack<T>::clear() {
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

template <class T>
bool Stack<T>::operator==(const Stack &toCompare) const {
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

template <class T>
ostream& operator<<(ostream &fout, const Stack< T >&stackToPrint) {
    fout << "[ ";
    for (int i = 0; i <= stackToPrint.top; i++) {
        fout << stackToPrint.data[i] << " ";
    }

    fout << "]";
    return fout;
}
