#include <iostream>
#include <fstream>

using namespace std;

// Node of the binary tree.
class TreeNode {
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    char data = '\0';
    int level = 1;

public:
    TreeNode() = default;

    // Constructor with data
    explicit TreeNode(char symbol) : data(symbol) {};

    // Return the left node
    TreeNode* getLeft() {
        return left;
    }

    // Set the left node
    void setLeft(TreeNode *l) {
        left = l;
    }

    // Set the right node
    void setRight(TreeNode *r) {
        right = r;
    }

    // Return the right node
    TreeNode* getRight() {
        return right;
    }

    // Return the data
    char getData() {
        return data;
    }

    // Return the level
    int getLevel() {
        return level;
    }

    // Set the level
    void setLevel(int l) {
        level = l;
    }
};


// Class of the binary tree. Based on TreeNode
class BinaryTree {
    TreeNode *root = nullptr;
    int readIndex = 0;
    int level = 1;

public:
    BinaryTree() : root(nullptr) {};

    ~BinaryTree() {
        deleteTree(root);
    }

    // Start recursion init of the tree
    void stringToTree(std::string input) {
        if (input.empty() || input == "\n") // Check for incorrect string
            return;

        root = new TreeNode();
        std::cout << "Start parsing the string: " << '\n';
        root = recTreeInit(std::move(input));
    }

    // Start recursion print the tree
    void print() {
        recTreePrint(root);
    }

    // Return the root
    TreeNode* getRoot() {
        return root;
    }

private:
    // Recursion tree memory free
    void deleteTree(TreeNode *node) {
        if (!node)
            return;

        deleteTree(node->getLeft()); // Go to left
        deleteTree(node->getRight()); // Go to right
        delete node;
    }

    // Recursion output the tree
    void recTreePrint(TreeNode *node) {
        if (!node) {
            std::cout << '/';
            return;
        }

        std::cout << node->getData() << '(' << node->getLevel() << ')';
        recTreePrint(node->getLeft()); // Go to left
        recTreePrint(node->getRight()); // Go to right
    }

    // Recursion read the tree
    TreeNode* recTreeInit(std::string input) {
        if (input.length() <= readIndex)
            return nullptr;
        std::cout << "Start recTreeInit" << '\n';
        char symbol = input[readIndex];
        readIndex++;
        std::cout << "Working with the symbol: " << symbol << " and level: " << level << '\n';

        if (symbol == '/') {
            std::cout << "It's an empty node. Going up in the recursion" << '\n';
            level--;
            return nullptr;
        } else {
            auto buf = new TreeNode(symbol);
            buf->setLevel(level);
            level++;
            std::cout << "Go to the left. End recTreeInit" << '\n';
            buf->setLeft(recTreeInit(input));
            level++;
            std::cout << "Go to the right. End recTreeInit" << '\n';
            buf->setRight(recTreeInit(input));
            level--;
            std::cout << "Going up in the recursion. End recTreeInit" << '\n';
            return buf;
        }
    }
};

// Queue for the tree
class TreeQueue {
    TreeNode** data = nullptr;
    int currElem = 0;

public:
    TreeQueue() = default;;

    // Reallocate the array and adds one element
    void extendMemory() {
        auto **buffer = new TreeNode*[currElem + 1];

        for (int i = 0; i < currElem; i++)
            buffer[i] = data[i];

        delete [] data;
        data = buffer;
    }

    // Start reallocate
    void add(TreeNode* value) {
        extendMemory();
        data[currElem++] = value;
    }

    // Delete the top
    TreeNode* pop() {
        TreeNode *elem = data[0];

        for (int i = 1; i < currElem + 1; i++) // Move elements in the array
            data[i - 1] = data[i];

        currElem--;
        return elem;
    }

    // Return top
    TreeNode* top() {
        return data[0];
    }

    // Return size
    int getSize() {
        return currElem;
    }
};

// The main algorithm based on queue.
bool stepByStepAlg(int& lev, string &out, TreeQueue *queue, bool flag) {
    for (;;) {
        TreeNode *current = queue->top();
        cout <<  "Current top is: " << current->getData() << '\n';
        queue->pop();

        if (lev != current->getLevel()) {
            lev++;
            if (lev == 1) {
                out += "Level: ";
                out += std::to_string(lev);
                out += '\n';
            } else {
                out += "\nLevel: ";
                out += std::to_string(lev);
                out += '\n';
            }
        }

        out += current->getData();
        out += '\t';

        if (!current->getLeft() && !current->getRight() && !queue->getSize())
            return true;

        if (current->getLeft()) {
            cout << "Add " << current->getLeft()->getData() << " to the queue" << '\n';
            queue->add(current->getLeft());
        }

        if (current->getRight()) {
            cout << "Add " << current->getRight()->getData() << " to the queue" << '\n';
            queue->add(current->getRight());
        }

        if (flag)
            return false;
    }
}

int getAction() {
    int action = 0;

    cout << "Choose one of the following options: " << '\n' <<
         "1. Read from the keyboard" << '\n' <<
         "2. Read from the file" << '\n' <<
         "3. Exit" << '\n' <<
         "Your choice: ";
    cin >> action;

    return action;
}

int main() {
    int action;
    string input;
    ifstream file;
    string fileName;

    while((action = getAction()) != 3) {
        string out;
        int level = 0;
        auto *tree = new BinaryTree();
        auto *treeQueue = new TreeQueue();

        switch(action) {
            case 1:
                cout << "Input your list: ";
                cin >> input;
                break;
            case 2:
                cout << "Input the path to your file: ";
                cin >> fileName;
                file.open(fileName);

                if (!file.is_open()) {
                    cout << "Wrong file" << '\n';
                    continue;
                }

                file >> input;
                file.close();
                break;
            default:
                cout << "Wrong input. Try again" << '\n';
                return 0;
        }

        tree->stringToTree(input);

        if (!tree->getRoot()) {
            cout << "That's an empty tree" << "\n\n";
            continue;
        }

        treeQueue->add(tree->getRoot());
        cout << "Your list is: ";
        tree->print();
        cout << '\n';
        cout << "The result is: " << '\n';
        stepByStepAlg(level, out, treeQueue, false);
        cout << out;
        cout << "\n\n";

        delete tree;
        delete treeQueue;
    }

    cout << "Exiting the program" << '\n';
    return 0;
}
