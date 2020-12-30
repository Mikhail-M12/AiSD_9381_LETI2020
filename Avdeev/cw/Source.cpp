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
		int num;
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
	void balance_insert_demo(node**);
	bool balance_remove_case1(node**);
	bool balance_remove_case2(node**);
	bool insert(int, node**);
	bool insert_demo(int, node**);
	bool getmin(node**, node**);
	bool remove(node**, int);
	void print_tree(node*& ptr, int u);
public:
	RBtree();
	~RBtree();
	void clear();
	int find(int);
	int findlog(int);
	void insert(int);
	void insert_demo(int);
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
	n->num = size;
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
		{
			left = node->left = rotate_left(left);
		}
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
		{
			right = node->right = rotate_right(right);
		}
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

void RBtree::balance_insert_demo(node** root)
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
		{
			system("cls");
			this->print();
			std::cout << "Обнаружена ситуация! Находится в узле " << (*root)->num << "\n";
			_getch();
			left = node->left = rotate_left(left);
			system("cls");
			this->print();
			_getch();
		}
		lleft = left->left;
		if (lleft && lleft->red)
		{
			system("cls");
			this->print();
			std::cout << "Перекрашивает узлы: " << node->num << " и " << left->num << "\n";
			_getch();
			node->red = true;
			system("cls");
			this->print();
			std::cout << "узел " << node->num << " теперь красный";
			_getch();
			left->red = false;
			system("cls");
			this->print();
			std::cout << "узел " << left->num << " теперь черный\n";
			_getch();
			if (right && right->red)
			{
				std::cout << "узел " << right->num << " красный, значит нужно покрасить его в черный, а узел " << lleft->num << " в красный\n";
				_getch();
				lleft->red = true;
				right->red = false;
				return;
			}
			std::cout << "Осуществляет поворот вправо относительно узла " << node->num << "\n";
			_getch();
			*root = rotate_right(node);
			system("cls");
			this->print();
			_getch();
			return;
		}
	}



	if (right && right->red)
	{
		lleft = right->left;
		if (lleft && lleft->red)
		{
			system("cls");
			this->print();
			std::cout << "Обнаружена ситуация! Находится в узле " << (*root)->num << "\n";
			_getch();
			right = node->right = rotate_right(right);
			system("cls");
			this->print();
			_getch();
		}
		lright = right->right;
		if (lright && lright->red)
		{
			system("cls");
			this->print();
			std::cout << "Перекрашивает узлы: " << node->num << " и " << right->num << "\n";
			_getch();
			node->red = true;
			system("cls");
			this->print();
			std::cout << "узел " << node->num << " теперь красный ";
			_getch();
			right->red = false;
			system("cls");
			this->print();
			std::cout << "узел " << right->num << " теперь черный\n";
			_getch();
			if (left && left->red)
			{
				std::cout << "узел " << left->num << " красный, значит нужно покрасить его в черный, а узел " << lright->num << " в красный\n";
				_getch();
				lright->red = true;
				left->red = false;
				return;
			}
			std::cout << "Осуществляет поворот влево относительно узла " << node->num << "\n";
			_getch();
			*root = rotate_left(node);
			system("cls");
			this->print();
			_getch();
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

int RBtree::findlog(int value)
{
	int f = 0;

	node* n = tree_root;
	int i = 0;
	while (n)
	{
		std::cout << ++f << " -й запуск цикла\n";
		std::cout << "находится в узле " << n->num << "\n";
		if (n->value == value)
		{
			std::cout << "Элемента найден\n";
			i++;
		}
		if (n->value > value)
		{
			std::cout << "Искомый элемент меньше, чем содержимое узла поэтому идет в ";
			std::cout << "левый узел\n";
			n = n->left;
		}
		else
		{
			std::cout << "Искомый элемент больше, чем содержимое узла поэтому идет в ";
			std::cout << "правый узел\n";
			n = n->right;
		}
	}
	return i;
}

bool RBtree::insert(int value, node** root)
{
	node* n = *root;
	if (!n) *root = make_node(value);
	else
	{
	//	if (value == n->value) return true;
		if (insert(value, value <= n->value ? &n->left : &n->right)) return true;
		balance_insert(root);
	}
	return false;
}

bool RBtree::insert_demo(int value, node** root)
{
	node* n = *root;
	if (!n) *root = make_node(value);
	else
	{
	//	if (value == n->value) return true;
		if (insert_demo(value, value <= n->value ? &n->left : &n->right)) return true;
		balance_insert_demo(root);
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

void RBtree::insert_demo(int value)
{
	insert_demo(value, &tree_root);
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
		std::cout << ptr->num << "(" << ptr->value << ")(";
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

int withoutlog(RBtree& tree)
{
	char cin[10], exit = 0;
	int n = 1;
	while (n)
	{
		system("cls");
		tree.print();
		std::cout << "Найти: \n";
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
			std::cout << "Закончить или найти 0?\n y - выйти n = найти\n";
			while (exit != 'y' && exit != 'n')
				exit = _getch();
		}
		if (exit != 'y')
		{
			tree.print();
			if (!tree.find(n))
			{
				std::cout << "Числа в дереве нет, ввести его?\n y - да n - нет\n";
				while (*cin != 'y' && *cin != 'n')
					*cin = _getch();
				if (*cin == 'y')
					tree.insert(n);
				system("cls");
			}
			else
			{
				std::cout << "Число в дереве есть, все равно ввести его?\n y - да n - нет\n";
				while (*cin != 'y' && *cin != 'n')
					*cin = _getch();
				if (*cin == 'y')
					tree.insert(n);
				system("cls");
			}
		}

		if (exit == 'n')
			n = 1;
		else
			return 0;
		exit = 0;
	}
}

int withlog(RBtree& tree)
{
	char cin[10], exit = 0;
	int n = 1;
	while (n)
	{
		system("cls");
		tree.print();
		std::cout << "Найти: \n";
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
			std::cout << "Закончить или найти 0?\n y - найти n = выйти\n";
			while (exit != 'y' && exit != 'n')
				exit = _getch();
		}
		if (exit != 'n')
		{
			tree.print();
			if (!tree.findlog(n))
			{
				std::cout << "Числа в дереве нет, ввести его?\n y - да n - нет\n";
				while (*cin != 'y' && *cin != 'n')
					*cin = _getch();
				if (*cin == 'y')
					tree.insert_demo(n);
			}
			else
			{
				std::cout << "Число в дереве есть, все равно ввести его?\n y - да n - нет\n";
				while (*cin != 'y' && *cin != 'n')
					*cin = _getch();
				if (*cin == 'y')
					tree.insert_demo(n);
			}

		}

		if (exit != 'n')
			n = 1;
		else
			return 0;
		exit = 0;
	}
}

int main()
{
	int n = 1, c, j = 20;
	char cin[10], exit = 0;
	RBtree tree;
	setlocale(LC_ALL, "ru");

	std::cout << "Способ ввода из консоли 1, заполнить дерево случайными числами 2, ввести из файла 3\n";
	std::cin >> cin;
	//Выбор способа инициализации
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

	if (exit != 27) //Выбор размеров случайного дерева
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
	//Инициализация
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
			while (tree.getsize() < j)
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
	lin.close();

	
	while (exit != 27)
	{
		std::cout << "Запуск программы с логами 1, Без логов 2\n";
		std::cin >> cin;
		if (isdigit(*cin))
		{
			c = atoi(cin);
			if ((c != 1) && (c != 2) && (c != 3))
			{
				std::cout << "нужно ввести 1 или 2, чтобы выйти из программы нужно нажать esc\n";
				exit = _getch();
				if (exit == 27)
					break;
			}
			else
				break;
			continue;
		}
		else
		{
			std::cout << "Нужно ввести число, попробуйте еще\n";
			std::cin >> cin;
		}
	}

	system("cls");

	//Запуск программы без логов
	try
	{
		if (exit != 27)
			if (c == 2)
				withoutlog(tree);
	}
	catch (const std::exception&)
	{
		throw "Ошибка: Программа без логов не запущена";
	}
	
	
	system("cls");
	
	//Запуск программы с логами
	try
	{
		if (exit != 27)
			if (c == 1)
				withlog(tree);
	}
	catch (const std::exception&)
	{
		throw "Ошибка: Программа с логами не запущена";
	}
	
	

	getchar();
	return 0;
}