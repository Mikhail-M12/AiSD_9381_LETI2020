#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <fstream>
#include <cstring>
#include <cmath>
#include <limits>
#include <cstring>


using namespace std;

class WeakHeap {

public:
    vector <int> wheap;
    int size_of_heap = 0;
    int* bit_array = NULL;
    int size_array;
    WeakHeap* InputHeap();
    void DisplayArray();
    void DisplayHeap();
    void WeakHeapMerge(int* bit_array, int i, int j);
    void WeakHeapSort();

    ~WeakHeap() {
        if (!wheap.empty())
            wheap.clear();
    }

};

double logarifm(int a, int b) //вычисление логарифма b по сонованию a
{
    return log(b) / log(a);
}

void WeakHeap::DisplayHeap() {

    vector <int> result_heap;
    result_heap.push_back(wheap[0]);
    result_heap.push_back(wheap[1]);
    for (int i = 0; i < size_array; i++) {//записываем элементы в кучу в порядке, удобном для вывода на экран
        result_heap.push_back(wheap[2 * i + bit_array[i]]);
        result_heap.push_back(wheap[2 * i + 1 - bit_array[i]]);

    }
    cout << wheap[0];
    cout << "\n";

    int depth = (int)logarifm(2, size_of_heap); //вычисляем глубину дерева
    if (depth == 3)
        depth++;
    int k = 0;
    double idt = depth * 2;
    for (int i = 0; i < depth; i++) {

        for(int iter = 0; iter < idt; iter++)
            cout <<" ";
        idt = idt / 2;

        for (int j = 0; j < pow(2, i); j++) {
            cout << wheap[k+1]<< "  ";
            for (int it = 0; it < idt * 4 - 1; it++)
                cout << " ";
            k++;
        }
        cout << "\n";
    }

    for (int i = 0; i < 100; i++)
        cout << "_";
    cout << "\n";
}

void WeakHeap::WeakHeapMerge(int* bit_array, int i, int j) {


    if (wheap[i] < wheap[j]) { //Для потомка переопределяем, порядок его потомков, кто левых, а кто правый
        bit_array[j>>3] ^= 1 << ((j) & 7);
        this->DisplayHeap();
        cout << "СуперРодитель " << wheap[i] << " меньше потомка " << wheap[j] << ", меняем их местами\n";
        swap(wheap[i], wheap[j]);//Меняем значения "суперродителя" и потомка
        this->DisplayHeap();

    }
    else {
        this->DisplayHeap();
        for (int i = 0; i < 100; i++)
            cout << "_";
        cout << "\n";
    }
}

void WeakHeap::WeakHeapSort() {
    int n = size_of_heap;
    int lef;
    int per;
    if (n > 1){
    int i;
    int j;
    int x;
    int y;
    int GreatParent;
    size_array = (n + 7) / 8;
    bit_array = new int[size_array]; // массив для обозначения левого и правого потомков элемента
    for (i = 0; i < n / 8; ++i)
            bit_array[i] = 0;
    cout << "Построение первоначальной слабой кучи\n";
            for (i = n - 1; i > 0; --i) { //Построение первоначальной слабой кучи
            j = i;
            //Поднимаемся на сколько возможно вверх,
            lef = (bit_array[(j >> 1) >> 3] >> ((j >> 1) & 7)) & 1;  //если в качестве левого потомка родителя
            while ((j & 1) == lef) {
                j = j >> 1;
                lef = (bit_array[(j >> 1) >> 3] >> ((j >> 1) & 7)) & 1;
            }
            GreatParent = j >> 1;//И ещё на один уровень вверх как правый потомок родителя
            WeakHeapMerge(bit_array, GreatParent, i); //Слияние начального элемента, с которого начали восхождение до СуперРодителя
        }
        cout << "Слабая куча построена!!!\n"; //переносим максимум из корня в конец, потом слабая просейка
        this->DisplayHeap();

        for (i = n - 1; i >= 2; --i) {
            cout << "Переносим максимум из корня, применяя слабую просейку\n";
            this->DisplayHeap();
            cout << "Переместили корень " << wheap[0] << " и элемент из конца неотсортированной части " << wheap[i] << "\n";
            swap(wheap[0], wheap[i]);
            this->DisplayHeap();
            x = 1;
            lef = (bit_array[(j >> 1) >> 3] >> ((j >> 1) & 7)) & 1; //Опускаемся жадно вниз по левым веткам
            while ((y = 2 * x + lef) < i) {
                x = y;
                lef = (bit_array[(j >> 1) >> 3] >> ((j >> 1) & 7)) & 1;
            }

            while (x > 0) {   //Поднимаемся полевой ветке обратно до самого вверха
                WeakHeapMerge(bit_array, 0, x);
                x >>= 1;
            }
        }
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
    cout << "Через пробел введите элементы массива:\n";
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
