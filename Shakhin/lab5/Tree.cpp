#include "Tree.h"

BinaryTree::BinaryTree(std::vector<int> &arr) {
    cout<<"Your input: ";
    for(int i : arr){
        cout<<i<<' ';
    }
    cout<<endl;
    cout<<"Sorting array"<<endl;
    sort(arr.begin(), arr.end());
    for(int i : arr){
        cout<<i<<' ';
    }
    cout<<endl;
    int countUnique = 1;
    int pos = 0;
    for(int i = 0; i < arr.size()-1; i++){
        if(arr[i]<arr[i+1]){
            countUnique++;
        }
    }
    cout<<"Making tree"<<endl;
    tree = makeTree(countUnique, arr, pos, 0);
}

Node * BinaryTree::getTree() {
    return tree;
}

Node * BinaryTree::makeTree(int n, std::vector<int>& arr, int& pos, int indent) {
    if (n == 0) {
        for(int i = 0; i < indent; i++){cout<<"  ";}
        cout<<"()"<<endl;
        return nullptr;
    }
    for(int i = 0; i < indent; i++){cout<<"  ";}
    cout<<"amount of elements: "<< n<<endl;
    Node *buf = new Node();
    int nL, nR;
    nL = n / 2;
    for(int i = 0; i < indent; i++){cout<<"  ";}
    cout<<nL<<" Elements goes to the left"<<endl;
    nR = n - nL - 1;
    for(int i = 0; i < indent; i++){cout<<"  ";}
    cout<<nR<<" Elements goes to the right"<<endl;
    for(int i = 0; i < indent+1; i++){cout<<"  ";}
    cout<<"Left"<<endl;
    buf->setLeft(makeTree(nL, arr, pos, indent+1));
    for(int i = 0; i < indent; i++){cout<<"  ";}
    cout<<arr[pos]<<" is a root"<<endl;
    buf->setData(arr[pos]);
    buf->incAmount();
    while (arr[pos] == arr[pos + 1]) {
        pos++;
        buf->incAmount();
    }
    pos++;
    for(int i = 0; i < indent+1; i++){cout<<"  ";}
    cout<<"Right"<<endl;
    buf->setRight(makeTree(nR, arr, pos, indent+1));
    return buf;
}

void BinaryTree::printTree(Node* node) {
    if(node == nullptr)
        return;
    cout<<node->getData();
    cout<<'(';
    printTree(node->getLeft());
    cout<<')';
    cout<<'(';
    printTree(node->getRight());
    cout<<')';
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
BinaryTree::~BinaryTree() {
    destroy(tree);
}

void BinaryTree::findElem(int e) {
    cout<<"find element "<< e<<endl;
    find(tree, e);
}
bool BinaryTree::find(Node *node, int x) {
    if(node == nullptr) {
        cout<<"\nNo element "<<x<<" in bst"<<endl;
        return false;
    }
    if(x == node->getData()){
        cout<<"\nElem "<<x<<" appears in tree "<<node->getAmount()<<" times"<<endl;
        return true;
    }else if(x < node->getData()){
        cout<<x<<" < "<<node->getData()<<" Go to the left"<<endl;
        if(find(node->getLeft(), x))
            return true;
    } else if(x > node->getData()) {
        cout<<x<<" > "<<node->getData()<<" Go to the right"<<endl;
        if(find(node->getRight(), x))
            return true;
    }
    return false;
}

void BinaryTree::treeToArrHelp(Node *node, std:: vector<int>& arr) {
    if(node != nullptr){
        treeToArrHelp(node->getLeft(), arr);
        cout<<node->getData()<<" goes to array"<<endl;
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr);
    }
}

void BinaryTree::treeToArr(Node *node, std::vector<int> &arr, int e) {
    if(node == nullptr){
        arr.push_back(e);
        cout<<"New elem "<<e<<" goes to array"<<endl;

    } else if(e < node->getData()){
        treeToArr(node->getLeft(), arr, e);
        cout<<node->getData()<<" goes to array"<<endl;
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr);

    } else if(e > node->getData()){
        treeToArrHelp(node->getLeft(), arr);
        cout<<node->getData()<<" goes to array"<<endl;
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArr(node->getRight(), arr, e);

    } else if(e == node->getData()){
        treeToArrHelp(node->getLeft(), arr);
        node->incAmount();
        cout<<node->getData()<<" goes to array"<<endl;
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr);

    }
}

void BinaryTree::addElem(int e) {
    cout<<"Add elem "<< e<<endl;
    cout<<"rebuild tree"<<endl;
    std::vector<int> arr;
    cout<<"making array"<<endl;
    treeToArr(tree, arr, e);
    destroy(tree);
    int countUnique = 1;
    int pos = 0;
    for(int i = 0; i < arr.size()-1; i++){
        if(arr[i]<arr[i+1]){
            countUnique++;
        }
    }
    tree = makeTree(countUnique, arr, pos, 0);
}

