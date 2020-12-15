#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class AVL_Tree {
private:
	int height;
	int key;
	AVL_Tree* left;
	AVL_Tree* right;
public:
	void destroy();
	AVL_Tree(int key);
	bool find_key(int k);
	void print_tree(ostream* stream, int depth = 0);
	int get_height();
	int bfactor();
	void fixheight();
	AVL_Tree* rotateright(ostream* stream = nullptr);
	AVL_Tree* rotateleft(ostream* stream = nullptr);
	AVL_Tree* balance(ostream* stream = nullptr);
	AVL_Tree* insert(int k, ostream* stream = nullptr);
	AVL_Tree* findmin();
	AVL_Tree* removemin();
	AVL_Tree* remove(int k, ostream* stream = nullptr);
};