/**
 * @file Stack.cpp
 *
 * @brief Header/Implementation file for the Stack Class
 *
 * @author Willis Allstead
 *
 * @details Defines functions for the Stack Class
 *
 * @version 0.50
 *
 */
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdexcept> // for underflow errors
#include <vector>
using namespace std;

template <class T>
class Stack {
public:
	bool isEmpty();
	void push(T item);
	T peek();
	void pop();
private:
	vector<T> data; // using vector as Iman said we could in canvas forum
};

/**
  * @brief isEmpty function
  *
  * @details returns if the stack is empty or not
  */
template <class T>
bool Stack<T>::isEmpty() {
	return data.empty();
}

/**
  * @brief push function
  *
  * @details adds an item to the stack
  */
template <class T>
void Stack<T>::push(T item) {
	data.push_back(item);
}

/**
  * @brief peek function
  *
  * @details returns item at the top of the stack
  */
template <class T>
T Stack<T>::peek() {
	if(!isEmpty())
	return data.back();
	else
		throw underflow_error("Can't peek from an empty stack");
}

/**
  * @brief pop function
  *
  * @details removes the item at the top of the stack
  */
template <class T>
void Stack<T>::pop() {
	data.pop_back();
}

#endif
