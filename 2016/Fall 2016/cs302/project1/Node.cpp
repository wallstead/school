/**
 * @file Node.cpp
 *
 * @brief Implementation file for the Node class
 *
 * @author Someone at Pearson (I didn't code any of this)
 *
 * @details Specifies the functions of the Node class
 *
 * @version 0.10
 *
 */
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
#include "Node.h"

/**
  * @brief Default constructor for the class
  *
  * @details constructs the class
  */
template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} // end default constructor

/**
  * @brief Copy constructor for the class
  *
  * @details constructs the class using a previously constructed reference
  */
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

/**
  * @brief Constructor for the class
  */
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
item(anItem), next(nextNodePtr)
{
} // end constructor

/**
  * @brief setItem function
  * @details Sets the current item to another item
  */
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
} // end setItem

/**
  * @brief setNext function
  * @details Sets the next item to an item
  */
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
    next = nextNodePtr;
} // end setNext

/**
  * @brief getItem function
  * @details returns current item
  */
template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
    return item;
} // end getItem

/**
  * @brief getNext function
  * @details returns next item       
  */
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
    return next;
} // end getNext
