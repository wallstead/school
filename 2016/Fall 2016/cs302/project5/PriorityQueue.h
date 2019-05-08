//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 14-6.

/** ADT priority queue: ADT sorted list implementation.
 @file PriorityQueue.h */

#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_

#include "SortedList.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class PriorityQueue {
private:
    SortedList<ItemType> sList; // sorted list of items

public:

    PriorityQueue();
    PriorityQueue(const PriorityQueue& pq);
    ~PriorityQueue();

    // Checks if empty.
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();

    /** @throw  PrecondViolatedExcept if priority queue is empty. */
    ItemType peek() const throw(PrecondViolatedExcept);
}; // end PriorityQueue
#include "PriorityQueue.cpp"
#endif
