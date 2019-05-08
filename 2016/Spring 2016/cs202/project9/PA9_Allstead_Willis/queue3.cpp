// Queue - node based
#include <fstream>
#include "queueN.h"

Node::Node(int data, Node *next) {
    this->data = data;
    this->next = next;
}

Queue::Queue(int ignore) {
    front = rear = NULL;
}

Queue::Queue(const Queue &toCopy) {
    if (!toCopy.empty()) {
        front = toCopy.front;
        rear = toCopy.rear;
    } else {
        front = rear = NULL;
    }
}

Queue::~Queue() {
    clear();
}

Queue& Queue::operator=(const Queue &toCopy) {
    if (this != &toCopy) {
        front = toCopy.front;
        rear = toCopy.rear;
    }
    return *this;
}

bool Queue::enqueue(int data) {
    if (!full()) {
        Node *tmp = new Node(data, NULL);
        if (empty()) {
            front = rear = tmp;
        } else {
            rear->next = tmp;
            rear = tmp;
        }

        return true;
    } else { return false; }
}

bool Queue::dequeue(int &removed) {
    if (!empty()) {
        Node *tmp = front;
        removed = front->data;
        front = front->next;
        delete [] tmp;

        return true;
    } else { return false; }
}

bool Queue::empty() const {
    return front == NULL;
}

bool Queue::full() const {
    return false;
}

bool Queue::clear() {
    if (!empty()) {

        while(front) {
            Node *tmp = front;
            if (front->next) {
                front = front->next;
            } else {
                front = NULL;
            }
            delete [] tmp;
        }

        return true;
    } else { return false; }
}


ostream& operator<<(ostream &fin, const Queue &toPrint) {
    Node *tmp = toPrint.front;
    while(tmp) {

        if (tmp == toPrint.front) {
            fin << "[" << tmp->data << "] ";
        } else if (tmp == toPrint.rear) {
            fin << "|" << tmp->data << "|";
        } else {
            fin << tmp->data << " ";
        }

        if (tmp->next) {
            tmp = tmp->next;
        } else {
            break;
        }
    }

    return fin;
}
