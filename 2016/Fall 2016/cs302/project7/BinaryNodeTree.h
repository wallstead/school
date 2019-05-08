/**
 * @file BinaryNodeTree.h
 *
 * @brief Header file for the Binary Node Tree class
 *
 * @author Willis Allstead
 *
 * @details Specifies the members of the Binary Node Tree class
 *
 * @version 0.5
 *
 */

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include <algorithm>    // for std::max, which is used in book's code
#include "BinaryNode.h"

template<class ItemType>
class BinaryNodeTree {
private:
  BinaryNode<ItemType> *rootPtr;

protected:
  //------------------------------------------------------------
  // Protected Utility Methods Section:
  // Recursive helper methods for the public methods.
  //------------------------------------------------------------
  int getHeightHelper(BinaryNode<ItemType> *subTreePtr) const;
  int getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const;
  // Recursively adds a new node to the tree in a left/right fashion to
  // keep the tree balanced.
  BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType> *subTreePtr,
                                    BinaryNode<ItemType> *newNodePtr);
  // Removes the target value from the tree by calling moveValuesUpTree
  // to overwrite value with value from child.
  BinaryNode<ItemType>* removeValue(BinaryNode<ItemType> *subTreePtr,
                                    const ItemType target,
                                    bool &isSuccessful);
  BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType> *subTreePtr);
  BinaryNode<ItemType>* findNode(BinaryNode<ItemType> *treePtr,
                                 const ItemType &target,
                                 bool &isSuccessful) const;
  BinaryNode<ItemType>* copyTree(BinaryNode<ItemType> *oldTreePtr) const;
  // Recursively deletes all nodes from the tree.
  void destroyTree(BinaryNode<ItemType> *subTreePtr);

  // Recursive traversal helper methods:
  void preorder(void visit(ItemType&), BinaryNode<ItemType> *treePtr) const;
  void inorder(ItemType&, BinaryNode<ItemType> *treePtr) const;
  void postorder(void visit(ItemType&), BinaryNode<ItemType> *treePtr) const;

public:
  //------------------------------------------------------------
  // Constructor and Destructor Section.
  //------------------------------------------------------------
  BinaryNodeTree();
  ~BinaryNodeTree();

  bool isEmpty() const;
  int getHeight() const;
  int getNumberOfNodes() const;
  ItemType getRootData() const;
  void setRootData(const ItemType &newData);
  bool add(const ItemType &newData); // adds item to tree
  bool remove(const ItemType &data); // removes item from treePtr
  void clear();
  ItemType getEntry(const ItemType &anEntry) const;
  bool contains(const ItemType &anEntry) const;

  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  void preorderTraverse(void visit(ItemType&)) const;
  void inorderTraverse(void visit(ItemType&)) const;
  void postorderTraverse(void visit(ItemType&)) const;

  BinaryNodeTree& operator=(const BinaryNodeTree &rhs);
}; // end BinaryNodeTree

#include "BinaryNodeTree.cpp"
#endif
