#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>

int fnum = 0;

template<class T>
void qsortRecursive(T* mas, int size) 
{
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Разрешающий элемент массива
    T mid = (mas[i] + mas[j]) / 2;

    //Делим массив
    do {
        //ищем то, что нужно перекинуть в другую часть
        //В левой части массива пропустить элементы, которые меньше центрального
        while (mas[i] < mid)
        {
            i++;
        }
        //В правой части пропустить элементы, которые больше центрального
        while (mas[j] > mid) 
        {
            j--;
        }

        //Поменять элементы местами
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
        //Левая часть
        qsortRecursive(mas, j + 1);
    }
    if (i < size)
    {
        //Правая часть
        qsortRecursive(&mas[i], size - i);
    }
}

template<class T>
void qsortRecursivelog(T* mas, int size)
{
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;


    int f = ++fnum;
    int q = size - 1;

    std::cout << f << "-й запуск функции\n массив:\n";
    for (; i <= j; i++)
        std::cout << mas[i] << "   ";
    i = 0;

    std::cout << "\n";

    //Разрешающий элемент массива

    T mid = (mas[i] + mas[j]) / 2;

    std::cout << "разрешающий элемент - " << mid << "\n";

    int l = 0;
    _getch();
    //Делим массив
    do 
    {
        std::cout << ++l << "-ая итерация: \n";
        //ищем то, что нужно перекинуть в другую часть
        //В левой части массива пропустить элементы, которые меньше центрального
        while (mas[i] < mid)
        {
            i++;
        }   
        std::cout << "i = " << i << "\n";
        //В правой части пропустить элементы, которые больше центрального
        while (mas[j] > mid)
        {
            j--;
        }
        std::cout << "j = " << j << "\n";
        //Поменять элементы местами
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
    //Рекурсивные вызовы
    if (j > 0)
    {
        //Левая часть
        std::cout << "Запуск левой части \n";
        _getch();
        qsortRecursivelog(mas, j + 1);
        std::cout << "Вернулся в " << f << "-й запуск функции\n";
    }
    if (i < size)
    {
        //Првая часть
        std::cout << "Запуск правой части \n";
        _getch();
        qsortRecursivelog(&mas[i], size - i);
        std::cout << "Вернулся в " << f << "-й запуск функции\n";
    }
    std::cout << f << "-й запуск функции завершился\n";
    _getch();
}

int main()
{
    setlocale(LC_ALL, "ru");
    int j;
    char jin[10];
    std::cout << "введите размер массива\n";
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
            std::cout << "нужно ввести цифру, попробуйте еще\n";
        }
    }
    float* mas;
    if (j != 0)
        mas = new float[j];
    else
        return 2;

    std::cout << "Ввод из консоли на кнопку 1, из файла на 2, заполнить раномными числами на любую другую\n";
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
                std::cout << "нужно ввести цифру, попробуйте еще\n";
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