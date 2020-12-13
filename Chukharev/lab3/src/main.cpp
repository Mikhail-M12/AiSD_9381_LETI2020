#include <iostream>
#include <fstream>
#include <stack>

class BinaryNode;
class BinaryTree;

using pBinaryNode = BinaryNode*;
using pBinaryTree = BinaryTree*;

// Node of the binary tree.
class BinaryNode {
    pBinaryNode left_;
    pBinaryNode right_;
    char data_;

public:
    BinaryNode() : left_(nullptr), right_(nullptr), data_('\0') {}

    explicit BinaryNode(char symbol) : BinaryNode() {
        data_ = symbol;
    };

    // Setters
    void setLeft(pBinaryNode left) {
        left_ = left;
    }

    void setRight(pBinaryNode right) {
        right_ = right;
    }

    // Getters
    pBinaryNode getRight() {
        return right_;
    }

    char getData() {
        return data_;
    }

    pBinaryNode getLeft() {
        return left_;
    }
};

// Binary tree, node is a BinaryNode
class BinaryTree {
    pBinaryNode root_;
    std::string stringTree_; // string representation of the tree

public:
    BinaryTree() : root_(nullptr) {};

    ~BinaryTree() {
        deleteTree(root_);
    }

    // Starts recursion read of the tree
    void initTree(std::string &input) {
        if (input.empty() || input == "\n")
            return;

        root_ = new BinaryNode();
        root_ = recTreeInit(input);
        treeToString(getRoot(), stringTree_, 1); // get the string representation
    }

    friend std::ostream& operator<<(std::ostream &stream, const BinaryTree &tree);

    // Getters
    pBinaryNode getRoot() {
        return root_;
    }

private:
    // Get the string representation of the tree
    void treeToString(pBinaryNode node, std::string &string, int level) {
        if (!node) {
            string += '/';
            return;
        }

        string += node->getData();
        treeToString(node->getLeft(), string, level + 1);
        treeToString(node->getRight(), string, level + 1);
    }

    // Recursion tree memory free
    void deleteTree(pBinaryNode node) {
        if (!node)
            return;

        deleteTree(node->getLeft()); // Go to left
        deleteTree(node->getRight()); // Go to right
        delete node;
    }

    // Recursion read the tree
    pBinaryNode recTreeInit(std::string &input) {
        if (input.empty())
            return nullptr;

        char symbol = input[0];
        input = input.substr(1);

        if (symbol == '/') {
            return nullptr;
        } else {
            auto buf = new BinaryNode(symbol);
            buf->setLeft(recTreeInit(input));
            buf->setRight(recTreeInit(input));
            return buf;
        }
    }
};

void treeToString(pBinaryNode node, std::string string) {
    if (!node)
        return;

    if (!node->getLeft() && !node->getRight()) { // the end of the branch
        std::cout << string << node->getData() << '\n';
        return;
    }

    std::string temp = string;
    if (node->getRight()) { // go to the right
        temp += '\t';
        treeToString(node->getRight(), temp);
    }

    std::cout << string << node->getData() << '\n';
    if (node->getLeft()) { // go to the left
        string += '\t';
        treeToString(node->getLeft(), string);
    }
}

std::ostream& operator<<(std::ostream &stream, const BinaryTree &tree) {
    return stream << tree.stringTree_;
}

void outputHelp() {
    std::cout << "Choose one of the following options: " << '\n' <<
              "1. Read from the keyboard" << '\n' <<
              "2. Read from the file" << '\n' <<
              "3. Exit" << '\n' <<
              "Your choice: ";
}

int getAction() {
    int action;
    outputHelp();
    std::cin >> action;
    return action;
}

void bfSearch(pBinaryNode node) { // breadth-first traversal
    if (!node)
        return;

    std::stack <pBinaryNode> nodes;
    nodes.push(node);

    while (!nodes.empty()) {
        auto temp = nodes.top();
        nodes.pop();

        if (temp) {
            std::cout << temp->getData() << ' ';
            nodes.push(temp->getLeft());
            nodes.push(temp->getRight());
        }
    }
}

void execConvert(pBinaryTree tree) {
    std::cout << "Your input: ";
    std::cout << *tree << '\n';

    std::cout << "The tree is: " << '\n';
    treeToString(tree->getRoot(), "");

    std::cout << '\n';
    std::cout << "The forest is: " << '\n' << '\n';

    std::cout << "Left: " << '\n';
    treeToString(tree->getRoot()->getLeft(), "");

    std::cout << "Horizontal: " << '\n';
    bfSearch(tree->getRoot()->getLeft());
    std::cout << '\n' << '\n';

    std::cout << "Right: " << '\n';
    treeToString(tree->getRoot()->getRight(), "");

    std::cout << "Horizontal: " << '\n';
    bfSearch(tree->getRoot()->getRight());
    std::cout << '\n' << '\n';
}

int main() {
    int action;

    std::ifstream file;
    std::string filePath;

    std::string string;

    while ((action = getAction()) != 3) {
        auto tree = new BinaryTree();

        switch (action) {
            case 1:
                std::cout << "Input your tree: ";
                std::cin >> string;
                break;
            case 2:
                std::cout << "Input the path to your file: ";
                std::cin >> filePath;

                file.open(filePath);
                if (!file.is_open()) {
                    std::cout << "Wrong file" << '\n';
                    continue;
                }

                file >> string;
                file.close();
                break;
            default:
                std::cout << "Wrong string. Try again" << '\n';
                return 0;
        }

        tree->initTree(string);

        if (!tree->getRoot()) {
            std::cout << "That's an empty tree" << "\n\n";
            continue;
        }

        execConvert(tree);
        delete tree;
    }

    return 0;
}