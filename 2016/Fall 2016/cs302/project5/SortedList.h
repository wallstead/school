//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 12-4.

/** ADT sorted list using ADT list.
 @file SortedList.h */
#ifndef SORTED_LIST_
#define SORTED_LIST_
#include <memory>
#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class SortedList : public LinkedList<ItemType>
{
public:
   SortedList();
   SortedList(const SortedList<ItemType>& sList);
   virtual ~SortedList();

   bool insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& anEntry) const;

   // The inherited methods remove, clear, getEntry, isEmpty, and
   // getLength have the same specifications as given in ListInterface.


}; // end SortedList
#include "SortedList.cpp"
#endif
