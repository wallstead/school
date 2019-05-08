/**
 * @file BinaryNodeTree.cpp
 *
 * @brief Implementation file for the Binary Node Tree class
 *
 * @author Willis Allstead
 *
 * @version 0.5
 *
 */

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() {
  rootPtr = nullptr;
}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree() {

}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *subTreePtr) const {
  if (subTreePtr == nullptr) {
    return 0;
  } else {
    return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr())); // max returns largest of two
  }
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const {
  /* TODO: make this work correctly */
  if (subTreePtr == nullptr) {
    return 0;
  } else {
    return 1 + getNumberOfNodesHelper(subTreePtr -> getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr -> getRightChildPtr());
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType> *subTreePtr,
                                                            BinaryNode<ItemType> *newNodePtr) {
  if (subTreePtr == nullptr) {
    return newNodePtr;
  } else {

    // std::cout << "adding " << newNodePtr->getItem() << std::endl;
    BinaryNode<ItemType> *leftPtr = subTreePtr->getLeftChildPtr();
    BinaryNode<ItemType> *rightPtr = subTreePtr->getRightChildPtr();

    if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)) {
      rightPtr = balancedAdd(rightPtr, newNodePtr);
      subTreePtr->setRightChildPtr(rightPtr);
    } else {
      leftPtr = balancedAdd(leftPtr, newNodePtr);
      subTreePtr->setLeftChildPtr(leftPtr);
    }

    return subTreePtr;
  }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType> *treePtr) const {
  if (treePtr != nullptr) {
    /* ROOT -> LEFT -> RIGHT */
    ItemType theItem = treePtr->getItem();
    visit(theItem);
    inorder(visit, treePtr->getLeftChildPtr());
    inorder(visit, treePtr->getRightChildPtr());
  }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(ItemType &sum, BinaryNode<ItemType> *treePtr) const {
  if (treePtr != nullptr) { // TODO: check if I can do this by just if(treePtr)
    /* LEFT -> ROOT -> RIGHT */
    inorder(sum, treePtr->getLeftChildPtr());
    ItemType theItem = treePtr->getItem();
    sum += theItem;

    inorder(sum, treePtr->getRightChildPtr());
  }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType> *treePtr) const {
  if (treePtr != nullptr) { // TODO: check if I can do this by just if(treePtr)
    /* LEFT -> RIGHT -> ROOT */
    inorder(visit, treePtr->getLeftChildPtr());
    inorder(visit, treePtr->getRightChildPtr());
    ItemType theItem = treePtr->getItem();
    visit(theItem);
  }
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {
  return (rootPtr == nullptr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {
  return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {
  return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const {
  return rootPtr->getItem();
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType &newData) {
  return rootPtr->setItem(newData);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType &newData) {
  BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>;
  newNodePtr->setItem(newData);

  rootPtr = balancedAdd(rootPtr, newNodePtr);

  return true;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const {
  preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
  inorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const {
  postorder(visit, rootPtr);
}
