/**
 * @file PA06.cpp
 *
 * @brief Main driver for project 6
 *
 * @author Willis Allstead
 *
 * @version 1.0
 *
 */

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

bool existsInArray(int toCheck, int arr[], int count);

void visit(int &visited) {
  cout << visited << endl;
}

int main() {
  /* Randomly generate 100 unique values in the range of [1-200] */
  int randArr[100];
  int max = 200;
  for (int index = 0; index < 100; index++) {
      int random_int;
      do {
        random_int = (rand()%(max-1))+1; // from 1 to 200
      } while (existsInArray(random_int, randArr, index)); // inefficient
      // cout << random_int << endl;
      randArr[index] = random_int;
  }

  /* Insert them into a binary search tree (BST1) */
  BinarySearchTree<int> BST1;

  for (int i = 0; i < 100; i++) {
    BST1.add(randArr[i]);
    // cout << "height after adding: " << i << ": "<< BST1.getHeight() << endl; DEBUG ONLY
  }


  /* Print height and inorder output of the BST1 tree */
  cout << "height of BST1 after adding 100 unique values: "<< BST1.getHeight() << endl;
  cout << "BST1 inorder traverse: " << endl;
  BST1.inorderTrav(visit);

  /* Randomly generate 10 unique values in the range of [1-200] where there is an overlap with the previous values */
  // since the randArr is already randomized, taking the first 10 out of the array should suffice
  int randArr2[10];
  for (int j = 0; j < 10; j++) {
    randArr2[j] = randArr[j];
  }

  /* Insert them into another binary search tree (BST2) */
  BinarySearchTree<int> BST2;

  for (int i = 0; i < 10; i++) {
    BST2.add(randArr[i]);
  }

  /* Print preorder, inorder, and postorder output of the BST2 tree */
  cout << "BST2 preorder traverse: " << endl;
  BST2.preorderTrav(visit);
  cout << "BST2 inorder traverse: " << endl;
  BST2.inorderTrav(visit);
  cout << "BST2 postorder traverse: " << endl;
  BST2.postorderTrav(visit);



  /* Find and remove any values of BST2 from BST1 */
  for (int k = 0; k < 10; k++) {
    BST1.remove(randArr2[k]);
  }

  /* Print height, number of nodes, and inorder output of the modified BST1 tree */
  cout << "height of BST1 after removing BST2 values: "<< BST1.getHeight() << endl;
  cout << "number of nodes in BST1 after removing BST2 values: "<< BST1.getNumberOfNodes() << endl;
  cout << "BST1 inorder traverse after removing BST2 values: " << endl;
  BST1.inorderTrav(visit);

  /* Clear the binary search trees. Print whether trees are empty before and after clear operation */
  cout << "is BST1 empty? : " << BST1.isEmpty() << endl;
  cout << "is BST2 empty? : " << BST2.isEmpty() << endl;

  BST1.clear();
  // cout << "number of nodes in BST1 after clear: "<< BST1.getNumberOfNodes() << endl;
  BST2.clear();
  cout << "is BST1 empty? : " << BST1.isEmpty() << endl;
  cout << "is BST2 empty? : " << BST2.isEmpty() << endl;

  return 0;
}

bool existsInArray(int toCheck, int arr[], int count) {
  for (int i = 0; i < count; i++) {
    if (arr[i] == toCheck) {
      return true;
    }
  }
  return false;
}
