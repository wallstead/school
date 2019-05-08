#include <iostream>

using namespace std;

class Queue;

class Node{
	private:
		Node(int, Node*);
		int data;
		Node* next;
		friend class Queue;
		friend ostream& operator<<(ostream&, const Queue&);
};

class Queue{
	public:
		Queue(int = 0);
		Queue(const Queue&);
  		~Queue();
		Queue& operator=(const Queue&);
		bool enqueue(int);
		bool dequeue(int&);
		bool empty() const;
		bool full() const;
		bool clear();
		bool operator==(const Queue&) const;
		friend ostream& operator<<(ostream&, const Queue&);
	private:
		Node* front;
		Node* rear;
};