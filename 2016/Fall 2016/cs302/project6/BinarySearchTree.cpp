/**
 * @file BinarySearchTree.cpp
 *
 * @brief Implementation file for the Binary Search Tree class
 *
 * @author Willis Allstead
 *
 * @version 0.5
 *
 */

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
  rootPtr = nullptr;
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {

}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::placeNode(
                                BinaryNode<ItemType> *subTreePtr,
                                BinaryNode<ItemType> *newNodePtr) {
  if (subTreePtr == nullptr) {
    return newNodePtr;
  } else if (subTreePtr->getItem() > newNodePtr->getItem()) {
    BinaryNode<ItemType> *tempPtr = placeNode(subTreePtr->getLeftChildPtr(),
                                              newNodePtr);
    subTreePtr->setLeftChildPtr(tempPtr);
  } else {
    BinaryNode<ItemType> *tempPtr = placeNode(subTreePtr->getRightChildPtr(),
                                              newNodePtr);
    subTreePtr->setRightChildPtr(tempPtr);
  }

  return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(
                                BinaryNode<ItemType> *subTreePtr,
                                const ItemType &target, bool &isSuccessful) {
  if (subTreePtr == nullptr) {
    isSuccessful = false;
  } else if (subTreePtr->getItem() == target) { // item is root of a subtree
    subTreePtr = removeNode(subTreePtr); // remove item
    isSuccessful = true;
  } else if (subTreePtr->getItem() > target) {
    // search left subtree
    BinaryNode<ItemType> *tempPtr = removeValue(subTreePtr->getLeftChildPtr(),
                                                target, isSuccessful);
    subTreePtr->setLeftChildPtr(tempPtr);
  } else {
    // search right subtree
    BinaryNode<ItemType> *tempPtr = removeValue(subTreePtr->getRightChildPtr(),
                                                target, isSuccessful);
    subTreePtr->setRightChildPtr(tempPtr);
  }

  return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(
                                        BinaryNode<ItemType> *nodeToRemovePtr) {
  if (nodeToRemovePtr->isLeaf()) {
    // remove leaf from tree
    delete nodeToRemovePtr;
    nodeToRemovePtr = nullptr;
    return nodeToRemovePtr;
  } else if ((nodeToRemovePtr->getLeftChildPtr() == nullptr && nodeToRemovePtr->getRightChildPtr() != nullptr) || (nodeToRemovePtr->getRightChildPtr() == nullptr && nodeToRemovePtr->getLeftChildPtr() != nullptr)) { // != is logical XOR
    // if it has only one child
    // std::cout << "hereeeeee"  << std::endl;
    BinaryNode<ItemType> *nodeToConnectPtr;
    if (nodeToRemovePtr->getLeftChildPtr() != nullptr) { // if it has a left child
      nodeToConnectPtr = nodeToRemovePtr->getLeftChildPtr();
    } else { // if it has a right child
      nodeToConnectPtr = nodeToRemovePtr->getRightChildPtr();
    }

    delete nodeToRemovePtr;
    nodeToRemovePtr = nullptr;
    return nodeToConnectPtr;
  } else {
    // has two children
    ItemType newNodeValue;
    BinaryNode<ItemType> *tempPtr = removeLeftmostNode(nodeToRemovePtr->getRightChildPtr(),
                                                       newNodeValue);
    nodeToRemovePtr->setRightChildPtr(tempPtr);
    nodeToRemovePtr->setItem(newNodeValue);

    return nodeToRemovePtr;
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(
                                          BinaryNode<ItemType> *nodePtr,
                                          ItemType &inorderSuccessor) {
  if (nodePtr->getLeftChildPtr() == nullptr) {
    inorderSuccessor = nodePtr->getItem();
    return removeNode(nodePtr);
  } else {
    BinaryNode<ItemType> *tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(),
                                                       inorderSuccessor);
    nodePtr->setLeftChildPtr(tempPtr);
    return nodePtr;
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::clearTree(BinaryNode<ItemType> *subTreePtr) {
  if (subTreePtr) {
    clearTree(subTreePtr->getLeftChildPtr());
    clearTree(subTreePtr->getRightChildPtr());
    delete subTreePtr;
  }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
  return (rootPtr == nullptr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
  return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
  return BinaryNodeTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const {
  return rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(ItemType &newEntry) {
  return rootPtr->setItem(newEntry);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData) {
  BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>;
  newNodePtr->setItem(newData);

  rootPtr = placeNode(rootPtr, newNodePtr);

  return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target) {
  bool isSuccessful = false;
  rootPtr = removeValue(rootPtr, target, isSuccessful);
  return isSuccessful;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
  clearTree(rootPtr);
  rootPtr = nullptr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTrav(void visit(ItemType&)) const {
  BinaryNodeTree<ItemType>::preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTrav(void visit(ItemType&)) const {
  BinaryNodeTree<ItemType>::inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTrav(void visit(ItemType&)) const {
  BinaryNodeTree<ItemType>::postorder(visit, rootPtr);
}
