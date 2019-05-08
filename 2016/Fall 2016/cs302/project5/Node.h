/**
 * @file Node.h
 *
 * @brief Header file for the Node class
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies the members of the Node class and defines function parameters
 *
 * @version 0.10
 *
 */
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
private:
    ItemType        item; // A data item
    Node<ItemType>* next; // Pointer to next node

public:
    Node();
    Node(const ItemType& anItem);
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
    void setItem(const ItemType& anItem);
    void setNext(Node<ItemType>* nextNodePtr);
    ItemType getItem() const ;
    Node<ItemType>* getNext() const ;
}; // end Node

#include "Node.cpp"
#endif
