#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstring>
#include <cmath>
#include <limits>
#include <cstring>
#include <cctype>

#define GETFLAG(r, x) ((r[(x) >> 3] >> ((x) & 7)) & 1) //если в качестве "левого" потомка родителя
#define TOGGLEFLAG(r, x) (r[(x) >> 3] ^= 1 << ((x) & 7)) //Для потомка переопределяем, порядок его потомков
//(кто "левый", а кто "правый")

using namespace std;

class WeakHeap {

public:

    vector <int> wheap;
    int size_of_heap = 0;
    unsigned char* r = nullptr;
    int s;
    WeakHeap() {}
    void DisplayArray();
    void DisplayHeap(int i, int j, int num);
    void DisplayHeap();
    void WeakHeapMerge(unsigned char* r, int i, int j, int num);
    void WeakHeapSort();
    WeakHeap* InputHeap();
    ~WeakHeap() {
        if (!wheap.empty())
            wheap.clear();
    }
};



//вычисляет логарифм от b по основанию a
double log(int a, int b)
{
    return log(b) / log(a);
}


void WeakHeap::DisplayHeap(int i_1, int j_1, int num) {


    if (i_1 == 0 || j_1 == 0)
        std::cout << "(" << wheap[0] << ")";
    else
        std::cout << wheap[0];


    cout << "\n";
    int new_size = size_of_heap - num;

    int depth = (int)log(2, new_size);//вычисляем глубину дерева
    if ((int)log(2, new_size) != pow(2, depth))
        depth += 1;

    int k = 0;
    double idt = depth * 6 / 4;



    for (int i = 0; i < depth; i++) {

        for (int iter = 0; iter < idt; iter++)
            cout << " ";
        idt = idt / 5 * 2;


        for (int j = 0; j < pow(2, i); j++) {
            if (k < new_size)
                if (k + 1 == i_1 || k + 1 == j_1) {
                    cout << "(" << wheap[k + 1] << ")" << "  ";

                }
                else {
                    cout << wheap[k + 1] << "  ";
                }

            k++;
        }

        cout << "\n";

    }


    for (int it = 0; it < 65; it++)
        cout << "_";
    cout << "\n";
}


void WeakHeap::DisplayHeap() {
    cout << wheap[0];
    cout << "\n";

    int depth = (int)log(2, size_of_heap);//вычисляем глубину дерева
    if ((int)log(2, size_of_heap) != pow(2, depth))
        depth += 1;

    int k = 0;
    double idt = depth * 2;

    for (int i = 0; i < depth; i++) {

        for (int iter = 0; iter < idt; iter++)
            cout << " ";
        idt = idt / 2;

        for (int j = 0; j < pow(2, i); j++) {
            if (k < size_of_heap - 1)
                cout << wheap[k + 1] << "  ";
            k++;
        }
        cout << "\n";
    }
}

void WeakHeap::WeakHeapMerge(unsigned char* r, int i, int j, int num) {

    cout << "Выделяем рассматриваемые элементы!\n";
    if (wheap[i] < wheap[j]) {//"Суперродитель" меньше потомка?
        //Для потомка переопределяем, порядок его потомков
        //(кто "левый", а кто "правый")

        TOGGLEFLAG(r, j);
        //Меняем значения "суперродителя" и потомка

        this->DisplayHeap(i, j, num);
        cout << "Суперродитель " << wheap[i] << " меньше потомка " << wheap[j] << ", меняем их местами\n";
        swap(wheap[i], wheap[j]);
        this->DisplayHeap(i, j, num);

    }
    else {
        this->DisplayHeap(i, j, num);
        cout << "СупперРодитель больше и равен потомку, оставляем всё, как есть.\n";
    }
}

