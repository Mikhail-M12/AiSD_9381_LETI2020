#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>

int fnum = 0;

template<class T>
void qsortRecursive(T* mas, int size) 
{
    //��������� � ������ � � ����� �������
    int i = 0;
    int j = size - 1;

    //����������� ������� �������
    T mid = (mas[i] + mas[j]) / 2;

    //����� ������
    do {
        //���� ��, ��� ����� ���������� � ������ �����
        //� ����� ����� ������� ���������� ��������, ������� ������ ������������
        while (mas[i] < mid)
        {
            i++;
        }
        //� ������ ����� ���������� ��������, ������� ������ ������������
        while (mas[j] > mid) 
        {
            j--;
        }

        //�������� �������� �������
        if (i <= j) 
        {
            T tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) 
    {
        //����� �����
        qsortRecursive(mas, j + 1);
    }
    if (i < size)
    {
        //������ �����
        qsortRecursive(&mas[i], size - i);
    }
}

template<class T>
void qsortRecursivelog(T* mas, int size)
{
    //��������� � ������ � � ����� �������
    int i = 0;
    int j = size - 1;


    int f = ++fnum;
    int q = size - 1;

    std::cout << f << "-� ������ �������\n ������:\n";
    for (; i <= j; i++)
        std::cout << mas[i] << "   ";
    i = 0;

    std::cout << "\n";

    //����������� ������� �������

    T mid = (mas[i] + mas[j]) / 2;

    std::cout << "����������� ������� - " << mid << "\n";

    int l = 0;
    _getch();
    //����� ������
    do 
    {
        std::cout << ++l << "-�� ��������: \n";
        //���� ��, ��� ����� ���������� � ������ �����
        //� ����� ����� ������� ���������� ��������, ������� ������ ������������
        while (mas[i] < mid)
        {
            i++;
        }   
        std::cout << "i = " << i << "\n";
        //� ������ ����� ���������� ��������, ������� ������ ������������
        while (mas[j] > mid)
        {
            j--;
        }
        std::cout << "j = " << j << "\n";
        //�������� �������� �������
        if (i <= j) 
        {
            T tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            for (int p = 0; p <= q; p++)
                std::cout << mas[p] << "   ";
           
            std::cout << "\n";
            _getch();

            i++;
            j--;
        }
    } while (i <= j);

    std::cout << size << "\n";
    //����������� ������
    if (j > 0)
    {
        //����� �����
        std::cout << "������ ����� ����� \n";
        _getch();
        qsortRecursivelog(mas, j + 1);
        std::cout << "�������� � " << f << "-� ������ �������\n";
    }
    if (i < size)
    {
        //����� �����
        std::cout << "������ ������ ����� \n";
        _getch();
        qsortRecursivelog(&mas[i], size - i);
        std::cout << "�������� � " << f << "-� ������ �������\n";
    }
    std::cout << f << "-� ������ ������� ����������\n";
    _getch();
}

int main()
{
    setlocale(LC_ALL, "ru");
    int j;
    char jin[10];
    std::cout << "������� ������ �������\n";
    while (1)
    {
        std::cin >> jin;
        if (isdigit(*jin))
        {
            j = atoi(jin);
            break;
        }
        else
        {
            std::cout << "����� ������ �����, ���������� ���\n";
        }
    }
    float* mas;
    if (j != 0)
        mas = new float[j];
    else
        return 2;

    std::cout << "���� �� ������� �� ������ 1, �� ����� �� 2, ��������� ��������� ������� �� ����� ������\n";
    char k;
    k = _getch();
    srand(time(0));

    std::ifstream lin("lin.txt");
    if (!lin.is_open())
        return 1;
    switch (k)
    {
    case '1':
        for (int i = 0; i < j; i++)
        {
            char masin[10];
            std::cin >> masin;
            if (isdigit(*masin))
                mas[i] = atoi(masin);
            else
            {
                std::cout << "����� ������ �����, ���������� ���\n";
                i--;
                continue;
            }
        }
        break;
    case '2':
        for (int i = 0; i < j; i++)
        {
            lin >> mas[i];
        }
        break;
    default:
        for (int i = 0; i < j; i++)
        {
            mas[i] = rand() % 1000;
        }
        break;
    }

    lin.close();
    qsortRecursivelog(mas, j);

    for (int i = 0; i < j; i++)
        std::cout << mas[i] << "   ";


    delete[] mas;

    return 0;
}