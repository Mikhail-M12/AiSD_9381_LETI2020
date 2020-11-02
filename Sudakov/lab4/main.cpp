#include <bits/stdc++.h>

#ifdef __linux__
    #define FIRST_COLOR   "\033[1m\033[31m"
    #define FAILURE_COLOR "\033[1m\033[31m"
    #define SUCCESS_COLOR "\033[1m\033[32m"
    #define SECOND_COLOR  "\033[1m\033[32m"
    #define INFO_COLOR    "\033[1m\033[36m"
    #define MERGED_COLOR  "\033[1m\033[33m"
    #define ITERATION_COLOR    "\033[1m\033[35m"

#elif __WIN32
    #define FIRST_COLOR   ""
    #define FAILURE_COLOR ""
    #define SUCCESS_COLOR ""
    #define SECOND_COLOR  ""
    #define INFO_COLOR    ""
    #define MERGED_COLOR  ""
    #define ITERATION_COLOR    ""
#endif

#define inf 1e5


//16. Сортировка массивов слиянием – естественное слияние.

using namespace std;


/**
 * Функция вывода шаблонного вектора
 * @tparam T тип данных
 * @param vec вектор для вывода
 * @param start оптимальный старт
 * @param end оптимальный конец
 */
template<typename T>
void printArray(vector<T>vec, int start = 0, int end = inf) {
    int startInd = max(start, 0);
    int endInd = min(end, int(vec.size()));
    for(int i = startInd; i < endInd; i++) cout << vec[i] << " ";
}


/**
 * Функция вывода некоторой промежуточной информации
 * @tparam T тип данных
 * @param arr вектор, куда происходит слияние
 * @param start стартовая позиция для записи
 * @param first  первая серия для слияния
 * @param second  вторая серия для слияния
 */
template<typename T>
void printInfo(vector<T> &arr, int start, vector<T>first, vector<T>second) {
    cout << FIRST_COLOR << "\nFirst series : ";
    printArray(first);
    cout << "\n";
    cout << SECOND_COLOR << "Second series : ";
    printArray(second);
    cout << "\n";
    cout << INFO_COLOR << "Array before merging :: ";
    printArray(arr, 0, start);
    cout << FIRST_COLOR;
    printArray(first);
    cout << SECOND_COLOR;
    printArray(second);
    cout << INFO_COLOR;
    printArray(arr, start + first.size() + second.size(), arr.size());
    cout << MERGED_COLOR << "\nmerged : ";
}


/**
 * Функция слияния двух серий в исходный массив
 * @tparam T тип данных
 * @param arr вектор, куда происходит слияние
 * @param start стартовая позиция для записи
 * @param first  первая серия для слияния
 * @param second  вторая серия для слияния
 */
template<typename T>
void merge(vector<T> &arr, int start, vector<T>first, vector<T>second) {
    printInfo(arr, start, first, second);
    int pos1(0), pos2(0), n1 = first.size(), n2 = second.size();
    while(pos1 + pos2 < n1 + n2) {
        if(pos2 >= n2 || (pos1 < n1 && first[pos1] < second[pos2])) {
            arr[start + pos1 + pos2] = first[pos1];
            cout << first[pos1] << " ";
            pos1++;
        }
        else {
            arr[start + pos1 + pos2] = second[pos2];
            cout << second[pos2] << " ";
            pos2++;
        }
    }
    cout << "\n" <<INFO_COLOR << "Array after merging :: ";
    printArray(arr);
    cout << "\n\n";
}


/**
 * Функция сортировки массивов слиянием – естественное слияние.
 * @tparam T тип данных
 * @param arr вектор для сортировки
 */
template<typename T>
void naturalMergeSort(vector<T> &arr){
    int n = arr.size();
    int cnt = 1;
    while(true)  {
        int start1 = 1, start2 = -1, end1, end2 = 0;
        vector<T>s1, s2;
        cout << ITERATION_COLOR << "======================================\n";
        cout << "Iteration " << cnt++ << INFO_COLOR << "\nArray :: ";
        printArray(arr);
        cout << "\n";
        while(true) {
            s1.clear(); s2.clear();
            start1 = end2; end1 = start1;

            s1.push_back(arr[end1++]); // первая серия
            while(end1 < n && arr[end1] >= arr[end1-1]){
                s1.push_back(arr[end1++]);
            }

            if(end1 == n)
                break;

            start2 = end1; end2 = start2;

            s2.push_back(arr[end2++]); // вторая серия
            while(end2 < n && arr[end2] >= arr[end2-1]) {
                s2.push_back(arr[end2++]);
            }

            merge(arr, start1, s1, s2);

            if(end2  == n) break;
        }
        cout << ITERATION_COLOR << "======================================\n";
        if(start1 == 0 && end1 == n) break;
    }
}


/**
 * Программа запуска и сравнения двух сортировок
 * @tparam T тип вектора для сортировки
 * @param data исходные данные(вектор)
 */
template<typename T>
void solution(vector<T> data) {
    vector<T>stdSortData = data;
    naturalMergeSort(data);
    cout << INFO_COLOR <<  "\n\nData sorted by " <<  ITERATION_COLOR << "naturalMergeSort :: " << MERGED_COLOR;
    printArray(data);
    cout << INFO_COLOR << "\nData sorted by" << ITERATION_COLOR << " std::sort :: " << MERGED_COLOR;
    sort(stdSortData.begin(), stdSortData.end());
    printArray(stdSortData);
    if(data == stdSortData) {
        cout << SUCCESS_COLOR << "\nArrays are equal\n";
    }
    else {
        cout << FAILURE_COLOR << "\nArrays are not equal\n";
    }
    assert(data == stdSortData);
}


/**
 * Функция вывода шаблонного вектора
 * @tparam T Тип элементов вектора
 * @param arr собственно вектор для вывода
 */
template<typename T>
void readArray(vector<T> &arr) {
    for(auto &it : arr) cin >> it;
}


int main() {
    int type;
    cout << "Введите тип массива :\n"
            "(1) Integer\n"
            "(2) Float\n"
            "(3) String\n"
            "(4) Char\n";
    cin >> type;
    vector<int>iv;
    vector<float>fv;
    vector<string>sv;
    vector<char>cv;
    int n;
    cout << "Введите, пожалуйста, количество элементов в массиве\n";
    cin >> n;
    int f;
    cout << "Массив из консоли или из файла (0/1)?\n";
    cin >> f;
    if (f == 1) {
        freopen("input.txt", "r", stdin);
        //Если работать на windows, то можно использовать вывод в файл. Если нет, то в файл
        //будет выводить абракадабра с цветами.
//        freopen("output.txt", "w", stdout);
    }
    else cout << "Введите массив :\n";
    switch (type) {
        case 1:
            iv = vector<int>(n);
            readArray(iv);
            solution(iv);
            break;
        case 2:
            fv = vector<float>(n);
            readArray(fv);
            solution(fv);
            break;
        case 3:
            sv = vector<string>(n);
            readArray(sv);
            solution(sv);
            break;
        case 4:
            cv = vector<char>(n);
            readArray(cv);
            solution(cv);
            break;
    }
    return 0;
}
