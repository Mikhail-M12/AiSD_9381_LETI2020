#ifndef BDP_NODE_H
#define BDP_NODE_H
#include <iostream>
using namespace std;
#define COUNT 5

class Node {
    int key;  // значение элемента узла
    int size;  //размер дерева с корнем в данном узле
    int amount; //количество попыток ввести элемент со значением данного узла
    Node *left;  //левое поддерево
    Node *right; // правое поддерево
public:
    Node(int key, Node *left = nullptr, Node *right = nullptr);
    int find(Node *p, int k);
    int getSize(Node* p);
    void fixSize(Node* p);
    Node* rotateLeft(Node* p);
    Node* rotateRight(Node* p);
    Node* insert(Node* p, int k);
    Node* insertRoot(Node* p, int k);
    Node* getLeft();
    Node* getRight();
    void print2DUtil(Node *root, int space);
    void recTreePrint(Node* p);
};

#endif //BDP_NODE_H
