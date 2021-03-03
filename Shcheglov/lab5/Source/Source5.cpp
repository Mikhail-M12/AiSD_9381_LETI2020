#include<iostream>
#include<cstdlib>
#include<cmath>
#include<locale>
#include<fstream>

using namespace std;

double logarifm(int a, int b) //вычисляем логарифм по основанию a от
{
    return log(b) / log(a);
}


typedef struct elem { //структура для записи элементов массива типа число-бит
    int number;
    int bit;
} elem;

class WeakHeap { //класс слабой кучи
    elem* heap; // массив элементов кучи
    int start_of_heap = 0;
    int end_of_heap = 0;
    int size_of_heap;
public:
    WeakHeap(int size) { //конструктор для создания новой слабой кучи
        size_of_heap = size;
        heap = new elem[size_of_heap]; //выделяем память под массив элементов кучи
    }
    void print_heap();
    void push(elem x);
    void pop();
    ~WeakHeap() {//деструктор для освобождения памяти массива элементов кучи
        delete[] heap;
    }
};

//методы класса WeakHeap
void WeakHeap::print_heap() {
    ofstream fout;
    fout.open("result.txt");
    cout << heap[0].number << "\n";
    fout << heap[0].number << "\n";
    int depth = (int)logarifm(2, size_of_heap);//вычисляем глубину дерева
    int k = 0;
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < pow(2, i); j++) {
            cout << heap[k + 1].number << "  ";
            fout << heap[k + 1].number << "  ";
            k++;
        }
        cout << "\n";
        fout << "\n";
    }
    fout.close();
}

void WeakHeap::push(elem x) { //функция помещения элемента в кучу
    heap[end_of_heap].number = x.number;
    heap[end_of_heap].bit = x.bit;
    end_of_heap++; //так как теперь в куче на один элемент больше
}

void WeakHeap::pop(){   //функуция извлечения элемента из кучи
    if (start_of_heap == end_of_heap) {
        cout << "куча пустая\n";
        return;
    }
    start_of_heap++;
}

int main() {
    setlocale(LC_ALL, "rus"); //cмена кодировки консоли
    cout << "Введите количество пар:\n";
    int count;
    cin >> count; // считываем количество пар
    elem* bit_array = new elem[count]; // выделяем динамическую память под массив бит
    cout << "Введите пары в формате число бит:\n";
    for (int i = 0; i < count; i++) { //считываем массив, который является слабой кучей
        cin >> bit_array[i].number >> bit_array[i].bit;
    }

    WeakHeap result_heap(count);
    result_heap.push(bit_array[0]);
    result_heap.push(bit_array[1]);

    int count_of_bit = count / 2; // количество элементов с не фиктивным дополнительным битом
    for (int i = 1; i < count_of_bit; i++) {//записываем элементы в кучу в порядке, удобном для вывода на экран
        result_heap.push(bit_array[2 * i + bit_array[i].bit]); // Левый потомок: 2 * i + BIT[i]
        result_heap.push(bit_array[2 * i + 1 - bit_array[i].bit]);// Правый потомок: 2 * i + 1 - BIT[i]
    }

    result_heap.print_heap();//выводим слабую кучу на экран
    delete[] bit_array; //освобождаем память, чтобы избежать утечки
    return 0;
}
