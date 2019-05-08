#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* NOTE: all header definitions and implementation in one file to make the templates work */

template <class T>
class Queue {
 public:
  Queue(int = 20000); // large queue by default just incase
  Queue(const Queue&);
  ~Queue();
  bool enqueue(T);
  bool dequeue(T&);
  bool empty() const;
  bool full() const;
  bool clear();
  T getFront() const;

 private:
  int max;
  int front;
  int rear;
  T* data;
};

// Parameterized constructor
template <class T>
Queue<T>::Queue(int size) {
  max = size;
  data = new T[size];
  front = -1;
  rear = -1;
}

// Copy constructor
template <class T>
Queue<T>::Queue(const Queue &toCopy) {
  this->max = toCopy.max;
  this->data = new T[toCopy.max];
  this->front = toCopy.front;
  this->rear = toCopy.rear;

  for (int i = 0; i <= toCopy.rear; i++) {
    this->data[i] = toCopy.data[i];
  }
}

// Destructor
template <class T>
Queue<T>::~Queue() {
  max = 0;
  delete[] data;
  front = -1;
  rear = -1;
}

// To add an object to the queue
template <class T>
bool Queue<T>::enqueue(T toAdd) {
  if (!full()) {
    front = 0;
    data[++rear] = toAdd;
    return true;
  } else {
    return false;
  }
}

// To remove an object to the queue
template <class T>
bool Queue<T>::dequeue(T &removed) {
  if (!empty()) {
    removed = data[front];
    for (int i = front; i < rear; i++) {
      data[i] = data[i + 1];
    }
    rear--;

    return true;
  } else {
    return false;
  }
}

// To check if the queue is empty
template <class T>
bool Queue<T>::empty() const { return rear < 0; }

// To check if the queue is full
template <class T>
bool Queue<T>::full() const { return rear == max - 1; }

// To clear the queue
template <class T>
bool Queue<T>::clear() {
  if (!empty()) {
    front = rear = -1;
    return true;
  } else {
    return false;
  }
}

// To retrieve the object at the front of the queue
template <class T>
T Queue<T>::getFront() const {
  return data[front];
}
