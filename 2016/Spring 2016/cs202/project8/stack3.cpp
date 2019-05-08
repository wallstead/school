// node

#include "stackN.h"

Node::Node(char data, Node *next) {
    this->data = data;
    this->next = next;
}

Stack::Stack(int ignore) {
    top = NULL;
}

Stack::Stack(const Stack &toCopy) {
    top = NULL;

    Node *copyNode = toCopy.top;

    while(copyNode != NULL) {
        this->push(copyNode->data);
        copyNode = copyNode->next;
    }
}

Stack::~Stack(){
    this->clear();
    delete [] top;
}

bool Stack::push(char data) {
    if (!full()) {
        Node *tmp = new Node(data, NULL);

        if (!empty()) {
            tmp->next = top;
        }

        top = tmp;

        return true;
    } else {
        return false;
    }
}

bool Stack::pop(char &data) {
    if (!empty()) {

        data = top->data;
        Node *tmp = top;
        top = top->next;
        delete tmp;


        return true;
    } else {
        return false;
    }
}

bool Stack::empty() const {
    if (top == NULL) {
        return true;
    } else {
        return false;
    }
}

bool Stack::full() const {
    return false;
}

bool Stack::clear() {
    if (!empty()) {
        Node *currentNode = top;

        while(currentNode != NULL) {
            Node *tmp = currentNode;
            currentNode = currentNode->next;
            delete [] tmp;
            tmp = NULL;
        }
        top = NULL;

        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream &fout, const Stack &stackToPrint) {
    Node *currentTop = stackToPrint.top;
    fout << "[ ";
    while(currentTop != NULL) {
        fout << currentTop->data << "->";
        currentTop = currentTop->next;
    }
    fout << " ]";
    currentTop = stackToPrint.top;
    return fout;
}

bool Stack::operator==(const Stack &toCopy) const {
    // not done
    return true;
}
