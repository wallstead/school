//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 14-4.

/** ADT queue: Circular array-based implementation.
 @file ArrayQueue.h */

#ifndef ARRAY_QUEUE_
#define ARRAY_QUEUE_
#include "PrecondViolatedExcept.h"

template<class ItemType>
class ArrayQueue
{
private:
    static const int DEFAULT_CAPACITY = 10000;
    ItemType items[DEFAULT_CAPACITY]; // Array of queue items
    int      front;                   // Index to front of queue
    int      back;                    // Index to back of queue


public:
    int      count;                   // Number of items currently in the queue
    ArrayQueue();
    // Copy constructor and destructor supplied by compiler
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();

    ItemType peekFront() const;
}; // end ArrayQueue
#include "ArrayQueue.cpp"
#endif
