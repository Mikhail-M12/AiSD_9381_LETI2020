#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Функции вывода информации-------------------------------------------------------

// Функция печати объекта в поток
template <class T>
void print(T obj, ofstream* fout) {
    if (fout) *fout << obj;
    else cout << obj;
}
// Функция печати отступов
void printStep(int step, ofstream* fout){
    for (int i = 0; i < step; i++) print<string>("\t", fout);
}
// Объявление функции печати массива
void print_arr(int* arr, size_t n, ofstream* fout);
// Функция печати подмассивов слияния
void printIntermediaArrays(int* arr_1, size_t count_1, int cur_1, int* arr_2, size_t count_2, int cur_2, int* result_arr, int res_cur, int step, ofstream* fout){
    printStep(step, fout);
    print<string>("Первый массив: ", fout);
    print_arr(arr_1 + cur_1, count_1 - cur_1, fout);
    print<string>("\n", fout);

    printStep(step, fout);
    print<string>("Второй массив: ", fout);
    print_arr(arr_2 + cur_2, count_2 - cur_2, fout);
    print<string>("\n", fout);

    printStep(step, fout);
    print<string>("Результирующий массив: ", fout);
    print_arr(result_arr, res_cur, fout);
    print<string>("\n", fout);
    printStep(step, fout);
    print<string>("--\n", fout);
}
// Функция печати результата программы
void printResult(int* arr, int* arrFor_stdSort, size_t count, bool cmp, ofstream* p_fout){
    print<string>("\nРезультат сортировки слиянием: ", p_fout);
    print_arr(arr, count, p_fout);
    print<string>("\n", p_fout);

    print<string>("Результат стандартной сортировки std::sort(): ", p_fout);
    print_arr(arrFor_stdSort, count, p_fout);
    print<string>("\n", p_fout);

    print<string>("Результаты стандартной сортировки std::sort() и сортировки слиянием: ", p_fout);
    if (cmp) print<string>("совпадают\n", p_fout);
    else print<string>("не совпадают\n", p_fout);
}

// Функции ввода, вывода, копирования и сравнения массивов-------------------------------------------------

