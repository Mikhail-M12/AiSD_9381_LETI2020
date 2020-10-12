#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static int h = 0;   //отвечает за количество замен

template <typename T> void printArr(T* arr, int size, int f, int l){
    for (int i = 0; i < size; i++){
        if (i == f || i == l)
            cout << "\033[34m" << arr[i] << "\033[0m ";  //цветной вывод элементов, которые меняются местами
        else
            cout << arr[i] << ' ';
    }
    cout << '\n';
}

template <typename T> void insert(T* array, int step, int size){
    for (int i = step; i < size; i++) {
        for (int j = i - step; j >= 0 && array[j] > array[j+step]; j -= step) { //сортировка вставками с учетом инкременты
            T x = array[j];
            h++;       //количество замен увеличивается
            cout << "   ЗАМЕНА № \033[32m" << h << "\033[0m\n";
            cout << "\033[31m Change " << array[j] << " and " << array[j+step] << "  \033[0m\n";
            array[j] = array[j + step];
            array[j + step] = x;
            printArr(array, size, j+step, j); //печать измененного массива
        }
    }
}

template <typename T> void shellSortSedgwick(T* array, int size) {
    int steps[50];  //массив для хранения инкремент(step)
    steps[0] = 1;
    int q = 1;
    while (steps[q - 1] * 3 < size) { //заполняем массив, пока текущая инкремента хотя бы в 3 раза
                                    // меньше количества элементов в массиве
        if (q % 2 == 0)
            steps[q] = 9 * (1 << q) - 9 * (1 << (q / 2)) + 1;  //1 << q = pow(2,q)
        else
            steps[q] = 8 * (1 << q) - 6 * (1 << ((q + 1) / 2)) + 1;
        q++;
    }
    q--;
    cout << "The array of increments:\n";
    printArr(steps, q + 1, -1, -1);  //вывод массива инкремент без подсветки
    while (q >= 0) {
        int step = steps[q--];  //извлекаем очередную инкременту
        cout << "       STEP = " << step << '\n';
        insert(array,step,size);
    }
}

template <typename T> void shell(T* array, int size) {
    for (int step = size/2; step > 0; step /= 2) { //первоначальная последовательность Шелла
                                        //каждый раз инкремента уменьшается в 2 раза
        cout << "       STEP = " << step << '\n';
        insert(array,step,size);
    }
}

template <typename T> int check(vector<T> vec, T* array, int size){
    for (int i = 0; i != size; i++)
        if (vec[i]!= array[i])
            return 0;
        return 1;
}

template <typename T> void typeSort(T* array, int size){
    cout << "Choose the way of sorting:\n1. Using the formula by Sedgwick. \n2. Using division by 2.\n";
    int type = 0;
    cin >> type;
    switch(type){
        case 1:
            shellSortSedgwick(array, size); //сортировка по формуле Седжвика
            break;
        case 2:
            shell(array,size);  //стандартная сортировка Шелла
            break;
        default:
            cout << "You need to choose 1 or 2. Try again.\n";
            exit(1);
    }
}

int main() {
    int size = 0;  //размер массива
    int type = 0; //тип ввода и тип сортировки Шелла
    int* array;    //массив указателей на int. Для тестирования можно использовать другой тип данных
    cout << "Choose the way:\n1. Reading from console.\n2. Reading from file." << "\n";
    cin >> type;
    switch(type){
        case 1: {
            cout << "Please enter size of your array:" << "\n";
            cin >> size;
            array = new int[size];
            cout << "Enter elements of array one by one:\n";
            for (int i = 0; i != size; i++) {       //заполнение массива с консоли
                cin >> array[i];
            }
            break;
        }
        case 2: {
            ifstream file;
            string name;
            cout << "Please enter the directory of file:" << "\n";
            cin >> name;
            file.open(name);        //открываем файл по введенной директории
            if (!file.is_open()) {
                cout << "Can't open the file!\n";
                exit(1);
            }
            file >> size;
            array = new int[size];
            for (int i = 0; i != size; i++) //заполнение массива
                file >> array[i];
            break;
        }
        default:
            cout << "You need to choose 1 or 2. Try again.\n";
            return 0;
    }
    cout << "YOUR INPUT: ";
    printArr(array,size,-1,-1); //вывод введенного массива

    cout << "TEST USING STD::SORT: ";
    vector<int> vec (array, array+size);
    sort (vec.begin(), vec.end());
    for (int i = 0; i < size; i++) {
        cout << vec[i] << " ";
    }
    cout << '\n';
    typeSort(array, size);
    cout << "\nИТОГ:\n";
    printArr(array, size,-1,-1); //вывод отсортированного массива
    if (check(vec,array,size))
        cout << "Results of std::sort and Shell sorting are SAME. Test passed.";
    else
        cout << "Results of std::sort and Shell sorting are DIFFERENT. Test failed.";
    delete [] array;    //очищение памяти, занятой массивом
    return 0;
}
