/**
 * @file LinkedList.h
 *
 * @brief Header file for the Linked List ADT
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies the members of the Linked list ADT
 *
 * @version 0.10
 *
 */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
    Node<ItemType>* headPtr; // Pointer to first node in the chain;
    // (contains the first entry in the list)
    int itemCount;           // Current count of list items

    // Locates a specified node in this linked list.
    // @pre  position is the number of the desired node;
    //       position >= 1 and position <= itemCount.
    // @post  The node is found and a pointer to it is returned.
    // @param position  The number of the node to locate.
    // @return  A pointer to the node at the given position.
    Node<ItemType>* getNodeAt(int position) const;

    // Attempt to insert a new node into the chain.
    // @pre  position is the number of the desired position;
    // @post  A node is inserted at the position.
    // @param position  The number of the wanted position.
    // @return  A pointer to the node inserted at the given position.
    Node<ItemType>* insertNode(int position, Node<ItemType>* newNodePtr, Node<ItemType>* subChainPtr);

public:
    LinkedList();
    LinkedList(const LinkedList<ItemType>& aList);
    virtual ~LinkedList();

    /** Sees whether this list is empty.
     @return True if the list is empty; otherwise returns false. */
    bool isEmpty() const;

    /** Gets the current number of entries in this list.
     @return The integer number of entries currently in the list. */
    int getLength() const;

    /** Inserts an entry into this list at a given position.
     @pre  None.
     @post  If 1 <= position <= getLength() + 1 and the insertion is
        successful, newEntry is at the given position in the list,
        other entries are renumbered accordingly, and the returned
        value is true.
     @param newPosition  The list position at which to insert newEntry.
     @param newEntry  The entry to insert into the list.
     @return  True if insertion is successful, or false if not. */
    bool insert(int newPosition, const ItemType& newEntry);

    /** Removes the entry at a given position from this list.
     @pre  None.
     @post  If 1 <= position <= getLength() and the removal is successful,
        the entry at the given position in the list is removed, other
        items are renumbered accordingly, and the returned value is true.
     @param position  The list position of the entry to remove.
     @return  True if removal is successful, or false if not. */
    bool remove(int position);

    /** Removes all entries from this list.
     @post  List contains no entries and the count of items is 0. */
    void clear();

    /** @throw PrecondViolatedExcept if position < 1 or
     position > getLength(). */
    ItemType getEntry(int position) const throw(PrecondViolatedExcept);

    /** @throw PrecondViolatedExcept if position < 1 or
     position > getLength(). */
    void replace(int position, const ItemType& newEntry)
    throw(PrecondViolatedExcept);
}; // end LinkedList

#include "LinkedList.cpp"
#endif
