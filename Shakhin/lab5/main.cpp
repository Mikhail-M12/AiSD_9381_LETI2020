#include <iostream>
#include "structs.h"
#include "InOut.h"
#include "Tree.h"
#include <cmath>

int main() {
    string choice;
    cout<<"Choose console or file:\n 1 - Console\n 2 - File\nYour choice: ";
    getline(cin, choice);
    int ch = 1;
    switch (choice[0]) {
        case '1':
            ch = 1;
            break;
        case '2':
            ch = 2;
            break;
        default:
            cout<<"not correct\n";
            return 1;
            break;
    }
    std::vector<int> arr;
    if(makeArr(arr, ch))
        return 1;
    BinaryTree* tree = new BinaryTree(arr);
    int c = 0;
    while (c!=5){
        cout<<"\n-----------------------------------\n1 - Find Element\n2 - Add Element\n3 - Print tree\n4 - Delete Element\n5 - Exit\nYour choice ";
        cin>>c;
        int elem;
        switch (c) {
            case 1:
                cout<<"Enter element: ";
                cin>>elem;
                tree->findElem(elem);
                break;
            case 2:
                cout<<"Enter element: ";
                cin>>elem;
                tree->addElem(elem);
                break;
            case 3:
                tree->printTree(tree->getTree());
                break;
            case 4:
                cout<<"Enter element: ";
                cin>>elem;
                tree->deleteElem(elem);
                break;
            case 5:
                cout<<"end of program"<<endl;
                break;
        }
    }
    delete tree;
    return 0;
}
