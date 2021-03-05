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
#define GETFLAG(r, x) ((r[(x) >> 3] >> ((x) & 7)) & 1)
#define TOGGLEFLAG(r, x) (r[(x) >> 3] ^= 1 << ((x) & 7))

using namespace std;

class WeakHeap {
public:
    vector <int> wheap;
    int size_of_heap = 0;
    unsigned char* bit_array = NULL;
    int size_array;
    WeakHeap(){}
    void DisplayArray();
    void DisplayHeap();
    void WeakHeapMerge(unsigned char* r, int i, int j);
    void WeakHeapSort();
    WeakHeap* InputHeap();
    ~WeakHeap() {
        if (!wheap.empty())
            wheap.clear();
    }
};

double log(int a, int b)
{
    return log(b) / log(a);
}

void WeakHeap::DisplayHeap() {
    vector <int> heap1;
    heap1.push_back(wheap[0]);
    heap1.push_back(wheap[1]);
    for (int i = 0; i < size_array; i++) {//записываем элементы в кучу в порядке, удобном для вывода на экран
        heap1.push_back(wheap[2 * i + bit_array[i]]);
        heap1.push_back(wheap[2 * i + 1 - bit_array[i]]);

    }
    cout << wheap[0];
    cout << "\n";

    int depth = (int)log(2, size_of_heap);//вычисляем глубину дерева
    if ((int)log(2, size_of_heap) != pow(2, depth))
        depth++;

    int k = 0;
    double idt = depth * 2;
    for (int i = 0; i < depth; i++) {

        for (int iter = 0; iter < idt; iter++)
            cout << " ";
        idt = idt / 2;

        for (int j = 0; j < pow(2, i); j++) {
                cout << wheap[k + 1] << "  ";
                for (int it = 0; it < idt * 4 - 1; it++)
                    cout << " ";
            k++;
        }
        cout << "\n";
    }
    for (int i = 0; i < 100; i++)
        cout <"_";
}

void WeakHeap::WeakHeapMerge(unsigned char* r, int i, int j) {
 if (wheap[i] < wheap[j]) {//"Суперродитель" меньше потомка?
        //Для потомка переопределяем, порядок его потомков
        //(кто "левый", а кто "правый")

        TOGGLEFLAG(r, j);
        //Меняем значения "суперродителя" и потомка
        this->DisplayHeap();
        cout << "СуперРодитель " << wheap[i] << " меньше потомка " << wheap[j] << ", меняем их местами\n";

        swap(wheap[i], wheap[j]);
        this->DisplayHeap();

    }
    else {
        this->DisplayHeap();
        for (int i = 0; i < 100; i++)
        cout <"_";
    }
}

void WeakHeap::WeakHeapSort() {
    int n = size_of_heap;
    int lef;
    int per;
    if (n > 1) {

    int i, j, x, y, Gparent;
    size_array = (n + 7) / 8;
    bit_array = new unsigned char[size_array];
    for (i = 0; i < n / 8; ++i)
    bit_array[i] = 0;


    cout << "Построение первоначальной слабой кучи\n";

    //Построение первоначальной слабой кучи
    for (i = n - 1; i > 0; --i) {
        j = i;
        lef = GETFLAG(bit_array, j >> 1);
        while ((j & 1) == lef) {
            j = j >> 1;
            lef = GETFLAG(bit_array, j >> 1);
        }
            //И ещё на один уровень вверх как "правый" потомок родителя
        Gparent = j >> 1;
            //Слияние начального элемента, с которого
            //начали восхождение до "суперродителя"
        WeakHeapMerge(bit_array, Gparent, i);
    }

    //Перенос максимума из корня в конец -->
    //слабая просейка --> и всё по новой
    cout << "Слабая куча построена\n";
    this->DisplayHeap();

    for (i = n - 1; i >= 2; --i) {
    cout << "Переносим максимум из корня, применяем слабую просейку\n";
    //Максимум отправляем в конец неотсортированной части массива
    //Элемент из конца неотсортированной части попадает в корень
    this->DisplayHeap();
    cout << "Переместили корень " << wheap[0] << " и элемент из конца неотсортированной части " << wheap[i] << "\n";
    swap(wheap[0], wheap[i]);
    this->DisplayHeap();
    x = 1;
    //Опускаемся жадно вниз по "левым" веткам
    lef = GETFLAG(bit_array, x);
    while ((y = 2 * x + lef) < i) {
    x = y;
    lef = GETFLAG(bit_array, x);
    }
    //Поднимаемся по "левой" ветке обратно до самого вверха
    //попутно по дороге делаем слияние каждого узла с корнем
    while (x > 0) {
        WeakHeapMerge(bit_array, 0, x);
        x >>= 1;
    }
    }
    //Последнее действие - меняем местами корень
        //и следующий за ним элемент
    this->DisplayHeap();
    cout << "Меняем местами корень " << wheap[0] << " и следующий за ним элемент " << wheap[1] << "\n";
    swap(wheap[0], wheap[1]);
    this->DisplayHeap();
    delete[] bit_array;
    }
}


void WeakHeap::DisplayArray()
{
    for (int i = 0; i < size_of_heap; i++)
        cout << wheap[i] << " ";
    cout << "\n\n\n";
}

WeakHeap* WeakHeap::InputHeap() {
    int count;
    cin >> count;
    int elem;
    WeakHeap* wh = new WeakHeap();
    while (wh->size_of_heap != count) {
        cin >> elem;
        wh->wheap.push_back(elem);
        wh->size_of_heap++;
}

    return wh;
}



int main() {
	setlocale(LC_ALL, "rus");
    cout << "Программа для визуализации сортировки слабой кучей.\n\n";
    cout << "На примере данной программы, можно увидеть, как происходит сортировка слабой кучей.\n\n";
    WeakHeap* wh = NULL;
    cout << "Введите количество элементов массива:\n";
    wh = wh->InputHeap(); //вводим элементы в кучу
    wh->WeakHeapSort();
    cout << "\nВ результате сортировки массив примет вид:\n";
    cout << "Итоговый массив: ";
    wh->DisplayArray();
    delete wh;
	return 0;
 }
