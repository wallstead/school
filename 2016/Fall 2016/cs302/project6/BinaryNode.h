/**
 * @file BinaryNode.h
 *
 * @brief Header file for the Binary Node class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the BinaryNode class
 *
 * @version 0.5
 *
 */

#ifndef BINARY_NODE_
#define BINARY_NODE_

template<class ItemType>
class BinaryNode {
private:
  ItemType item; // data stored in node
  BinaryNode<ItemType> *leftChildPtr;
  BinaryNode<ItemType> *rightChildPtr;

public:
  BinaryNode();
  // ~BinaryNode();

  /** Sets the item data member **/
  void setItem(const ItemType &anItem);
  /** Returns the item data member
    @return The item data member. */
  ItemType getItem() const;
  /** Tells if the node is a leaf
    @return Whether or not the node is a leaf of the tree. */
  bool isLeaf() const;

  BinaryNode<ItemType>* getLeftChildPtr() const;
  BinaryNode<ItemType>* getRightChildPtr() const;

  void setLeftChildPtr(BinaryNode<ItemType> *leftPtr);
  void setRightChildPtr(BinaryNode<ItemType> *rightPtr);
};

#include "BinaryNode.cpp"
#endif
