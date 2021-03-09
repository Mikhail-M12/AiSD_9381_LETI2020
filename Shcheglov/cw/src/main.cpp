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

typedef struct elem { //структура для записи элементов массива типа число-бит
    int number;
    int bite;
} elem;

class WeakHeap {

public:

    vector <int> wheap;
    int size_of_heap = 0;
    int size_of_array = 0;
    unsigned char* r = nullptr;
    int s;
    elem* heap;
    WeakHeap(){}
    WeakHeap(int size) { //конструктор для создания новой слабой кучи
        size_of_heap = size;
        heap = new elem[size_of_heap]; //выделяем память под массив элементов кучи
        for (int i = 0; i < size_of_heap; i++)
            heap[i].number = 0;
    }
    void DisplayArray();
    void DisplayHeap(int i, int j, int num);
    void DisplayHeap();
    void WeakHeapMerge(unsigned char* r, int i, int j, int num, int* bit);
    void WeakHeapSort();
    void push(elem x);
    WeakHeap* InputHeap();
    int* bit;
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


void WeakHeap::push(elem x) { //функция помещения элемента в кучу
    heap[size_of_array].number = x.number;
    heap[size_of_array].bite = x.bite;
    size_of_array++; //так как теперь в куче на один элемент больше
}


void WeakHeap::DisplayHeap(int i_1, int j_1, int num) {
    vector <int> res = wheap; //сохраняем состояние массива чисел
    cout << "Текущее состояние массива бит: ";
    for (int i = 1; i < s; i++)
        cout << bit[i] << " ";
    cout << "\n";
    for (int i = 1; i < s; i++) {
        if (bit[i] == 0)
            cout << "Так как бит предка " << wheap[i] <<" равен 0, его потомки должны быть на месте:\n";
        else {
            cout << "Так как бит предка " << wheap[i] <<" равен 1, его потомки должны быть переставлены:\n";
                int c = wheap[2 * i + bit[i]];
                wheap[2 * i + bit[i]] = wheap[2 * i + 1 - bit[i]];
                wheap[2 * i + 1 - bit[i]] = c;
        }
    }




    if (i_1 == 0 || j_1 == 0)
        cout << "(" << wheap[0] << ")";
    else
        cout << wheap[0];


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
    wheap = res;
}


void WeakHeap::DisplayHeap() {
    cout << " " << heap[0].number;
    int depth = (int)log(2, size_of_heap);//вычисляем глубину дерева
    if ((int)log(2, size_of_heap) != pow(2, depth))
        depth += 1;
    cout << "                 добавляем в кучу следующий элемент\n";
    int k = 0;
    double idt = depth * 2;

    for (int i = 0; i < depth - 1; i++) { //цикл для вывода всей кучи

        for (int iter = 0; iter < idt; iter++)
            cout << " ";
        idt = idt / 2;

        for (int j = 0; j < pow(2, i); j++) { //цикл для вывода строки
            cout << heap[k + 1].number;
            for (int it = 0; it < idt * 4 - 1; it++)
                cout << " ";

            k++;
        }
        cout << "\n";

    }
}

void WeakHeap::WeakHeapMerge(unsigned char* r, int i, int j, int num, int* bit) {

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
    int size_of_array = size_of_heap;
    int lef;
    if (n > 1) {
        int i, j, x, y, Gparent;
        s = (n + 7) / 8;
        r = new unsigned char[s];
        s = n / 2;
        bit = new int[s];
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
        cout << "\nВывод итоговой слабой кучи c использованием массива:\n";

        cout << " ";
        for (i = 1; i < n / 2; ++i)
            cout << bit[i] << "|";

        cout <<"    массив бит \n";

        for (int i = 0; i < size_of_heap; i++)
            cout << wheap[i] << "|";
        cout << "   массив чисел \n";

        elem* bit_array = new elem[size_of_heap]; // выделяем динамическую память под массив бит

        for (int i = 0; i < size_of_heap; i++) { //считываем массив, который является слабой кучей
            bit_array[i].number = wheap[i];
            if (i >= 1 && i < n / 2)
                bit_array[i].bite = bit[i];
            else
                bit_array[i].bite = -1;
        }

        heap = new elem[size_of_heap]; // выделяем динамическую память под массив бит
        for (int i = 0; i < size_of_heap; i++)
            heap[i].number = 0;

        cout << "\n\n";
        cout << "В конструктуре инициализируем массив для кучи нулями:\n\n";

        cout << "Массив битов:";

        for (int i = 0; i < size_of_heap; i++)
            cout << bit_array[i].bite << " ";
        cout << "\n";

        cout << "Массив чисел: ";
        for (int i = 0; i < size_of_heap; i++)
            cout << bit_array[i].number << " ";
        cout << "\n\n";

        this->DisplayHeap();
        for (int it = 0; it < 65; it++)
            cout << "_";
        cout << "\n";
        this->push(bit_array[0]);
        this->DisplayHeap();
        for (int it = 0; it < 65; it++)
            cout << "_";
        cout << "\n";
        this->push(bit_array[1]);
        this->DisplayHeap();
        for (int it = 0; it < 65; it++)
            cout << "_";
        cout << "\n";

        int count_of_bit = size_of_heap / 2; // количество элементов с не фиктивным дополнительным битом

        for (int i = 1; i < count_of_bit; i++) {//записываем элементы в кучу в порядке, удобном для вывода на экран
            if (bit_array[i].bite == 0)
                cout << "Так как бит предка равен 0, оставляем на месте его потомков:\n";
            else
                cout << "Так как бит предка равен 1, переставляем местами его потомков:\n";
            this->push(bit_array[2 * i + bit_array[i].bite]); // Левый потомок: 2 * i + BIT[i]
            this->DisplayHeap();
            for (int it = 0; it < 65; it++)
                cout << "_";
            cout << "\n";
            this->push(bit_array[2 * i + 1 - bit_array[i].bite]);// Правый потомок: 2 * i + 1 - BIT[i]
            this->DisplayHeap();
            for (int it = 0; it < 65; it++)
                cout << "_";
            cout << "\n";
        }
        cout << "\n^^^^^^^^^^^^^^^^ Получившаяся слабая куча выведена на экран!\n";
        delete[] bit_array; //освобождаем память, чтобы избежать утечки
        delete[] heap;
        //Перенос максимума из корня в конец -->
       //слабая просейка --> и всё по новой
        cout << "\n2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП 2 ЭТАП\n";
        cout << "На 2 этапе из корня кучи текущий максимальный элемент перемещаем в конец\n";
        cout  <<"неотсортированной части массива, после чего восстанавливаем слабую кучу\n";
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
                WeakHeapMerge(r, 0, x, n - i, bit);
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
