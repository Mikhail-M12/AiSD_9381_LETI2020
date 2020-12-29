#include <iostream>
#include <time.h>
#include <fstream>
#include <conio.h>

class RBtree
{
	struct node
	{
		node* left, * right;
		int value;
		bool red;
	};
	node* tree_root;					
	int size;					
private:
	node* make_node(int value);	
	void del_node(node*);				
	void clear(node*);				
	node* rotate_right(node*);		
	node* rotate_left(node*);		
	void balance_insert(node**);	
	bool balance_remove_case1(node**);		
	bool balance_remove_case2(node**);
	bool insert(int, node**);			
	bool getmin(node**, node**);	
	bool remove(node**, int);			
	void print_tree(node*& ptr, int u);
public:
	RBtree();
	~RBtree();
	void clear();							
	int find(int);			
	void insert(int);		
	void remove(int);		
	void print();
	int getsize() { return size; }
};

RBtree::RBtree()
{
	tree_root = 0;
	size = 0;
}

RBtree::~RBtree()
{
	clear(tree_root);
}

RBtree::node* RBtree::make_node(int value)
{
	size++;
	node* n = new node;
	n->value = value;
	n->left = n->right = NULL;
	n->red = true;
	return n;
}

void RBtree::del_node(node* node)
{
	size--;
	delete node;
}

void RBtree::clear(node* node)
{
	if (!node) return;
	clear(node->left);
	clear(node->right);
	del_node(node);
}

RBtree::node* RBtree::rotate_left(node* n)
{
	node* right = n->right;
	node* rleft = right->left;
	right->left = n;
	n->right = rleft;
	return right;
}

RBtree::node* RBtree::rotate_right(node* n)
{
	node* left = n->left;
	node* lright = left->right;
	left->right = n;
	n->left = lright;
	return left;
}

void RBtree::balance_insert(node** root)
{
	node* left, * right, * lleft, * lright;
	node* node = *root;
	if (node->red) return;
	left = node->left;
	right = node->right;
	if (left && left->red)
	{
		lright = left->right;				
		if (lright && lright->red)
			left = node->left = rotate_left(left);
		lleft = left->left;
		if (lleft && lleft->red)
		{
			node->red = true;
			left->red = false;
			if (right && right->red)
			{	
				lleft->red = true;
				right->red = false;
				return;
			}
			*root = rotate_right(node);
			return;
		}
	}
	
	if (right && right->red)
	{
		lleft = right->left;				
		if (lleft && lleft->red)
			right = node->right = rotate_right(right);
		lright = right->right;
		if (lright && lright->red)
		{
			node->red = true;
			right->red = false;
			if (left && left->red)
			{	
				lright->red = true;
				left->red = false;
				return;
			}
			*root = rotate_left(node);
			return;
		}
	}
}

bool RBtree::balance_remove_case1(node** root)
{
	node* n = *root;
	node* left = n->left;
	node* right = n->right;
	if (right && left->red)
	{
		left->red = false; return false;
	}
	if (right && right->red)
	{ 
		n->red = true;
		right->red = false;
		n = *root = rotate_left(n);
		if (balance_remove_case1(&n->left)) n->left->red = false;
		return false;
	}
	unsigned int mask = 0;
	node* rleft = right->left;
	node* rright = right->right;
	if (rleft && rleft->red) mask |= 1;
	if (rright && rright->red) mask |= 2;
	switch (mask)
	{
	case 0:		
		right->red = true;
		return true;
	case 1:
	case 3:		
		right->red = true;
		rright->red = false;
		right = n->right = rotate_right(right);
		rright = right->right;
	case 2:		
		right->red = n->red;
		rright->red = n->red = false;
		*root = rotate_left(n);
	}
	return false;
}

bool RBtree::balance_remove_case2(node** root)
{
	node* n = *root;
	node* left = n->left;
	node* right = n->right;
	if (right && right->red) { right->red = false; return false; }
	if (left && left->red)
	{ 
		n->red = true;
		left->red = false;
		n = *root = rotate_right(n);
		if (balance_remove_case2(&n->right)) n->right->red = false;
		return false;
	}
	unsigned int mask = 0;
	node* lleft = left->left;
	node* lright = left->right;
	if (lleft && lleft->red) mask |= 1;
	if (lright && lright->red) mask |= 2;
	switch (mask)
	{
	case 0:	
		left->red = true;
		return true;
	case 2:
	case 3:		
		left->red = true;
		lright->red = false;
		left = n->left = rotate_left(left);
		lleft = left->left;
	case 1:		
		left->red = n->red;
		lleft->red = n->red = false;
		*root = rotate_right(n);
	}
	return false;
}

int RBtree::find(int value)
{
	node* n = tree_root;
	int i = 0;
	while (n)
	{
		if (n->value == value)
			i++;
		n = n->value > value ? n->left : n->right;
	}
	return i;
}

bool RBtree::insert(int value, node** root)
{
	node* n = *root;
	if (!n) *root = make_node(value);
	else
	{
		if (value == n->value) return true;
		if (insert(value, value < n->value ? &n->left : &n->right)) return true;
		balance_insert(root);
	}
	return false;
}

