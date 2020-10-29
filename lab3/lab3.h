//
// Created by xtkcb on 29-Oct-20.
//

#ifndef LAB3_LAB3_H
#define LAB3_LAB3_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>


#define equal_Z2(i, k) !((i&1)^(k&1))


typedef char Data;
const int MaxNodes = 5000;
using namespace std;

class Node {
public:
    Data data = {};
    int count = -1;
};

class BT {
public:
    int mx_dep = 0;

    Node a[MaxNodes];

    void insert(Node x);

    int find(Node x);

    void read_str(string &s);

    void read_BT(string s);

    void print();

    void print_leaf();

    void count_edges(int dep);

private:
    int count_nodes = 0;
};

#endif //LAB3_LAB3_H
