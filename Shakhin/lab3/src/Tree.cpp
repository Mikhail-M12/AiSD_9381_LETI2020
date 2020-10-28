#include "Tree.h"
#include "InOut.h"


BinaryTree::BinaryTree(string &str){
    int pos = 0;
    tree = scanTree(str, pos);
}

BinaryTree::~BinaryTree() {
    destroy(this->tree);
}

void BinaryTree::skip(string& str, int& pos, int n){
    if (str.length() >= n) {
        str = str.substr(n);
        pos++;
    }
}
int BinaryTree::getNum(string& str, int& pos){
    string strNum;
    while (isdigit(str[0]) || (strNum.length() == 0 && str[0] == '-')) {
        strNum += str[0];
        skip(str, pos, 1);
    }
    return stoi(strNum);
}

Node *BinaryTree::scanTree(string& str, int& pos) {
    if(str[0] == '(') {
        skip(str, pos, 1);
        if(str[0] == ')') {
            skip(str, pos, 1);
            return nullptr;
        }
        Node *buf = new Node();
        buf->setData(getNum(str, pos));
        if(str[0] == ')'){
            skip(str, pos, 1);
            buf->setLeft(nullptr);
            buf->setRight(nullptr);
            return buf;
        }
        if(str[0] == '('){
            buf->setLeft(scanTree(str, pos));
            if(str[0] == '('){
                buf->setRight(scanTree(str, pos));
                if(str[0]== ')') {
                    skip(str, pos, 1);
                    return buf;
                } else cout<<"error";
            }else if(str[0]== ')'){
                skip(str, pos, 1);
                return buf;
            }

        }

    }
    else{ cout<<"error";}
    return nullptr;
}

void BinaryTree::destroy(Node*& buf){
    if(buf != nullptr) {
        Node* left = buf->getLeft();
        Node* right = buf->getRight();
        destroy(left);
        destroy(right);
        delete buf;
    }
}

bool BinaryTree::checkBST(){
    if(tree != nullptr){
        cout<<"check Binary Search Tree\n";
        cout<<"Root: "<< tree->getData()<<endl;
        int indent = 0;
        if(checkBst_left(tree->getLeft(), MIN, tree->getData(), indent) && checkBst_right(tree->getRight(), tree->getData(), MAX, indent))
            return true;
        else return false;
    }
    return false;
}

bool BinaryTree::checkBst_left(Node* node, int min, int max, int indent){
    if(node != nullptr){
        for(int i = 0; i < indent; i++){cout<<"  ";}
        cout<<"go left to the "<<node->getData()<<"; ";
        if(node->getData() > min && node->getData() < max){
            if(min == MIN){
                cout<<node->getData()<<"<"<<max<<"  OK  "<<endl;
            }else cout<<min<<"<"<<node->getData()<<"<"<<max<<"  OK  "<<endl;
            if(node->getLeft()!= nullptr && node->getRight()!= nullptr) {
                for (int i = 0; i <= indent; i++) { cout << "  "; }
                cout << "Leaf: " << node->getData() << endl;
            }
            int old_max = max;
            max = node->getData();
            int old_min = min;
            min = node->getData();
            if(checkBst_left(node->getLeft(), old_min, max, indent+1) && checkBst_right(node->getRight(), min, old_max, indent+1)){
                return true;
            } else return false;
        } else{
            cout<<max<<"<"<<node->getData()<<" ERROR"<<endl;
            return false;
        }
    }
    return true;
}
bool BinaryTree::checkBst_right(Node* node, int min, int max, int indent){
    if(node != nullptr){
        for(int i = 0; i < indent; i++){cout<<"  ";}
        cout<<"go right to the "<<node->getData()<<"; ";
        if(node->getData() > min && node->getData() < max){
            if(max == MAX){
                cout<<min<<"<"<<node->getData()<<"  OK  "<<endl;
            }else cout<<min<<"<"<<node->getData()<<"<"<<max<<"  OK  "<<endl;
            if(node->getLeft()!= nullptr && node->getRight()!= nullptr) {
                for (int i = 0; i <= indent; i++) { cout << "  "; }
                cout << "Leaf: " << node->getData() << endl;
            }
            int old_max = max;
            max = node->getData();
            int old_min = min;
            min = node->getData();
            if(checkBst_left(node->getLeft(), old_min, max, indent+1) && checkBst_right(node->getRight(), min, old_max, indent+1)){
                return true;
            } else return false;
        } else{
            cout<<node->getData()<<"<"<<min<<" ERROR"<<endl;
            return false;
        }
    }
    return true;

}

bool BinaryTree::checkPiramid(){
    if(tree!= nullptr){
        cout<<"Check Piramid\n";
        cout<<"Root: "<< tree->getData()<<endl;
        int indent = 0;
        if(checkPiramid_leaf(tree->getLeft(), tree->getData(), indent) && checkPiramid_leaf(tree->getRight(), tree->getData(), indent)){
            return true;
        } else return false;
    }
    return false;
}

bool BinaryTree::checkPiramid_leaf(Node* node, int max, int indent){
    if(node != nullptr){
        for(int i = 0; i < indent; i++){cout<<"  ";}
        cout<<"go to the "<<node->getData()<<"; ";
        if(node->getData() <= max){
            cout<<node->getData()<<"<="<<max<<"  OK  "<<endl;
            if(node->getLeft()!= nullptr && node->getRight()!= nullptr) {
                for (int i = 0; i <= indent; i++) { cout << "  "; }
                cout << "Leaf: " << node->getData() << endl;
            }
            max = node->getData();
            if(checkPiramid_leaf(node->getLeft(), max, indent+1) && checkPiramid_leaf(node->getRight(), max, indent+1)) {
                return true;
            } else return false;
        } else {
            cout<<node->getData()<<">="<<max<<"  ERROR  "<<endl;
            return false;
        }
    }
    return true;
}
