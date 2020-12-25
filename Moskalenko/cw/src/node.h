#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include <sstream>
#include <QGraphicsScene>
using namespace std;
#define COUNT 10

struct Node {
    int key;  // значение элемента узла
    int size;  //размер дерева с корнем в данном узле
    int amount; //количество попыток ввести элемент со значением данного узла
    Node *left;  //левое поддерево
    Node *right; // правое поддерево
    Node(int k) { key = k; size = 1; amount = 1; left = right = nullptr; }
};

class BinTree{
public:
    Node* head;
    BinTree();
    ~BinTree();
    int find(Node *p, int k);
    int getSize(Node* p);
    int maxDepth(Node *p);
    void fixSize(Node* p);
    Node* rotateLeft(Node* p);
    Node* rotateRight(Node* p);
    Node* insert(Node* p, int k, string* str);
    Node* insertRoot(Node* p, int k, string* str);
    Node* join(Node* p, Node* q);
    Node* remove(Node* p, int k, string* str);
    void print2DUtil(Node *root, int space, string* str);
    void recTreePrint(Node* p);
    void destroy(Node* p);
};
#endif // NODE_H

