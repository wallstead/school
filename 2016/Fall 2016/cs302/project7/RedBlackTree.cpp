/**
 * @file RedBlackTree.cpp
 *
 * @brief Implementation file for the Red Black Tree class
 *
 * @author Willis Allstead
 *
 * @version 0.5
 *
 */

template<class ItemType>
RedBlackTree<ItemType>::RedBlackTree() {
  rootPtr = nullptr;
}

template<class ItemType>
RedBlackTree<ItemType>::~RedBlackTree() {

}

template<class ItemType>
void RedBlackTree<ItemType>::rotateLeft(BinaryNode<ItemType> *x) {
  BinaryNode<ItemType> *y;
  y = x->getRightChildPtr();
  x->setRightChildPtr(y->getLeftChildPtr()); // Turn y's left sub-tree into x's right sub-tree
  if (y->getLeftChildPtr() != nullptr) {
    y->getLeftChildPtr()->setParentPtr(x);
  }

  y->setParentPtr(x->getParentPtr()); // y's new parent is x's old parent

  if (x->getParentPtr() == nullptr) {
    rootPtr = y;
  } else {
    if (x == (x->getParentPtr()->getLeftChildPtr())) {
      x->getParentPtr()->setLeftChildPtr(y);
    } else {
      x->getParentPtr()->setRightChildPtr(y);
    }
  }
  y->setLeftChildPtr(x); // put x on y's left
  x->setParentPtr(y);
}

template<class ItemType>
void RedBlackTree<ItemType>::rotateRight(BinaryNode<ItemType> *x) {
  BinaryNode<ItemType> *y;
  y = x->getLeftChildPtr();
  x->setLeftChildPtr(y->getRightChildPtr());
  if (y->getRightChildPtr() != nullptr) {
    y->getRightChildPtr()->setParentPtr(x);
  }
  y->setParentPtr(x->getParentPtr());
  if (x->getParentPtr() == nullptr) {
    rootPtr = y;
  } else {
    if (x == (x->getParentPtr()->getRightChildPtr())) {
      x->getParentPtr()->setRightChildPtr(y);
    } else {
      x->getParentPtr()->setLeftChildPtr(y);
    }
  }
  y->setRightChildPtr(x);
  x->setParentPtr(y);
}

template<class ItemType>
void RedBlackTree<ItemType>::insertNode(BinaryNode<ItemType> *x) {
  //  Insert in the tree in the way binary search did
  rootPtr = BinarySearchTree<ItemType>::placeNode(rootPtr, x);
  // Now fix it all
  x->color = red;
  while ((x != rootPtr) && (x->getParentPtr()->color == red)) {
    if ( x->getParentPtr() == x->getParentPtr()->getParentPtr()->getLeftChildPtr() ) {
      BinaryNode<ItemType> *y = x->getParentPtr()->getParentPtr()->getRightChildPtr();
      if (y != nullptr && y->color == red) {
        x->getParentPtr()->color = black;
        y->color = black;
        x->getParentPtr()->getParentPtr()->color = red;
        x = x->getParentPtr()->getParentPtr(); // Move x up the tree
      } else { // is black (or null since I don't have null nodes really)
        if (x == x->getParentPtr()->getRightChildPtr()) {
          x = x->getParentPtr();
          rotateLeft(x);
        }
        x->getParentPtr()->color = black;
        x->getParentPtr()->getParentPtr()->color = red;
        rotateRight(x->getParentPtr()->getParentPtr());
      }
    } else { // RIGHT AND LEFT EXCHANGED FROM PRIOR IF
      BinaryNode<ItemType> *y = x->getParentPtr()->getParentPtr()->getLeftChildPtr();
      if (y != nullptr && y->color == red) {
        x->getParentPtr()->color = black;
        y->color = black;
        x->getParentPtr()->getParentPtr()->color = red;
        x = x->getParentPtr()->getParentPtr(); // Move x up the tree
      } else {
        /* y is a black node (or null since I don't have null nodes really) */
        if (x == x->getParentPtr()->getLeftChildPtr()) {
          x = x->getParentPtr();
          rotateRight(x);
        }
        x->getParentPtr()->color = black;
        x->getParentPtr()->getParentPtr()->color = red;
        rotateLeft(x->getParentPtr()->getParentPtr());
      }
    }
  }
  rootPtr->color = black; // root is always black
}

template<class ItemType>
bool RedBlackTree<ItemType>::isEmpty() const {
  return (rootPtr == nullptr);
}

template<class ItemType>
int RedBlackTree<ItemType>::getHeight() const {
  return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
}

template<class ItemType>
int RedBlackTree<ItemType>::getNumberOfNodes() const {
  return BinaryNodeTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType RedBlackTree<ItemType>::getRootData() const {
  return rootPtr->getItem();
}

template<class ItemType>
void RedBlackTree<ItemType>::setRootData(ItemType &newEntry) {
  return rootPtr->setItem(newEntry);
}

template<class ItemType>
bool RedBlackTree<ItemType>::add(const ItemType &newData) {
  BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>();
  newNodePtr->setItem(newData);

  insertNode(newNodePtr);

  return true;
}

template<class ItemType>
bool RedBlackTree<ItemType>::remove(const ItemType &target) {
  bool isSuccessful = false;
  rootPtr = removeValue(rootPtr, target, isSuccessful);
  return isSuccessful;
}

template<class ItemType>
void RedBlackTree<ItemType>::clear() {
  BinarySearchTree<ItemType>::clearTree(rootPtr);
  rootPtr = nullptr;
}

// Traversals will stay the same for red-black trees

template<class ItemType>
void RedBlackTree<ItemType>::preorderTrav(void visit(ItemType&)) const {
  BinaryNodeTree<ItemType>::preorder(visit, rootPtr);
}

template<class ItemType>
void RedBlackTree<ItemType>::inorderTrav(ItemType &sum) const {
  BinaryNodeTree<ItemType>::inorder(sum, rootPtr);
}

template<class ItemType>
void RedBlackTree<ItemType>::postorderTrav(void visit(ItemType&)) const {
  BinaryNodeTree<ItemType>::postorder(visit, rootPtr);
}
