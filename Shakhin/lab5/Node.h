#ifndef AISD_LB5_NODE_H
#define AISD_LB5_NODE_H


class Node {
private:
    Node* right;
    int data;
    int amount;
    Node* left;
public:
    Node(): right(nullptr), data(0), left(nullptr), amount(0){}

    Node* getLeft();

    Node* getRight();

    int getData() const;

    int getAmount() const;

    void incAmount();

    void setAmount(int am);

    void setLeft(Node* l);

    void setRight(Node* r);

    void setData(int d);

};


#endif //AISD_LB5_NODE_H