bool RBtree::getmin(node** root, node** res)
{
	node* node = *root;
	if (node->left)
	{
		if (getmin(&node->left, res)) return balance_remove_case1(root);
	}
	else
	{
		*root = node->right;
		*res = node;
		return !node->red;
	}
	return false;
}

bool RBtree::remove(node** root, int value)
{
	node* t, * node = *root;
	if (!node) return false;
	if (node->value < value)
	{
		if (remove(&node->right, value))	return balance_remove_case2(root);
	}
	else if (node->value > value)
	{
		if (remove(&node->left, value))	return balance_remove_case1(root);
	}
	else
	{
		bool res;
		if (!node->right)
		{
			*root = node->left;
			res = !node->red;
		}
		else
		{
			res = getmin(&node->right, root);
			t = *root;
			t->red = node->red;
			t->left = node->left;
			t->right = node->right;
			if (res) res = balance_remove_case2(root);
		}
		del_node(node);
		return res;
	}
	return 0;
}

void RBtree::insert(int value)
{
	insert(value, &tree_root);
	if (tree_root) tree_root->red = false;
}

void RBtree::remove(int value)
{
	remove(&tree_root, value);
}

void RBtree::clear()
{
	clear(tree_root);
	tree_root = 0;
}

void RBtree::print_tree(node*& ptr, int u)
{
	if (ptr == nullptr)
	{
		u++;
		for (int i = 0; i < u - 1; ++i) std::cout << "\t";
		std::cout << "NULL\n";
		return;
	}
	else
	{
		print_tree(ptr->right, ++u);
		for (int i = 0; i < u - 1; ++i) std::cout << "\t";
		std::cout << ptr->value << "(";
		if (ptr->red)
			std::cout << "red";
		else
			std::cout << "black";
		std::cout << ")\n";
		u--;
	}
	print_tree(ptr->left, ++u);
}

void RBtree::print()
{
	print_tree(tree_root, 0);
}

int main()
{
	int n = 1, c, j = 20;
	char cin[10], exit = 0;
	RBtree tree;
	setlocale(LC_ALL, "ru");

	std::cout << "Способ ввода из консоли 1, заполнить дерево случайными числами 2, ввести из файла 3\n";
	std::cin >> cin;

	while (exit != 27)
	{
		if (isdigit(*cin))
		{
			c = atoi(cin);
			if ((c != 1) && (c != 2) && (c != 3))
			{
				std::cout << "нужно ввести 1 или 2 или 3, чтобы выйти из программы нужно нажать esc\n";
				exit = _getch();
				if (exit == 27)
					break;
			}
			else
				break;
			std::cout << "Способ ввода из консоли 1, Заполнить дерево случайными числами 2\n";
			std::cin >> cin;
			continue;
		}
		else
		{
			std::cout << "Нужно ввести число, попробуйте еще\n";
			std::cin >> cin;
		}
	}

	if (exit != 27)
		while (1)
		{
			if (c == 2)
			{
				std::cout << "сколько узлов создать?\n";
				std::cin >> cin;
				if (isdigit(*cin))
				{
					j = atoi(cin);
					break;
				}
				else
					std::cout << "Нужно ввести число, попробуйте еще\n";
			}
			else
				break;
		}

	std::ifstream lin("lin.txt");
	if (c == 3)
		if (!lin.is_open())
		{
			std::cout << "Файл не открыт";
			return -1;
		}

	srand(time(0));
	while (n)
	{
		switch (c)
		{
		case 1:
			std::cin >> cin;
			if (isdigit(*cin))
			{
				n = atoi(cin);
			}
			else
			{
				std::cout << "Нужно ввести число, попробуйте еще\n";
				continue;
			}
			while (n != NULL)
			{
				tree.insert(n);
				std::cin >> cin;
				if (isdigit(*cin))
				{
					n = atoi(cin);
				}
				else
				{
					std::cout << "Нужно ввести число, попробуйте еще\n";
					continue;
				}
			}
			break;
		case 2:
			while(tree.getsize() < j)
			{
				n = rand() % j + rand() % j;
				tree.insert(n);
			}
			n = 0;
			break;
		case 3:
			while (!lin.eof())
			{
				lin >> n;
				tree.insert(n);
			}
			
		default:
			n = 0;
			break;
		}
	}
	n = 1;
	
	if (exit != 27)
	{
		
		while (n)
		{
			tree.print();
			std::cout << "Вставить: \n";
			std::cin >> cin;
			system("cls");
			if (isdigit(*cin))
			{
				n = atoi(cin);
			}
			else
			{
				std::cout << "Нужно ввести число, попробуйте еще\n";
				continue;
			}
			if (n == 0)
			{
				std::cout << "Закончить или ввести 0?\n Y - выйти N = ввести\n";
				while (exit != 'y' && exit != 'n')
					exit = _getch();
			}

			tree.insert(n);
			
			if (exit == 'n')
				n = 1;
			exit = 0;
		}
	}

	lin.close();

	getchar();
	return 0;
}