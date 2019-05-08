#include "stack.cpp"
#include <iostream>
#include <string>

using namespace std;


template<typename T>
void printStack(Stack<T> stack, int stackSize)
{
	// declare variables
	T item;

	// loop and print the stack with formatting
	for(int i = 0; i < stackSize; i++)
	{
		// if an item has been popped off the stack
		if(stack.pop(item))
		{
			// print the top of the stack
			if(i == 0)
				cout << "[" << item << "] ";

			// print other stack items
			else
				cout << item << " ";
		}
		// print empty stack
		else if(i == 0)
		{
			cout << "[empty stack] ";
		}
	}
	cout << endl;
}


int main()
{
	// declare variables
	int testItem;
	string stringItem;
	Stack <string> stringStack (3);
	Stack <int> intStack (5);

	// print test name
    cout << endl << endl << "Integer Stack: " << endl;

    // push 0 through 5
    for(int i = 0; i < 5; i++)
    {
    	intStack.push(i);
    }

   	cout << "Testing Int Stack Insertion Operator: " << intStack << endl;

   	intStack.clear();

	// test integer stack
	intStack.push(1);
	printStack(intStack, 5);

	intStack.push(2);
	printStack(intStack, 5);

	intStack.pop(testItem);
	printStack(intStack, 5);

	intStack.push(5);
	printStack(intStack, 5);

	intStack.push(4);
	printStack(intStack, 5);



	// print test name
	cout << endl << endl << "String Stack: " << endl;

	// push a through c
    stringStack.push("a");
    stringStack.push("b");
    stringStack.push("c");


   	cout << "Testing String Stack Insertion Operator: " << stringStack << endl;

   	stringStack.clear();

	// test string stack
	stringStack.push("orange");
	printStack(stringStack, 3);

	stringStack.pop(stringItem);
	printStack(stringStack, 3);

	stringStack.push("dog");
	printStack(stringStack, 3);

	stringStack.push("apple");
	printStack(stringStack, 3);

	stringStack.pop(stringItem);
	printStack(stringStack, 3);

	stringStack.push("cat");
	printStack(stringStack, 3);

	cout << endl << endl;


	// end program
	return 0;
}
