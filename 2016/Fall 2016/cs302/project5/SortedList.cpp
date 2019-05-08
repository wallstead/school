//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
/**
 * @file SortedList.cpp
 *
 * @brief Implementation file for the SortedList class
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies function of the class.
 *
 * @version 0.10
 *
 */

#include <ctime>

template<class ItemType>
SortedList<ItemType>::SortedList()
{
}  // end default constructor

template<class ItemType>
SortedList<ItemType>::SortedList(const SortedList<ItemType>& sList)
	                                          : LinkedList<ItemType>(sList)
{
}  // end copy constructor

template<class ItemType>
SortedList<ItemType>::~SortedList()
{
}  // end destructor

// template<class ItemType>
// bool SortedList<ItemType>::insertSorted(const ItemType& newEntry)
// {
//    int newPosition = std::abs(getPosition(newEntry));
//    // We need to call the LinkedList version of insert, since the
//    // SortedList version does nothing but return false
//    return LinkedList<ItemType>::insert(newPosition, newEntry);
// }  // end insertSorted

template<class ItemType>
bool SortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
   int newPosition = std::abs(getPosition(newEntry));
   // We need to call the LinkedList version of insert, since the
   // SortedList version does nothing but return false
   return LinkedList<ItemType>::insert(newPosition, newEntry);
}  // end insertSorted


template<class ItemType>
bool SortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
   int position = getPosition(anEntry);
   bool ableToRemove = position > 0;

   if (ableToRemove)
      ableToRemove = LinkedList<ItemType>::remove(position);

   return ableToRemove;
}  // end removeSorted

template<class ItemType>
int SortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
	int position = 1;
	int length = LinkedList<ItemType>::getLength();

	while ( (position <= length) &&
			(anEntry > LinkedList<ItemType>::getEntry(position)) ) {
		position++;
	}  // end while

	if ( (position > length) || (anEntry != LinkedList<ItemType>::getEntry(position)) ) {
		position = -position;
	}  // end if

	// cout << anEntry.startTime << ": " << position << endl;

  return position;
}  // end getPosition
