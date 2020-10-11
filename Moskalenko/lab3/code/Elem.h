#ifndef LAB3_4_ELEM_H
#define LAB3_4_ELEM_H
#include <iostream>
using namespace std;

class Elem;
typedef Elem* tree;
typedef char T;

class Elem {
        tree left;
        tree right;
        T data;
    public:
        Elem():left(nullptr), right(nullptr), data('\0') {};

        tree getLeft() {
            return left;               //возвращает левое поддерево
        }

        void setLeft(tree l) {
            left = l;                   //устанавливает левое поддерево
        }

        void setRight(tree r) {         //устанавливает правое поддерево
            right = r;
        }

        tree getRight() {               //возвращает правое поддерево
            return right;
        }

        T getData() const {             //возвращает значение элемента
            return data;
        }

        void setData(T t) {             //устанавливает значение элемента
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

