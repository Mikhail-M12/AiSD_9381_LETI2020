//
// Created by xtkcb on 29-Oct-20.
//

#include "Test.h"
#include "../lab3.h"

void Test::test1() {
    BT bintree;
    string s = "8 2 9 4 1 7 5";
    cout << s << '\n';
    bintree.read_BT(s);
    bintree.print();
    bintree.print_leaf();
    bintree.count_edges(3);
    cout << "--------------------------------------------------\n\n";
}

void Test::test2() {
    BT bintree;
    string s = "a b c d f";
    cout << s << '\n';
    bintree.read_BT(s);
    bintree.print();
    bintree.print_leaf();
    bintree.count_edges(3);
    cout << "--------------------------------------------------\n\n";
}
void Test::test3() {
    BT bintree;
    string s = "6 t 2 9 f e 1";
    cout << s << '\n';
    bintree.read_BT(s);
    bintree.print();
    bintree.print_leaf();
    bintree.count_edges(2);
    cout << "--------------------------------------------------\n\n";
}
void Test::test4() {
    BT bintree;
    string s = "a";
    cout << s << '\n';
    bintree.read_BT(s);
    bintree.print();
    bintree.print_leaf();
    bintree.count_edges(1);
    cout << "--------------------------------------------------\n\n";
}

void Test::runall() {
    test1();
    test2();
    test3();
    test4();
}
