#ifndef _QUEUE_
#define _QUEUE_

#include <iostream>
using namespace std;

template <class T>
class Queue {
    class Node {
    public:
        T element;

        Node* next;

        Node(T e = 0): element(e), next(NULL){}
    };

    Node* first;
    Node* last;

public:
    int size;

    Queue()
        : first(NULL)
        , last(NULL)
    {
        size = 0;
    }

    inline bool empty() const { return first == NULL; }

    void push(const T x);
    void pop();
    T& front();
};

template <class T>
void Queue<T>::push(const T x)
{
    if (empty()) {
        first = new Node(x);
        last = first;
    }

    else {
        Node* p = new Node(x);

        last->next = p;
        last = last->next;
    }
    size++;
}

template <class T>
void Queue<T>::pop()
{
    if (!empty()) {
        Node* p = first;
        first = first->next;

        delete p;
        size--;
    }
}

template <class T>
T& Queue<T>::front()
{
    return first->element;
}

#endif
