#pragma once
class node
{
public:
	int num;
	int weight;
	struct node* left;
	struct node* right;
};

void push(int a, node** t);

unsigned int total(node* t);

void printCor(node* t);

void printTree(node* t, int u);

void console(node** cor);

void file(node** cor);

void deleteCor(node* tree);