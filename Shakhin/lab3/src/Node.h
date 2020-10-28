//
// Created by shakhinn on 27.10.2020.
//

#ifndef AISD_LB3_NODE_H
#define AISD_LB3_NODE_H


class Node {
private:
    Node* right;
    int data;
    Node* left;
public:
    Node(): right(nullptr), data(0), left(nullptr){}

    Node* getLeft();

    Node* getRight();

    int getData() const;

    void setLeft(Node* l);

    void setRight(Node* r);

    void setData(int d);

};


#endif //AISD_LB3_NODE_H
