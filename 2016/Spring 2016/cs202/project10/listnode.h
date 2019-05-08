#include <iostream>
using namespace std;

class ListNode;

class Node {
private:
    Node(int, Node*);
    int data;
    Node *next;

    friend class ListNode;
    friend ostream& operator << (ostream&, const ListNode&);
};

class ListNode {
public:
    ListNode(int=10);
    ListNode(const ListNode&);
    ~ListNode();

    bool insertAfter(int);
    bool insertBefore(int);
    bool get(int&) const;
    bool remove(int&);

    void clear();

    bool goToBeginning();
    bool goToEnd();

    bool goToNext();
    bool goToPrior();

    bool isEmpty() const;
    bool isFull() const;

    ListNode& operator = (const ListNode&);

    friend ostream& operator << (ostream&, const ListNode&);

private:
    Node *head;
    Node *cursor;
};
