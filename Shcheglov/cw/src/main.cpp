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
    int size_of_array = 0;
    int nsize = 0;
    unsigned char* r = nullptr;
    int s;
    WeakHeap() {}
    void DisplayArray();
    void DisplayHeap(int i, int j, int num);
    void WeakHeapMerge(unsigned char* r, int i, int j, int num, int* bit);
    void WeakHeapSort();
    WeakHeap* InputHeap();
    int* bit;
    int* mas;
    int flag = 0;
    int flag2 = 0;
    int flag4 = 0;
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
    vector <int> res = wheap; //сохраняем состояние массива чисел
    int current_size = size_of_heap - num;
    cout << "Текущее состояние массива бит: ";
    for (int i = 1; i < s; i++)
        cout << bit[i] << " ";
    cout << "\n";

    for (int i = 1; i < s; i++) //сохраняем текущее занчение масссива для дальнейшего корректного отображения
        mas[i] = bit[i];

    if (flag == 0) {
        for (int i = 1; i < s; i++) {

            if (bit[i] == 0)
                cout << "Так как бит предка " << wheap[i] << " равен 0, его потомки должны быть на месте:\n";
            else {
                cout << "Так как бит предка " << wheap[i] << " равен 1, его потомки должны быть переставлены:\n";
                int x = 0;
                int y;
                for (y = 1; y <= sqrt(nsize); ) {//size_of_heap
                    for (x = 0; x < y; x++) {
                        if (y * (2 * i + 1) + x < nsize) { //size_of_heap
                            int c = wheap[y * (2 * i) + x];
                            wheap[y * (2 * i) + x] = wheap[y * (2 * i + 1) + x];
                            wheap[y * (2 * i + 1) + x] = c;
                        }
                        if (y * (2 * i + 1) + x < s) {
                            int c1 = bit[y * (2 * i) + x];
                            bit[y * (2 * i) + x] = bit[y * (2 * i + 1) + x];
                            bit[y * (2 * i + 1) + x] = c1;
                        }
                    }
                    y = y * 2;
                }
            }
        }

    }

    else {
        cout << "Текущий размер кучи: " << current_size + flag4 << "\n\n";

        for (int it = current_size + 1 - flag2; it < size_of_heap; it++)
            wheap[it] = -2147483647;

        for (int i = 1; i < s; i++) {

            if (bit[i] == 0)
            {
                if (flag == 0)
                cout << "Так как бит предка " << wheap[i] << " равен 0, его потомки должны быть на месте:\n";
            }
            else {
                if (flag == 0) {
                    cout << "Так как бит предка " << wheap[i] << " равен 1, его потомки должны быть переставлены:\n";
                }
                int x = 0;
                int y;
                for (y = 1; y <= sqrt(nsize); ) { //size_of_heap
                    for (x = 0; x < y; x++) {
                        int flag3 = 0;
                        if (y * (2 * i + 1) + x < nsize) { //size_of_heap
                            int c = wheap[y * (2 * i) + x];
                            wheap[y * (2 * i) + x] = wheap[y * (2 * i + 1) + x];
                            wheap[y * (2 * i + 1) + x] = c;

                            if (y * (2 * i) + x == j_1) {
                                flag3++;
                                j_1 = y * (2 * i + 1) + x;
                            }

                            if (y * (2 * i + 1) + x == j_1 && flag3 == 0)
                                j_1 = y * (2 * i) + x;

                        }
                        if (y * (2 * i + 1) + x < s) {
                            int c1 = bit[y * (2 * i) + x];
                            bit[y * (2 * i) + x] = bit[y * (2 * i + 1) + x];
                            bit[y * (2 * i + 1) + x] = c1;
                        }
                    }
                    y = y * 2;

                }


            }
        }

    }

    if (i_1 == 0 || j_1 == 0)
        cout << "(" << wheap[0] << ")";
    else
        cout << wheap[0];


    cout << "\n";
    int new_size;
    if (flag == 0)
        new_size = nsize - num; //size_of_heap
    else
        new_size = nsize - 1;

    int depth = (int)log(2, new_size);//вычисляем глубину дерева
    if ((int)log(2, new_size) != pow(2, depth))
        depth += 1;

    int k = 0;
    int num_elem_in_str = 0; //смотрим, какой по счёту данный элемент в строке
    double idt = depth * 3.5;
    double idt_2 = idt;

    for (int i = 0; i < depth; i++) {
        num_elem_in_str = 0;
        if (num_elem_in_str == 0) {
            for (int iter = 0; iter < idt; iter++)
                cout << " ";
            idt = idt / 2 - 1;
        }
        else
        {
            for (int iter = 0; iter < idt_2; iter++)
                cout << " ";
        }

        for (int j = 0; j < pow(2, i); j++) {
            if (k < new_size) {
                if (k + 1 == i_1 || k + 1 == j_1)
                    if (wheap[k + 1] == -2147483647)
                        cout << "  ";
                    else
                    cout << "(" << wheap[k + 1] << ")";


                else {
                    if (wheap[k + 1] == -2147483647)
                        cout << "  ";
                    else
                    cout << wheap[k + 1];
                }

            }

            for (int iter = 0; iter < idt_2; iter++)
                cout << " ";

            k++;
            num_elem_in_str++;
        }
        cout << "\n";
        if (num_elem_in_str != 1)
              idt_2 = idt_2 / 2 - 1;
    }
    for (int it = 0; it < 73; it++)
        cout << "_";
    cout << "\n";
    wheap = res;
    for (int i = 1; i < s; i++)
        bit[i] = mas[i];
}

