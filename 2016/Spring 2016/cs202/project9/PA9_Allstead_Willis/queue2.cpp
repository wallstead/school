// Queue - wrap
#include <fstream>
#include "queue.h"

Queue::Queue(int size) {
    max = size;
    data = new int[size];
    front = -1;
    rear = -1;
}

Queue::Queue(const Queue &toCopy) {
    this->max = toCopy.max;
    this->data = new int[toCopy.max];
    this->front = toCopy.front;
    this->rear = toCopy.rear;

    for (int i = 0; i < toCopy.max; i++) {
        this->data[i] = toCopy.data[i];
    }
}

Queue::~Queue() {
    max = 0;
    delete [] data;
    front = -1;
    rear = -1;
}

Queue& Queue::operator=(const Queue &toCopy) {
    if (&toCopy != this) {
        this->max = toCopy.max;
        this->data = new int[toCopy.max];
        this->front = toCopy.front;
        this->rear = toCopy.rear;

        for (int i = 0; i < toCopy.max; i++) {
            this->data[i] = toCopy.data[i];
        }
    } else {
        cout << "Same pointer." << endl;
    }

    return *this;
}

bool Queue::enqueue(int toAdd) {
    if (!full()) {
        if (front < 0) {
            front = 0;
        }
        int placeToAdd = ++rear % max;
        data[placeToAdd] = toAdd;
        return true;
    } else {
        return false;
    }
}

bool Queue::dequeue(int &removed) {
    if (!empty()) {
        removed = data[front % max];
        if (rear==front) {
            clear();
        } else {
            ++front;
        }

        return true;
    } else {
        return false;
    }
}

bool Queue::empty() const {
    return front < 0 && rear << 0;
}

bool Queue::full() const {
    return (rear+1 - max) == front;
}

bool Queue::clear() {
    if (!empty()) {
        front = rear = -1;
        return true;
    } else {
        return false;
    }
}

bool Queue::operator==(const Queue &toCompare) const {
    if (this->max == toCompare.max) {
        for (int i = toCompare.front; i <= toCompare.rear; i++) { // count of items
            int positionToCompare = i % toCompare.max;
            if (this->data[positionToCompare] != toCompare.data[positionToCompare]) {
                return false;
            }
        }
        return true;
    } else { return false; }
}

ostream& operator<<(ostream &fin, const Queue &toPrint) {
    if (!toPrint.empty()) {
        for (int i = toPrint.front; i <= toPrint.rear; i++) { // count of items
            int positionToRead = i % toPrint.max;

            // cout << "front: " << toPrint.front << " rear: " << toPrint.rear << endl;
            if (positionToRead == (toPrint.front % toPrint.max)) {
                fin << "[" << toPrint.data[positionToRead] << "] ";
            } else if (positionToRead == (toPrint.rear % toPrint.max)) {
                fin << "|" << toPrint.data[positionToRead] << "|";
            } else {
                fin << toPrint.data[positionToRead] << " ";
            }
        }
    }
    return fin;
}
