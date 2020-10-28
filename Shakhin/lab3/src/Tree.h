#ifndef AISD_LB3_TREE_H
#define AISD_LB3_TREE_H

#include "Node.h"
#include "structs.h"
#define MIN -30000
#define MAX 30000

class BinaryTree{
public:
    explicit BinaryTree(string& str);
    bool checkBST(); 
    bool checkPiramid();
    ~BinaryTree();

private:
    Node* tree;
    void skip (string& str, int& pos, int n = 1);
    int getNum(string& input, int& pos);
    Node* scanTree(string& str, int& pos);
    void destroy(Node*& buf);

    bool checkBst_left(Node* node, int min = MIN , int max = MAX, int indent = 0);
    bool checkBst_right(Node* node, int min = MIN, int max = MAX, int indent = 0);

    bool checkPiramid_leaf(Node* node, int max, int indent);

};







#endif //AISD_LB3_TREE_H
