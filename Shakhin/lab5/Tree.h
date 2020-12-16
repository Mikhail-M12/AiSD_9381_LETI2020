#ifndef AISD_LB5_TREE_H
#define AISD_LB5_TREE_H

#include "Node.h"
#include "structs.h"


class BinaryTree{
public:
    explicit BinaryTree(std::vector<int>& arr);
    void printTree(Node* node);
    Node* getTree();
    ~BinaryTree();
    void findElem(int e);
    void addElem(int e);
private:
    Node* tree;
    Node* makeTree(int n, std::vector<int>& arr, int& pos, int indent);
    void destroy(Node*& buf);
    void treeToArr(Node* node, std::vector<int>& arr, int e);
    void treeToArrHelp(Node* node, std::vector<int>& arr);
    bool find(Node* node, int x);

};


#endif //AISD_LB5_TREE_H
