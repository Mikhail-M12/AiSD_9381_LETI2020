#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
using  namespace std;


struct array_list
{
    int* array;  //массив чисел
    int capacity;//размерность массива array
    int count; //количество непустых элементов массива array

    void resize(int new_capacity);
    array_list(int start_capacity=1);
    int& operator[] (int index);

    void push_back(int element);
    int size();
};


void array_list::resize(int new_capacity) //изменение размерности массива
{
    int *arr = new int[count];
    for (int i = 0; i < count; ++i)
    {
        arr[i] = array[i];  //переписываем значения массива в вспомогательный
    }
    delete [] array;         //удаляем старый массив
    array = new int[new_capacity]; //выделяем массив нужного размера
    for (int i = 0 ; i < count; ++i)
    {
        array[i] = arr[i];    //переписываем значения в нужный массив
    }
    delete [] arr;        //очищаем память под вспомогательный массив
    capacity = new_capacity;    //изменяем поле класса - размерность массива
}

array_list::array_list(int start_capacity)  //создание списка чисел
{
    capacity = start_capacity;
    count = 0;
    array = new int[capacity];
}

int& array_list::operator[] (int index)  //функция позволяет обращаться к элементам поля array через объект типа array_list по индексу
{
    return array[index];
}


void array_list::push_back(int element) //добавление элемента в конец массива
{
    if (capacity == count)
    {
        resize(count + 8);  //изменяем размер массива
    }
    array[count] = element;  //вставляем элемент
    count++;
}

int array_list::size() //получение длины списка
{
    return count;
}



string log(array_list &list, int min, int max, int pivot, int depth) //функция для вывода промежуточного результата
{
    string s = ""; //строка для вывода промежуточных данных
    for (int i = 0; i < list.size(); i++)
    {
        s += to_string(list[i]) + ' ';//добавлене элементов в строку
    }
    s += '\n';
    s += " l:" + to_string(min) + " r:" + to_string(max) + " pivot: " + to_string(pivot) + " depth: " + to_string(depth) +"\n\n"; //добавляем к строке промежуточные сведения
    return s;
}


void qsort3way(string& s, array_list& list, int l, int r, int depth) //функция трёхпутевой сортировки
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




std::string print_list(array_list& list)  //вывод итогового результата
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
    array_list list = array_list();
    int elem;
    istringstream str(input);
    while(str >> elem) list.push_back(elem);
    cout << print_list(list);
    cout << endl << "Executing algorithm..." << endl;
    string s;            //строка для вывода промежуточных значений
    qsort3way(s, list, 0, list.size() - 1,0);
    cout << "---LOG---" << endl << s << endl << "---END---" << endl;
    cout << endl << "Result: " << endl << print_list(list) << endl;
    return 0;
}
