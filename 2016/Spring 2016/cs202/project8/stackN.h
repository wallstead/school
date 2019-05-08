#include <iostream>

using namespace std;

class Stack;

class Node{
	private:
		Node(char, Node*);
		char data;
		Node* next;
		friend class Stack;
              	friend ostream& operator<<(ostream&, const Stack&);
};

class Stack{
        public:
                Stack(int = 0);
                Stack(const Stack&);
                ~Stack();
                Stack& operator=(const Stack&);
                bool push(char);
                bool pop(char&);
                bool empty() const;
                bool full() const;
                bool clear();
		bool operator==(const Stack&) const;
                friend ostream& operator<<(ostream&, const Stack&);
        private:
		Node* top;
};
