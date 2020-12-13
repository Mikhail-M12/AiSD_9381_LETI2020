#include "tree.h"

BinaryTree::BinaryTree(std::vector<int> &arr, string& str) {
    str += "Your input: ";
    for(int i : arr){
        str+= std::to_string(i) + ' ';
    }
    str+= '\n';
    str+="Sorting array\n";
    sort(arr.begin(), arr.end());
    for(int i : arr){
        str+= std::to_string(i) + ' ';
    }
    str+= '\n';
    int countUnique = 1;
    int pos = 0;
    for(int i = 0; i < arr.size()-1; i++){
        if(arr[i]<arr[i+1]){
            countUnique++;
        }
    }
    str+="Making tree\n";
    maxDepth = ceil(log2(countUnique+1));
    tree = makeTree(countUnique, arr, pos, 0, str);
}

Node * BinaryTree::getTree() {
    return tree;
}
/*Функция для созания дерева из массива.*/
Node * BinaryTree::makeTree(int n, std::vector<int>& arr, int& pos, int indent, string& str) {
    if (n == 0) {
        for(int i = 0; i < indent; i++){str+="  ";}
        str+="()\n";
        return nullptr;
    }
    for(int i = 0; i < indent; i++){str+="  ";}
    str+="amount of elements: "+ std::to_string(n)+'\n';
    Node *buf = new Node();
    int nL, nR;
    nL = n / 2;
    for(int i = 0; i < indent; i++){str+="  ";}
    str+= std::to_string(nL) + " Elements goes to the left\n";
    nR = n - nL - 1;
    for(int i = 0; i < indent; i++){str+="  ";}
    str+= std::to_string(nR) + " Elements goes to the right\n";
    for(int i = 0; i < indent; i++){str+="  ";}
    str+="Left\n";
    buf->setLeft(makeTree(nL, arr, pos, indent+1, str));
    for(int i = 0; i < indent; i++){str+="  ";}
    str += std::to_string(arr[pos]) + " is a root\n";
    buf->setData(arr[pos]);
    buf->incAmount();
    while (arr[pos] == arr[pos + 1]) {
        pos++;
        buf->incAmount();
    }
    pos++;
    for(int i = 0; i < indent; i++){str+="  ";}
    str+="Right\n";
    buf->setRight(makeTree(nR, arr, pos, indent+1, str));
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

void BinaryTree::findElem(int e, string& str) {
    str+="find element " + std::to_string(e) + '\n';
    find(tree, e, str);
}

/*Рекурсиваня функция для поиска элемента в дереве.
 * Если Элемент меньше узла, то она вызывается для левого поддерева. Если больше, то для правого поддерева
Поиск завершается, когда указатель на дерево равен nullptr или корень дерева равен элементу.*/
bool BinaryTree::find(Node *node, int x, string& str) {
    if(node == nullptr) {
        str+="\nNo element "+ std::to_string(x) + " in bst\n";
        return false;
    }
    if(x == node->getData()){
        str+="\nElem "+ std::to_string(x)+" appears in tree " + std::to_string(node->getAmount())+" times\n";
        return true;
    }else if(x < node->getData()){
        str+= std::to_string(x)+" < "+ std::to_string(node->getData())+" Go to the left\n";
        if(find(node->getLeft(), x, str))
            return true;
    } else if(x > node->getData()) {
        str+= std::to_string(x)+" > "+ std::to_string(node->getData()) + " Go to the right\n";
        if(find(node->getRight(), x, str))
            return true;
    }
    return false;
}

/*функция для сохранения дерева не содержащего нужный элемент в массив*/
void BinaryTree::treeToArrHelp(Node *node, std:: vector<int>& arr, string& str) {
    if(node != nullptr){
        treeToArrHelp(node->getLeft(), arr, str);
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr, str);
    }
}

/*функция для сохранения дерева в массив при добавлении элемента*/
void BinaryTree::treeToArrAdd(Node *node, std::vector<int> &arr, int e, string& str) {
    if(node == nullptr){
        arr.push_back(e);
        str+="New elem "+ std::to_string(e)+" goes to array\n";

    } else if(e < node->getData()){
        treeToArrAdd(node->getLeft(), arr, e, str);
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr, str);

    } else if(e > node->getData()){
        treeToArrHelp(node->getLeft(), arr, str);
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrAdd(node->getRight(), arr, e, str);

    } else if(e == node->getData()){
        treeToArrHelp(node->getLeft(), arr, str);
        node->incAmount();
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr, str);
    }
}

/*Функция для сохранения дерева в массив при удалении элемента*/
void BinaryTree::treeToArrDelete(Node *node, std::vector<int> &arr, int e, string& str) {
    if(node == nullptr){
        return;

    } else if(e < node->getData()){
        treeToArrDelete(node->getLeft(), arr, e, str);
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrHelp(node->getRight(), arr, str);

    } else if(e > node->getData()){
        treeToArrHelp(node->getLeft(), arr, str);
        str+= std::to_string(node->getData())+" goes to array\n";
        for(int i = 0; i<node->getAmount(); i++){
            arr.push_back(node->getData());
        }
        treeToArrDelete(node->getRight(), arr, e, str);

    } else if(e == node->getData()){
        treeToArrHelp(node->getLeft(), arr, str);

        treeToArrHelp(node->getRight(), arr, str);
    }
}

/*Удаление элемента и перестройка дерева*/
void BinaryTree::deleteElem(int e, string& str) {
    str+="Delete elem "+ std::to_string(e)+'\n';
    str+="making array\n";
    std::vector<int> arr;
    treeToArrDelete(tree, arr, e, str);
    destroy(tree);
    int countUnique = 1;
    int pos = 0;
    for(int i = 0; i < arr.size()-1; i++){
        if(arr[i]<arr[i+1]){
            countUnique++;
        }
    }
    maxDepth = ceil(log2(countUnique+1));
    str+="rebuild tree\n";
    tree = makeTree(countUnique, arr, pos, 0, str);

}

/*Добавление элемента и престройка дерева*/
void BinaryTree::addElem(int e, string& str) {
    str+="Add elem "+ std::to_string(e)+'\n';
    std::vector<int> arr;
    str+="making array\n";
    treeToArrAdd(tree, arr, e, str);
    destroy(tree);
    int countUnique = 1;
    int pos = 0;
    for(int i = 0; i < arr.size()-1; i++){
        if(arr[i]<arr[i+1]){
            countUnique++;
        }
    }
    maxDepth = ceil(log2(countUnique+1));
    str+="rebuild tree\n";
    tree = makeTree(countUnique, arr, pos, 0, str);
}

int BinaryTree::getMaxDepth(){
    return maxDepth;
}
