#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
using  namespace std;

template<typename T>
struct array_list
{
    T* array;  //массив чисел
    int capacity;//размерность массива array
    int count; //количество непустых элементов массива array

    void resize(int new_capacity);
    array_list(int start_capacity=1);
    T& operator[] (int index);

    void push_back(int element);
    int size();
};
template<typename T>
void array_list<T>::resize(int new_capacity) //изменение размерности массива
{
    T *arr = new T[count];
    for (int i = 0; i < count; ++i)
    {
        arr[i] = array[i];  //переписываем значения массива в вспомогательный
    }
    delete [] array;         //удаляем старый массив
    array = new T[new_capacity]; //выделяем массив нужного размера
    for (int i = 0 ; i < count; ++i)
    {
        array[i] = arr[i];    //переписываем значения в нужный массив
    }
    delete [] arr;        //очищаем память под вспомогательный массив
    capacity = new_capacity;    //изменяем поле класса - размерность массива
}
template<typename T>
array_list<T>::array_list(int start_capacity)  //создание списка чисел
{
    capacity = start_capacity;
    count = 0;
    array = new T[capacity];
}
template<typename T>
T& array_list<T>::operator[] (int index)  //функция позволяет обращаться к элементам поля array через объект типа array_list по индексу
{
    return array[index];
}

template<typename T>
void array_list<T>::push_back(int element) //добавление элемента в конец массива
{
    if (capacity == count)
    {
        resize(count + 8);  //изменяем размер массива
    }
    array[count] = element;  //вставляем элемент
    count++;
}
template<typename T>
int array_list<T>::size() //получение длины списка
{
    return count;
}


template<typename T>
string log(array_list<T> &list, int min, int max, int pivot, int depth) //функция для вывода промежуточного результата
{
    string s = ""; //строка для вывода промежуточных данных
    for (int i = 0; i < list.size(); i++)
    {
        s += to_string(list[i]) + ' ';//вывод элементов
    }
    s += '\n';
    s += "\tиндекс левого элемента: " + to_string(min) + "\n\tиндекс правого элемента: " + to_string(max) + "\n\tопорный элемент: " + to_string(pivot) + "\n\tглубина рекурсии: " + to_string(depth) +"\n\n"; //добавляем к строке промежуточные сведения
    return s;
}

template<typename T>
void qsort3way(string& s, array_list<T>& list, int l, int r, int depth) //функция трёхпутевой сортировки
{
    if (l >= r)
    {
        return;
    }
    int lt = l; // lt - индекс, по которому запишется очередное значение, меньше опорного
    int gt = r;  //gt - индекс, по которому запишется очередное значение, больше опорного
    int pivot = list[l + (rand() % (r - l))];//опорный элемент генерируется рандомным образом
    int i = l; //проходим по массиву слева направо
    while (i <= gt)
    {
        if (list[i] < pivot)  //если значение меньше чем опорный элемент, записываем его по индексу lt, lt смещаем вправо
        {
            int t = list[lt];
            list[lt] = list[i];
            list[i] = t;
            lt += 1;
            i += 1;
        }
        else if (list[i] > pivot)  //если значение больше чем опорный элемент, записываем его по индексу gt, gt смещаем влево
        {
            int t = list[gt];
            list[gt] = list[i];
            list[i] = t;
            gt -= 1;
        }
        else
        {
            i += 1;
        }
    }
    s += log(list, l, r, pivot, depth);
    qsort3way(s, list, l, lt - 1, depth + 1);  //рекурсивный вызов для левой части
    qsort3way(s, list, gt + 1, r, depth + 1);  //рекурсивный вызов для правой части
}



template<typename T>
std::string print_list(array_list<T>& list)  //вывод итогового результата
{
    string s;
    for (int i = 0; i < list.size(); i++)
    {
        s += std::to_string(list[i]) + " ";
    }
    return s;
}

int main() {
    string input;
    ifstream file;
    string filename;
    cout << "Введите путь до файла\n";
    cin >> filename;
    file.open(filename); //открываем файл
    if (!file.is_open()){
        cout << "Файл не может быть открыт!\n";
    }
    getline(file,input); //считываем строку из файла
    file.close();            //закрываем файл
    array_list<int> list = array_list<int>();
    int elem;
    istringstream str(input);
    while(str >> elem) list.push_back(elem);
    cout << print_list(list);
    cout << endl << "Работа алгоритма:" << endl;
    string s;
    qsort3way(s, list, 0, list.size() - 1,0);
    cout << "Логгирование" << endl << s << endl << "Конец промежутоных значений" << endl;
    cout << endl << "Ответ: " << endl << print_list(list) << endl;
    return 0;
}
