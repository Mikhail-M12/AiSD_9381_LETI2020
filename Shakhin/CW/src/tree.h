#ifndef BIMARYTREE_H
#define BIMARYTREE_H

#include "node.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;



class BinaryTree{
public:
    explicit BinaryTree(std::vector<int>& arr, string& str);
    void printTree(Node* node);
    Node* getTree();
    ~BinaryTree();
    void findElem(int e, string& str);
    void addElem(int e, string& str);
    void deleteElem(int e, string& str);
    int getMaxDepth();
private:
    int maxDepth;
    Node* tree;
    Node* makeTree(int n, std::vector<int>& arr, int& pos, int indent, string& str);
    void destroy(Node*& buf);
    void treeToArrAdd(Node* node, std::vector<int>& arr, int e, string& str);
    void treeToArrDelete(Node* node, std::vector<int>& arr, int e, string& str);
    void treeToArrHelp(Node* node, std::vector<int>& arr, string& str);
    bool find(Node* node, int x, string& str);

};


#endif // BIMARYTREE_H
