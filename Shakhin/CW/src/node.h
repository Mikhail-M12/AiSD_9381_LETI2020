#ifndef NODE_H
#define NODE_H

class Node {
private:
    Node* right;
    int data;
    int amount;
    Node* left;
public:
    Node(): right(nullptr), data(0), amount(0), left(nullptr){}

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

#endif // NODE_H
