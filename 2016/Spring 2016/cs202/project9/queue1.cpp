// Queue - stay
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

    for (int i = 0; i <= toCopy.rear; i++) {
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
    if (&toCopy == this) {
        this->max = toCopy.max;
        this->data = new int[toCopy.max];
        this->front = toCopy.front;
        this->rear = toCopy.rear;

        for (int i = 0; i <= toCopy.rear; i++) {
            this->data[i] = toCopy.data[i];
        }
    } else {
        cout << "Same pointer." << endl;
    }

    return *this;
}

bool Queue::enqueue(int toAdd) {
    if (!full()) {
        front = 0;
        data[++rear] = toAdd;
        return true;
    } else {
        return false;
    }
}

bool Queue::dequeue(int &removed) {
    if (!empty()) {
        removed = data[front];
        for (int i = front; i < rear; i++) {
            data[i] = data[i+1];
        }
        rear--;

        return true;
    } else {
        return false;
    }
}

bool Queue::empty() const {
    return rear < 0;
}

bool Queue::full() const {
    return rear == max-1;
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
    if (this->rear == toCompare.rear) {
        for (int i = toCompare.front; i < toCompare.rear; i++) {
            if (this->data[i] != toCompare.data[i]) {
                return false;
            }
        }
        return true;
    } else { return false; }
}

ostream& operator<<(ostream &fin, const Queue &toPrint) {
    if (!toPrint.empty()) {
        for (int i = toPrint.front; i <= toPrint.rear; i++) {
            if (i == toPrint.front) {
                fin << "[" << toPrint.data[i] << "] ";
            } else if (i == toPrint.rear) {
                fin << "|" << toPrint.data[i] << "|";
            } else {
                fin << toPrint.data[i] << " ";
            }
        }
    }
    return fin;
}
