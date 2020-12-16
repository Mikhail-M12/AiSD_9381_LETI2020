#include "Node.h"

int Node::getData() const {
    return data;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

int Node::getAmount() const {
    return amount;
}

void Node::setData(int d) {
    data = d;
}

void Node::setLeft(Node *l) {
    left = l;
}

void Node::setRight(Node *r) {
    right = r;
}

void Node::setAmount(int am) {
    amount = am;
}
void Node::incAmount() {
    amount++;
}