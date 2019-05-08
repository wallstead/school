#include "listnode.h"

Node::Node(int data, Node *next) {
    this->data = data;
    this->next = next;
}

ListNode::ListNode(int ignore) {
    head = cursor = NULL;
}

ListNode::ListNode(const ListNode &toCopy) {
    if (toCopy.isEmpty()) {
        head = cursor = NULL;
    } else {
        head = cursor = new Node(toCopy.head->data, NULL); // create the first Node
        Node *stmp = toCopy.head; // source traverser
        Node *dtmp = head; // destination traverser

        while(stmp != NULL) {
            if (stmp->next != NULL) {
                Node *newDNode = new Node(stmp->next->data, NULL); // Create new node with stmp's data
                dtmp->next = newDNode; // Point (node at dtmp)'s next to it
                dtmp = newDNode; // Set dtmp to the the new node;
            }
            if (stmp == toCopy.cursor) {
                cursor = dtmp;
            }
            stmp = stmp->next; // go to next source node
        }
    }
}

ListNode::~ListNode() {
    clear();
}

bool ListNode::insertAfter(int data) {
    if (!isFull()) {
        if (isEmpty()) {
            head = cursor = new Node(data, NULL);
        } else {
            Node *tmp = new Node(data, NULL); // Create new node
            if (cursor->next == NULL) { // at the end
                cursor->next = tmp; // Point (node at cursor)'s next to it
                cursor = tmp; // Set cursor to the the new node;
                tmp = NULL; // Remove the tmp node pointer;
            } else { // not at the end
                tmp->next = cursor->next; // attach this to what the one after the cursor
                cursor->next = tmp; // point next of cursor to this new node
                cursor = tmp; // Set cursor to the the new node;
                tmp = NULL; // Remove the tmp node pointer;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool ListNode::insertBefore(int data) {
    if (!isFull()) {
        if (isEmpty()) {
            head = cursor = new Node(data, NULL);
        } else {
            if (cursor == head) { // at first node
                cursor = head = new Node(data, head);
            } else {
                Node *tmp = new Node(cursor->data, cursor->next); // Create copy of node at cursor
                cursor->next = tmp;
                cursor->data = data;
                tmp = NULL; // Remove the tmp node pointer;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool ListNode::get(int &current) const {
    if (!isEmpty()) {
        current = cursor->data;
        return true;
    } else {
        return false;
    }
}

bool ListNode::remove(int &removed) {
    if (!isEmpty()) {
        removed = cursor->data;
        if (cursor == head) { // at first node
            cursor = head = head->next;
        } else {
            Node *tmp = cursor; // leave tmp node pointer at cursor
            goToPrior();
            cursor->next = tmp->next; // link cursor to next one
            tmp = NULL;
        }
        return true;
    } else {
        return false;
    }
}

void ListNode::clear() {
    if (!isEmpty()) {
        Node *del = head; // start deletion node at head

        while (head != NULL) {
            del = del->next;
            delete head;
            head = del;
        }

        head = cursor = NULL;
    }
}

bool ListNode::goToBeginning() {
    if (!isEmpty()) {
        cursor = head;
        return true;
    } else {
        return false;
    }
}

bool ListNode::goToEnd() {
    if (!isEmpty()) {
        while(cursor->next != NULL) {
            cursor = cursor->next;
        }
        return true;
    } else {
        return false;
    }
}

bool ListNode::goToNext() {
    if (!isEmpty()) {
        if (cursor->next != NULL) { // as long as its not at the end
            cursor = cursor->next;
            return true;
        } else {
            return false; // as nancy said
        }
    } else {
        return false;
    }
}

bool ListNode::goToPrior() {
    if (!isEmpty()) {
        if (cursor != head) { // not at first node
            Node *traverser = head;
            while(traverser->next != cursor) {
                traverser = traverser->next;
            }
            cursor = traverser;
            traverser = NULL;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ListNode::isEmpty() const {
    return (head == NULL);
}

bool ListNode::isFull() const {
    return false;
}

bool ListNode::readFile(string fileName) {
    fstream fin;
    fin.open(fileName);
    if (fin.good()) {
        clear();
        int number;
        while (true) {
            fin >> number;
            if(fin.eof()) { break; }
            insertAfter(number);
        }
        return true;
    } else {
        return false;
    }
}

int ListNode::count() {
    int count = 0;
    while (cursor != NULL) {
        count++;
        cursor = cursor->next;
    }
    cursor = head;
    return count;
}

ListNode& ListNode::operator=(const ListNode &toCopy) {
    this->clear();
    if (toCopy.isEmpty()) {
        this->head = this->cursor = NULL;
    } else {
        this->head = this->cursor = new Node(toCopy.head->data, NULL); // create the first Node
        Node *stmp = toCopy.head; // source traverser
        Node *dtmp = this->head; // destination traverser

        while(stmp != NULL) {
            if (stmp->next != NULL) {
                Node *newDNode = new Node(stmp->next->data, NULL); // Create new node with stmp's data
                dtmp->next = newDNode; // Point (node at dtmp)'s next to it
                dtmp = newDNode; // Set dtmp to the the new node;
            }
            if (stmp == toCopy.cursor) {
                this->cursor = dtmp;
            }
            stmp = stmp->next; // go to next source node
        }
    }

    return *this;
}

ostream& operator << (ostream &out, const ListNode &toPrint) {
    Node *traverser = toPrint.head;
    while(traverser) {
        if (traverser == toPrint.cursor) {
            out << "[" << traverser->data << "] ";
        } else {
            out << "|" << traverser->data << "| ";
        }
        traverser = traverser->next;
    }
    traverser = NULL;

    return out;
}
