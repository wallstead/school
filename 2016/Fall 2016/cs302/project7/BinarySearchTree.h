/**
 * @file BinarySearchTree.h
 *
 * @brief Header file for the Binary Search Tree class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Binary Search Tree class
 *
 * @version 0.5
 *
 */

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryNode.h"
#include "BinaryNodeTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
private:
  BinaryNode<ItemType> *rootPtr;

protected:
  BinaryNode<ItemType>* placeNode(BinaryNode<ItemType> *subTreePtr,
                                  BinaryNode<ItemType> *newNodePtr);
  // Removes the given target value from the tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType>* removeValue(BinaryNode<ItemType> *subTreePtr,
                                    const ItemType &target,
                                    bool &isSuccessful);
  // Removes a given node from a tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType>* removeNode(BinaryNode<ItemType> *nodeToRemovePtr);

  // Removes the leftmost node in the left subtree of the node
  // pointed to by nodePtr.
  // Sets inorderSuccessor to the value in this node.
  // Returns a pointer to the revised subtree.
  BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType> *nodePtr,
                                           ItemType &inorderSuccessor);
  BinaryNode<ItemType>* findNode(BinaryNode<ItemType> *treePtr,
                                 const ItemType &target) const;
  // Clears the tree recursively.
  void clearTree(BinaryNode<ItemType> *subTreePtr);

public:
  //------------------------------------------------------------
  // Constructor and Destructor Section.
  //------------------------------------------------------------
  BinarySearchTree();
  ~BinarySearchTree();

  //------------------------------------------------------------
  // Public Methods Section.
  //------------------------------------------------------------
  bool isEmpty() const;
  int getHeight() const;
  int getNumberOfNodes() const;
  ItemType getRootData() const; // TODO: make this throw for safety
  void setRootData(ItemType &newEntry);
  bool add(const ItemType &newData);
  bool remove(const ItemType &target); // TODO: implement this
  void clear();
  ItemType getEntry(const ItemType &anEntry) const; // TODO: make this throw for safety

  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  void preorderTrav(void visit(ItemType&)) const;
  void inorderTrav(void visit(ItemType&)) const;
  void postorderTrav(void visit(ItemType&)) const;
}; // end BinarySearchTree

#include "BinarySearchTree.cpp"
#endif