void WeakHeap::WeakHeapMerge(unsigned char* r, int i, int j, int num, int* bit) {
    flag4 = 0;
    cout << "Выделяем рассматриваемые элементы!\n";
    if (wheap[i] < wheap[j]) {//"Суперродитель" меньше потомка?
        //Для потомка переопределяем, порядок его потомков
        //(кто "левый", а кто "правый")
        TOGGLEFLAG(r, j);
        this->DisplayHeap(i, j, num);

        if (j > 0 && j < size_of_heap / 2) {
            if (bit[j] == 1)
                bit[j] = 0;
            else
                bit[j] = 1;
        }

        //Меняем значения "суперродителя" и потомка
        cout << "Суперродитель " << wheap[i] << " меньше потомка " << wheap[j] << ", меняем их местами.\n";
        if (flag == 0) {
            if (size_of_heap / 2 > j) {
                if (wheap[2 * j] != -2147483647 && wheap[2 * j + 1] != -2147483647)
                cout << "Меняем местами поддеревья с потомками для узла,\n в котором находится текущий элемент.\n";
            }
        }
        else {
            if ((size_of_heap - num + 1) / 2 > j) {
                if (wheap[2 * j] != -2147483647 && wheap[2 * j + 1] != -2147483647)
                cout << "Меняем местами поддеревья с потомками для узла,\n в котором находится текущий левый потомок.\n";
            }
        }
        swap(wheap[i], wheap[j]);
        this->DisplayHeap(i, j, num);
        flag4++;
    }
    else {
        this->DisplayHeap(i, j, num);
        flag4++;
        cout << "Суперродитель больше или равен потомка, оставляем всё, как есть.\n";
    }
}

void WeakHeap::WeakHeapSort() {
    int n = size_of_heap;
    int size_of_array = size_of_heap;
    int lef;
    if (n > 1) {
        int i, j, x, y, Gparent;
        s = (n + 7) / 8;
        r = new unsigned char[s];
        s = n / 2;
        bit = new int[s];
        mas = new int[s];
        //Массив для обозначения, какой у элемента
        //потомок "левый", а какой "правый"
        for (i = 1; i < n / 2; ++i)
            bit[i] = 0;
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
            WeakHeapMerge(r, Gparent, i, 1, bit);
        }
        cout << "Теперь строим итоговую слабую кучу:\n\n";
        cout << "На данном этапе имеем:\n";
        cout << " ";
        for (i = 1; i < n / 2; ++i)
            cout << bit[i] << "|";
        cout << "    массив бит \n";

        for (int i = 0; i < size_of_heap; i++)
            cout << wheap[i] << "|";
        cout << "   массив чисел \n";

        cout << "\nВывод итоговой слабой кучи c использованием массива:\n";

        this->DisplayHeap(-1, -1, 1);
        cout << "\n^^^^^^^^^^^^^^^^^^^^^^ Получившаяся слабая куча выведена на экран!\n";

        for (int i = 0; i < size_of_heap; i++)
            cout << wheap[i] << "|";
        cout << "   массив чисел \n";

        //Перенос максимума из корня в конец -->
       //слабая просейка --> и всё по новой
        cout << "\n2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП\n";
        cout << "На 2 этапе из корня кучи текущий максимальный элемент перемещаем в конец\n";
        cout << "неотсортированной части массива, после чего восстанавливаем слабую кучу\n";
        flag++;
        for (i = n - 1; i >= 2; --i) {
            cout << "Переносим максимум из корня, применяем слабую просейку:\n";
            //Максимум отправляем в конец неотсортированной части массива
            //Элемент из конца неотсортированной части попадает в корень
            this->DisplayHeap(0, i, n - i); //везде i будет последним
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
            cout << "Последний элемент с максимумом перестаёт быть узлом слабой кучи.\n\n";
            flag2++;
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
                WeakHeapMerge(r, 0, x, n - i, bit); // массив бит / i / j / количество отсортированных элементов / массив бит для вывода
                x >>= 1;
            }
            flag2--;
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
        cout << wheap[i] << " ";
    cout << "\n\n";
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
    int p = 1;
    while (count > pow(2, p))
        p++;
    wh->nsize = pow(2, p);
    for (int i = count; i < wh->nsize; i++)
        wh->wheap.push_back(-2147483647);
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
