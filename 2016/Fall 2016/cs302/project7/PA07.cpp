/**
 * @file PA07.cpp
 *
 * @brief Main driver for project 7
 *
 * @author Willis Allstead
 *
 * @version 1.0
 *
 */

#include <iostream>
#include "RedBlackTree.h"

using namespace std;

bool existsInArray(int toCheck, int arr[], int count);

const int numValues = 1000;

int main() {
  /* Randomly generate 1000 unique values in the range of [1-10,000] */
  int randArr[numValues];
  int max = 10000;
  for (int index = 0; index < numValues; index++) {
      int random_int;
      do {
        random_int = (rand()%(max-1))+1; // from 1 to 10,000
      } while (existsInArray(random_int, randArr, index)); // inefficient
      randArr[index] = random_int;
  }
  /* Insert them into a red-black tree (RBT1) */
  RedBlackTree<int> RBT1;

  for (int i = 0; i < numValues; i++) {
    RBT1.add(randArr[i]);
  }

  cout << "Height of tree after inserting " << numValues << " unique nodes: " << RBT1.getHeight() << endl;

  int sum = 0;

  RBT1.inorderTrav(sum);

  cout << "(using inorder) Sum of values in tree: " << sum << endl;

  cout << "Is tree empty before clearing? " << boolalpha << RBT1.isEmpty() << endl;

  RBT1.clear();

  cout << "Is tree empty after clearing? " << boolalpha << RBT1.isEmpty() << endl;

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