// Функция считывания массива из потока
size_t input_arr(int* &arr, ifstream* fin){
    size_t n = 0;
    if (fin) *fin >> n;
    else {
        cout << "Введите число элементов массива: ";
        cin >> n;
        cout << "Введите " << n << " целых чисел по порядку через пробел (массив): ";
    }
    arr = new int[n];
    for (int i = 0; i < n; i++)
        if (fin) {
            arr[i] = 0;
            *fin >> arr[i];
        }
        else cin >> arr[i];
    return n;
}
// Определение функции печати массива в поток
void print_arr(int* arr, size_t n, ofstream* fout){
    print('{', fout);
    if (n > 0) print(arr[0], fout);
    for (int i = 1; i < n; i++){
        print<string>(", ", fout);
        print(arr[i], fout);
    }
    print('}', fout);
}
// Функция копирования массива
int* copy_arr(int* arr, size_t n){
    int* c_arr = new int[n];
    for (int i = 0; i < n; i++)
        c_arr[i] = arr[i];
    return c_arr;
}
// Функция сравнения двух массивов одинковой длины (проверки на идентичность)
bool cmp_arr(int* arr1, int* arr2, size_t n){
    for (int i = 0; i < n; i++){
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

// Функция сортировки слиянием-------------------------------------------------
void merge_sort(int* arr, size_t count, int step, ofstream* fout){
    printStep(step, fout);
    print<string>("Функция merge_sort() для массива: ", fout);
    print_arr(arr, count, fout);
    print<string>(" вызвана\n", fout);

    if (count == 0 || count == 1){      // Проверка на пустоту или одноэлементность массива
        printStep(step, fout);
        print<string>("В данном массиве ", fout);
        print(count, fout);
        print<string>(" элементов, следовательно массив отсортирован\n", fout);
        printStep(step, fout);
        print<string>("Функция merge_sort() для массива: ", fout);
        print_arr(arr, count, fout);
        print<string>(" завершена\n", fout);
        return;                         // Досрочное завершение функции в случае сразу отсортированного пустого или одноэлементного массива
    }
    // Рассчет параметров разбиения
    int* arr_1 = arr;                   // Адрес первого подмассива
    size_t count_1 = (int)(count / 2);  // Длина первого подмассива
    int* arr_2 = arr + count_1;         // Адрес второго подмассива
    size_t count_2 = count - count_1;   // Длинна второго подмассива

    printStep(step, fout);
    print<string>("Исходный массив разбивается на два подмассива: ", fout);
    print_arr(arr_1, count_1, fout);
    print<string>(" и ", fout);         // Печать подмассивов
    print_arr(arr_2, count_2, fout);
    print<string>("\n", fout);

    printStep(step, fout);
    print<string>("Сортировка первого массива:\n", fout);
    merge_sort(arr_1, count_1, step + 1, fout);             // Сортировка первого подмассива слиянием
    printStep(step, fout);
    print<string>("Сортировка второго массива:\n", fout);
    merge_sort(arr_2, count_2, step + 1, fout);             // Сортировка второго подмассива слиянием

    int *result_arr = new int[count];                       // Создание вспомагательного результирующего массива

    printStep(step, fout);
    print<string>("Обрабатываются два отсортированных массива: ", fout);
    print_arr(arr_1, count_1, fout);
    print<string>(" и ", fout);
    print_arr(arr_2, count_2, fout);
    print<string>(" таким образом, что в результирующий массив на каждом шаге записывается меньший из их первых элементов:\n", fout);
    // Задание начальных значений текущих индексов подмассивов слияния
    int cur_1 = 0;
    int cur_2 = 0;
    printStep(step, fout);
    print<string>("--\n", fout);
    printIntermediaArrays(arr_1, count_1, cur_1, arr_2, count_2, cur_2, result_arr, 0, step, fout);
    for (int i = 0; i < count; i++){
        if (cur_1 < count_1 && cur_2 < count_2){
            if (arr_1[cur_1] < arr_2[cur_2]){       // Выбор меньшего элемента из текущих в подмассивах
                result_arr[i] = arr_1[cur_1];       // Занос меньшего элемента в результирующий массив
                cur_1++;                            // Сдвиг текущего индекса
            } else {
                result_arr[i] = arr_2[cur_2];       // Занос меньшего элемента в результирующий массив
                cur_2++;                            // Сдвиг текущего индекса
            }
            printIntermediaArrays(arr_1, count_1, cur_1, arr_2, count_2, cur_2, result_arr, i + 1, step, fout); // Печать состояний подмассивов
        } else {                                    // Прикрепление остатка подмассива большей длинны к результирующему массиву
            if (cur_1 == count_1){
                result_arr[i] = arr_2[cur_2];
                cur_2++;
            }
            else {
                result_arr[i] = arr_1[cur_1];
                cur_1++;
            }
        }
    }

    printStep(step, fout);
    print<string>("Оставшаяся часть массива присоединяется к результату:\n", fout);
    printStep(step, fout);
    print<string>("Результирующий массив: ", fout); // Вывод результирующего отсортированного массива
    print_arr(result_arr, count, fout);
    print<string>("\n", fout);
    printStep(step, fout);
    print<string>("--\n", fout);

    for (int i = 0; i < count; i++)                 // Перенос элементов отсортированного массива в исходный
        arr[i] = result_arr[i];
    delete[] result_arr;                            // Очистка памяти под вспомагательный массив

    printStep(step, fout);
    print<string>("Массив: ", fout);
    print_arr(arr, count, fout);
    print<string>(" отсортирован. Функция merge_sort() для него завершена\n", fout);
}
// ----------------------------------------------------------------------------

// Главная функция
int main(int argc, char* argv[]){
    if (argc > 3){
        cout << "Слишком много аргументов программы\n";
        return 1;
    }

    ifstream fin;
    ifstream* p_fin = nullptr;
    ofstream fout;
    ofstream* p_fout = nullptr;
    if (argc > 1){
        if (argc == 3){
            fin.open(argv[1]);
            if (!fin){
                cout << "Ошибка открытия файла: " << argv[1] << endl;
                return 1;
            }
            p_fin = &fin;
        }

        fout.open(argv[argc - 1]);
        if (!fout){
            cout << "Ошибка открытия файла: " << argv[argc - 1] << endl;
            fin.close();
            return 1;
        }
        p_fout = &fout;
    }

    int* arr;
    size_t count = input_arr(arr, p_fin);

    print<string>("Исходный массив: ", p_fout);
    print_arr(arr, count, p_fout);
    print<string>("\n", p_fout);

    if (p_fout){
        print<string>("Исходный массив: ", nullptr);
        print_arr(arr, count, nullptr);
    }

    int* arrFor_stdSort = copy_arr(arr, count);
    std::sort(arrFor_stdSort, arrFor_stdSort + count);

    print<string>("\nПромежуточные данные:\n", p_fout);
    merge_sort(arr, count, 0, p_fout);

    bool equalityArrs = cmp_arr(arr, arrFor_stdSort, count);
    printResult(arr, arrFor_stdSort, count, equalityArrs, p_fout);
    if (p_fout) { 
        printResult(arr, arrFor_stdSort, count, equalityArrs, nullptr);
        cout << "Промежуточные данные записаны в файл: " << argv[argc - 1] << "\n";
    }

    delete[] arr;
    delete[] arrFor_stdSort;
    fin.close();
    fout.close();
    return 0;
}