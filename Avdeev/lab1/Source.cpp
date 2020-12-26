#include <iostream>
#include <fstream>
using namespace std;

int fnum = 0;

int Clog(int k, int n)
{
	cout << ++fnum << "-й запуск функции\n";
	cout << "k = " << k << "\nn = " << n << "\n";
	int f = fnum;
	if (k == 0 || k == n)
	{
		cout << "Сочетание = " << 1 << "\n";
		return 1;
	}
	else 
		if (k > n)
		{
			cout << "Сочетание = " << 0 << "\n";
			return 0;
		}
		else
		{
			cout << "Раскладываем сочетание по свойтву\n";
			return Clog(k - 1, n - 1) + Clog(k, n - 1);
		}
}

int C(int k, int n)
{
	if (k == 0 || k == n)
		return 1;
	else
		if (k > n)
			return 0;
		else
			return C(k - 1, n - 1) + C(k, n - 1);
}

int main()
{
	//выбор ввода и вывода
	setlocale(LC_ALL, "ru");
	bool CH;
	int k, n;
	cout << "Консоль - 1\tФайл-0\n";
	cin >> CH;
	//ввод и вывод в файл
	if (CH == 0)
	{
		ifstream lin("lin.txt");
		ofstream lon("lon.txt");
		lin >> k >> n;
		if (k < 0 || n < 0)
			lon << "Упс! С такими числами нельзя считать.";
		else
			lon << C(k, n);
		lin.close();
		lon.close();
	}
	else
	//ввод и вывод в консоль
	{
		cin >> k >> n;
		cout << Clog(k, n);
	}
	return 0;
}