#ifndef LAB3_4_ELEM_H
#define LAB3_4_ELEM_H
#include <iostream>
using namespace std;

class Elem;
typedef Elem* tree;
typedef char T;
//template <typename T>

class Elem {
        tree left;
        tree right;
        T data;
    public:
        Elem():left(nullptr), right(nullptr), data('\0') {};

        tree getLeft() {
            return left;
        }

        void setLeft(tree l) {
            left = l;
        }

        void setRight(tree r) {
            right = r;
        }

        tree getRight() {
            return right;
        }

        T getData() const {
            return data;
        }

        void setData(T t) {
            data = t;
        }

};

void recTreePrint(tree node) {
    if (!node) {
        cout << '/';
        return;
    }
    cout << node->getData();
    recTreePrint(node->getLeft());      //печать левого
    recTreePrint(node->getRight());     //печать правого
}


#endif //LAB3_4_ELEM_H

