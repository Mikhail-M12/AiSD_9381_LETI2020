#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

int fnum = 0;

class elem
{
public:
	int num;
	int E;
	elem* left = NULL;
	elem* right = NULL;
};

void push(int a, elem** t)
{
	if ((*t) == NULL)
	{
		(*t) = new elem;
		(*t)->num = ++fnum;
		(*t)->E = a;
		(*t)->left = (*t)->right = NULL;
		return;
	}

	if (a > (*t)->E) push(a, &(*t)->right);
	else push(a, &(*t)->left);
}

void printTree(elem* t, int u)
{
	if (t == NULL) return;
	else
	{
		printTree(t->right, ++u);
		for (int i = 0; i < u - 1; ++i) cout << "\t";
		cout << t->num << "(" << t->E << ")\n";
		u--;
	}
	printTree(t->left, ++u);
}

bool isContains(elem* t, int E)
{
	if (t == NULL)
		return 0;
	if (t->E == E)
		return 1;
	bool r;
	if (t->E > E)
		r = isContains(t->left, E);
	else
		r = isContains(t->right, E);
	return r;
}

bool isContainslog(elem* t, int E)
{
	int f = ++fnum;
	cout << f << "-й запуск функции\n";
	if (t == NULL)
	{
		cout << "плечо отсутствует возвращается назад\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return 0;
	}
	cout << "находится в узле " << t->num << "\n";
	if (t->E == E)
	{
		cout << "узел найден, возвращается назад\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return 1;
	}
	else
		_getch();
	bool r;
	if (t->E >= E)
	{
		cout << "перемещается в левое плечо\n";
		_getch();
		r = isContainslog(t->left, E);
		cout << "вернулся в узел " << t->num << "\n";
	}
	else
	{
		cout << "перемещается в правое плечо\n";
		_getch();
		r = isContainslog(t->right, E);
		cout << "вернулся в узел " << t->num << "\n";
	}
	cout << f << "-й запуск функции завершился\n";
	_getch();
	return r;
}

int searchElem(elem* t, int E)
{
	if (!t)
		return 0;
	int res = 0;
	if (t->E == E)
		res = 1;
	if (t->E >= E)
		res += searchElem(t->left, E);
	else
		res += searchElem(t->right, E);
	return res;
}

int searchElemlog(elem* t, int E)
{
	int f = ++fnum;
	cout << f << "-й запуск функции\n";
	if (!t)
	{
		cout << "плечо отсутствует возвращается назад\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return 0;
	}
	cout << "находится в узле " << t->num << "\n";
	int res = 0;
	if (t->E == E)
	{
		cout << "узел содержит элемент\n";
		_getch();
		res = 1;
	}
	else
		_getch();
	if (t->E >= E)
	{
		cout << "перемещается в левое плечо\n";
		_getch();
		res += searchElemlog(t->left, E);
		cout << "вернулся в узел " << t->num << "\n";
	}
	else
	{
		cout << "перемещается в правое плечо\n";
		_getch();
		res += searchElemlog(t->right, E);
		cout << "вернулся в узел " << t->num << "\n";
	}
	cout << f << "-й запуск функции завершился\n";
	_getch();
	return res;
}

int path(elem* t, int E)
{
	int res = 0;
	if (!t)
		return -1;
	if (t->E == E)
		return 0;
	if (t->E < E)
	{
		int r = path(t->right, E);
		return r == -1 ? -1 : ++res + r;
	}
	else
	{
		int r = path(t->left, E);
		return r == -1 ? -1 : ++res + r;
	}
}

int pathlog(elem* t, int E)
{
	int f = ++fnum;
	cout << f << "-й запуск функции\n";
	int res = 0;
	if (!t)
	{
		cout << "плечо отсутствует -> элемент отсутствует, возвращается назад\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return -1;
	}
	else
		_getch();
	cout << "находится в узле " << t->num << "\n";
	if (t->E == E)
	{
		cout << "узел содержит элемент\n";
		_getch();
		return 0;
	}
	else
		_getch();
	if (t->E < E)
	{
		cout << "перемещается в правое плечо\n";
		_getch();
		int r = pathlog(t->right, E);
		cout << "вернулся в узел " << t->num << "\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return r == -1 ? -1 : ++res + r;
	}
	else
	{
		cout << "перемещается в левое плечо\n";
		_getch();
		int r = pathlog(t->left, E);
		cout << "вернулся в узел " << t->num << "\n";
		cout << f << "-й запуск функции завершился\n";
		_getch();
		return r == -1 ? -1 : ++res + r ;
	}
}

void file(elem** t)
{
	int n;
	int s;
	ifstream lin("lin.txt");
	lin >> n;

	for (int i = 0; i < n; ++i)
	{
		lin >> s;

		push(s, &(*t));
	}
	fnum = 0;
	lin.close();
}

void console(elem** t)
{
	while(1)
	{
		char nin,  sin;
		int n;
		int s;
		cout << "Введите количество элементов\n";
		cin >> nin;
		if (isdigit(nin))
		{
			n = atoi(&nin);

			for (int i = 0; i < n; ++i)
			{
				cout << "Введите число\n";
				cin >> sin;
				if (isdigit(sin))
					s = atoi(&sin);
				else
				{
					cout << "неправильный ввод, попробуйте еще\n";
					i--;
					continue;
				}

				push(s, &(*t));
			}
			
			return;
		}
		else
			cout << "неправильный ввод, попробуйте еще\n";
	}
	fnum = 0;
}

void deleteCor(elem* cor)
{
	if (cor != NULL) {
		deleteCor(cor->left);
		deleteCor(cor->right);
		delete cor;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	elem* t = NULL;
	char k;
	cout << "Ввод из консоли на кнопку С, из файла на любую другую\n";
	k = _getch();
	
	switch(k)
	{ 
	case 'c':
		console(&t);
		break;
	default:
		file(&t);
	}
	fnum = 0;
	printTree(t, 0);
	int E;
	while (1)
	{
		cout << "Введите элемент \n";
		cin >> k;
		if (isdigit(k))
			E = atoi(&k);
		else
		{
			cout << "Нужно ввести число\n";
			continue;
		}

		cout << "Выяснить есть ли он в дереве на кнопку 1, Выяснить количество элементов в дереве 2, найти путь до близжаешего узла с элементов любая другая кнопка\n";
		k = _getch();
		switch (k)
		{
		case '1':
			cout << "пошаговый метод на кнопку 1, обычный на любую другую\n";
			k = _getch();
			switch (k)
			{
			case '1':
				cout << isContainslog(t, E);
				break;
			default:
				cout << isContains(t, E);
				break;
			}
			break;
		case '2':
			cout << "пошаговый метод на кнопку 1, обычный на любую другую\n";
			k = _getch();
			switch (k)
			{
			case '1':
				cout << searchElemlog(t, E);
				break;
			default:
				cout << searchElem(t, E);
				break;
			}
			break;
		default:
			cout << "пошаговый метод на кнопку 1, обычный на любую другую\n";
			k = _getch();
			switch (k)
			{
			case '1':
				cout << pathlog(t, E);
				break;
			default:
				cout << path(t, E);
				break;
			}
			break;
		}
		break;
	}



	deleteCor(t);

	

	return 0;
}