void WeakHeap::WeakHeapSort() {
    int n = size_of_heap;
    int lef;
    int per;
    if (n > 1) {

        int i, j, x, y, Gparent;
        s = (n + 7) / 8;
        r = new unsigned char[s];

        //Массив для обозначения, какой у элемента 
        //потомок "левый", а какой "правый"
        for (i = 0; i < n / 8; ++i)
            r[i] = 0;


        cout << "\n1 ЭТАП 1 ЭТАП 1 ЭТАП 1 ЭТАП 1 ЭТАП\n";
        cout << "Построение первоначальной слабой кучи:\n";

        //Построение первоначальной слабой кучи
        for (i = n - 1; i > 0; --i) {
            j = i;
            //Поднимаемся на сколько возможно вверх, 
            //если в качестве "левого" потомка родителя
            lef = GETFLAG(r, j >> 1);
            while ((j & 1) == lef) {
                j = j >> 1;
                lef = GETFLAG(r, j >> 1);
            }
            //И ещё на один уровень вверх как "правый" потомок родителя
            Gparent = j >> 1;
            //Слияние начального элемента, с которого 
            //начали восхождение до "суперродителя"
            WeakHeapMerge(r, Gparent, i, 1);
        }

        //Перенос максимума из корня в конец -->
        //слабая просейка --> и всё по новой
        cout << "Слабая куча построена:\n";
        this->DisplayHeap();
        for (int it = 0; it < 65; it++)
            cout << " ";

        cout << "\n2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП\n";

        for (i = n - 1; i >= 2; --i) {
            cout << "Переносим максимум из корня, применяем слабую просейку:\n";
            //Максимум отправляем в конец неотсортированной части массива
            //Элемент из конца неотсортированной части попадает в корень
            this->DisplayHeap(0, i, n - i);
            cout << "Переместили корень " << wheap[0] << " и элемент из конца неотсортированной части " << wheap[i] << "\n";

            swap(wheap[0], wheap[i]);

            cout << "Отсортированная часть массива:   ";
            for (int j = i; j < size_of_heap; j++)
                cout << wheap[j] << " ";
            cout << "\n";

            cout << "Неотсортированная часть массива: ";
            for (int j = 0; j < i; j++)
                cout << wheap[j] << " ";
            cout << "\n\n";

            this->DisplayHeap(0, i, n - i);
            x = 1;
            //Опускаемся жадно вниз по "левым" веткам
            lef = GETFLAG(r, x);
            while ((y = 2 * x + lef) < i) {
                x = y;
                lef = GETFLAG(r, x);
            }
            //Поднимаемся по "левой" ветке обратно до самого вверха
            //попутно по дороге делаем слияние каждого узла с корнем
            while (x > 0) {
                WeakHeapMerge(r, 0, x, n - i);
                x >>= 1;
            }
        }
        //Последнее действие - меняем местами корень
        //и следующий за ним элемент
        this->DisplayHeap(0, 1, n - 1);
        cout << "Меняем местами корень " << wheap[0] << " и следующий за ним элемент " << wheap[1] << "\n";
        swap(wheap[0], wheap[1]);
        this->DisplayHeap(0, 1, n - 1);
        delete[] r;
    }
}
void WeakHeap::DisplayArray()
{
    for (int i = 0; i < size_of_heap; i++)
        std::cout << wheap[i] << " ";
    std::cout << "\n\n";
}

WeakHeap* WeakHeap::InputHeap() {
    int count;
    cin >> count;
    int elem;
    WeakHeap* wh = new WeakHeap();
    cout << "Введите через пробел элементы массива:\n";
    while (wh->size_of_heap != count) {
        cin >> elem;
        wh->wheap.push_back(elem);
        wh->size_of_heap++;
    }

    return wh;

}
int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа для визуализации сортировки слабой кучей.\n\n";
    cout << "На примере данной программы, можно увидеть, как происходит сортировка слабой кучей.\n\n";
    int command;
    WeakHeap* wh = nullptr;
    int flag = 0;
    while (!flag) {
        cout << "Список команд:\n 1.Ввести массив с клавиатуры\n 2.Завершить работу программы\n\n";
        cout << "Введите номер команды: \n";
        cin >> command;

        if (command == 1) {
            cout << "Введите количество элементов массива:\n";
            wh = wh->InputHeap();
            if (wh) {
                wh->WeakHeapSort();
                cout << "\nВ результате сортировки массив примет вид:\n";
                cout << "Итоговый массив: ";
                wh->DisplayArray();
                delete wh;
            }

        }
        else if (command == 2) {
            cout << "Работа программы завершена!\n";
            flag = 1;
        }
        else {
            cout << "Введите корректную команду! \n" << command << "\n";
        }
    }

    return 0;
}
