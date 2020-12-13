#include "Tree.h"
#include "InOut.h"

int main (int argc, char** argv){
    string input = cuinput(argc, argv);
    if(input.empty()){
        cout<<"ERROR";
        return 0;
    }
    string copy = string(input);
    BinaryTree tree = BinaryTree(copy);
    if(!tree.isErr() && copy.empty()) {
        cout<<input<<endl;
        if (tree.checkBST()) {
            cout << "Tree is BST\n";
            if (argc > 1) {
                ofstream outfile(optarg, ios::app);
                outfile << "Tree is BST\n";
            }
        } else if (tree.checkPiramid()) {
            cout << "Tree is a piramid\n";
            if (argc > 1) {
                ofstream outfile(optarg, ios::app);
                outfile << "Tree is a piramid\n";
            }
        } else {
            cout << "Tree is not BST or Piramid\n";
            if (argc > 1) {
                ofstream outfile(optarg, ios::app);
                outfile << "Tree is not BST or Piramid\n";
            }
        }
    } else{
        cout<<"error\n"<<input<<" is not a Tree or correct tree\n";
    }
    return 0;
}
