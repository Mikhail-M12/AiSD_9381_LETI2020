#include <iostream>
#include <cstdlib>
#include <ostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;
struct Array{
    int * array;
    int size;
};
void printArray(int *arr, int &size, ostream &out); // функция печати массива на экран
void bubbleSortOptimized(int *array, int &arrSize, ostream &out); // оптимизированная сортировка пузырьком
void oddEvenSorting(int *array, int &arrSize, ostream &out); // сортировка чёт-нечёт
bool isCorrect(string &arrSeq); // проверка на корректность введённой строки
Array * copyArray(Array * obj); // функция копирования массива
Array *getArrayFromString(string &arrSeq); // получение массива из строки
void destroy(Array * obj); // удаление экземпляра структуры Array
bool isEqual(Array * first, Array * second); // проверка массивов на равенство

namespace file{
    ifstream inputFile;
    ofstream outputFile;
}

int main(){
    string path; // путь до файла ввода
    string arraySequence; // вводимая строка-массив
    stringstream myStream; // вспомогательный поток
    char inputFlag; // управляющий флаг для ввода
    char sortFlag; // управляющий флаг для сортировки
    char outputFlag; // управляющий флаг для вывода
    int size; // количество элементов массива
    cout << "Первый введённый Вами символ - выбор ввода, второй - выбор вывода, третий - выбор алгоритма сортировки\n"
            "1) 0 - ввод с консоли\n   1 - ввод с файла\n"
            "2) 0 - вывод в консоль\n   1 - вывод в файл\n"
            "3) B - оптимизированная сортировка пузырьком (английская буква)\n   "
            "E - сортировка чёт-нечёт (английская буква)\n   "
            "Примеры начального ввода: 00E, 01B, 10E, 11B\n"
            "\n!Порядок ввода!\nЧисла должны быть введены строго через один пробел.\nПосле того, как был введён последний элемент, пробелы вводить нельзя\n";
    cin >> inputFlag;
    cin >> outputFlag;
    cin >> sortFlag;
    if((inputFlag != '0' && inputFlag != '1') || (sortFlag != 'B' && sortFlag != 'E') || (outputFlag != '1' && outputFlag != '0'))
    {
        cerr << "Некорректный ввод\n";
        return 0;
    }

    switch(inputFlag){ // определение, откуда будет производиться считывание
        case '0':
            cout << "Введите через пробел:\n";
            cin.ignore();
            getline( cin, arraySequence); // считывание строки
            break;
        case '1':
            cout << "Введите путь до входного файла:\n";
            cin >> path;
            file::inputFile.open(path); // открытие потока вывода в файл
            if(!file::inputFile.is_open()){
                cout << "Невозможно открыть файл на чтение\n";
                return 0;
            }
            getline(file::inputFile, arraySequence);
            file::inputFile.close();
            break;
        default:
            cerr << "Неизвестная ошибка\n";
            exit(1);
    }

    if(!isCorrect(arraySequence)){ //проверка строки на корректность
        cerr << "Некорректный ввод\n";
        return 0;
    }

    if(outputFlag == '1'){
        cout << "Введите путь до выходного файла:\n";
        cin >> path;
        file::outputFile.open(path);
    }
    ostream & out = outputFlag == '0' ? cout : file::outputFile;


    Array * arrayObject  = getArrayFromString(arraySequence); // пребразование строки в массив
    if(!arrayObject) {
        out << "Введена пустая строка. Сортировать нечего\n";
        return 0;
    }
    Array * copy = copyArray(arrayObject); // создание копии для проверки библиотечной функцией std::sort() (нужно в тестировании)
    switch(sortFlag){
       case 'E':
            oddEvenSorting(arrayObject->array, arrayObject->size, out);
            break;
       case 'B':
            bubbleSortOptimized(arrayObject->array, arrayObject->size, out);
            break;
            default:
            cerr << "Неизвестная ошибка\n";
            exit(1);
        }
        out << "\nОтсортированный массив: ";
        printArray(arrayObject->array, arrayObject->size, out); // вывод массива на экран

        out << "\nВыполним проверку библиотечной функцией std::sort()\n";
        out << "Исходный массив: ";
        printArray(copy->array, copy->size, out);
        out << "\n";
        std::sort(copy->array, copy->array + copy->size); // сортировка библиотечной функцией
        out << "Массив после обработки std::sort(): ";
        printArray(copy->array, copy->size, out);
        out << "\n";
        if(isEqual(arrayObject, copy))
            out << "Массивы идентичны.\n";
        else
            out << "Массивы НЕ идентичны\n";

        destroy(arrayObject); // освобождение памяти
        destroy(copy); // освобождение памяти

    return 0;
}

void bubbleSortOptimized(int *array, int &arrSize, ostream &out) {
    out << "Запуск оптимизированной сортировки пузырьком.\n";
    int i = 0; // вспомогательный счётчик, который нужен для оптимизированной версии алгоритма
    bool flag = true; // флаг, по которому устанавливается, завершена ли сортировка
    out << "Состояние массива: ";
    printArray(array, arrSize, out);
    out << "\n\n";
    if(arrSize == 1){
        out << "Массив состоит из одного элемента. Конец сортировки\n";
        return;
    }
    while(flag){  // цикл, зависящий от флага, который устанавливается в 1 если во внутреннем цикле произошёл хоть один обмен
        flag = false;

        for(int j = 0; j < arrSize - i - 1; j++) {
            if (array[j] > array[j + 1]) { // условие обмена
                std::swap(array[j], array[j+1]); // элементы меняются местами
                flag = true;
                out << "! Элементы (" << array[j] << ", индекс " << j << ") и " << "(" << array[j+1] << ", индекс " << j+1 <<") меняются местами\n";
                out << "\nСостояние массива: ";
                printArray(array, arrSize, out);
                out << "\n\n";
            }
            else{
                out << "Обмен элементов (" << array[j] << ", индекс " << j << ") и " << "(" << array[j+1] << ", индекс " << j+1 <<") не требуется\n";
            }
        }
        i++;
        if(!flag){
            out << "При текущем обходе не произошло ни одного обмена. (Условие конца сортировки)\n";
        }
    }
    out << "Сортировка закончена.\n";
}

void oddEvenSorting(int *array, int &arrSize, ostream &out) {
    // две переменные ниже необходимы для определения конца сортировки и служат для оптимизации алгоритма
    int checkChanges = 0; // переменная, фиксирующая количество обменов
    int delta = 0; // переменная, фиксирующая количество итераций
    out << "Запуск сортировки чёт-нечёт\n";
    out << "Состояние массива: ";
    printArray(array, arrSize, out);
    out << "\n\n";
    if(arrSize == 1){
        out << "Массив состоит из одного элемента. Конец сортировки";
        return;
    }
    char even = true;
    while(true) {
        switch(even){
            case true:
                out << "\nCocтояние ЧЁТ-нечёт:\n";
                break;
            case false:
                out << "\nCocтояние НЕЧЁТ-чёт:\n";
                break;
            default:
                break;
        }
        for (int j = even ? 0 : 1; j < arrSize-1; j += 2) { // состояния ЧЁТ-нечёт И НЕЧЁТ-чёт чередуются на каждой итерации внешнего цикла
            if (array[j] > array[j + 1]) { // условие обмена
                out << "! Элементы (" << array[j] << ", индекс " << j << ") и " << "(" << array[j+1] << ", индекс " << j+1 <<") меняются местами\n";
                std::swap(array[j], array[j+1]); // элементы меняются местами
                out << "Состояние массива: ";
                printArray(array, arrSize, out);
                out << "\n";
                checkChanges++;
            }
            else
                out << "Обмен элементов (" << array[j] << ", индекс " << j << ") и " << "(" << array[j+1] << ", индекс " << j+1 <<") не требуется\n";

        }

        delta++;

        if(delta == 2 && checkChanges == 0){ // если после подряд двух проходов по массиву подряд (ЧЁТ-нечёт и НЕЧЁТ-чёт) не произошло ни одного обмена, следует завершить сортировку
            out << "\nПосле двух проходов по массиву подряд (ЧЁТ-нечёт и НЕЧЁТ-чёт) не произошло ни одного обмена (Условие конца сортировки)\n";
            break;
        }
        else if(delta == 2){ /*важно в случае продолжения сортировки обнулить переменные-контроллеры, чтобы можно при следующих двух обходах
 * можно было понять, требуется ли продожать внешний цикл */
            delta = 0;
            checkChanges = 0;
        }
        if(even)
            even = false;
        else
            even = true;

    }
    out << "Сортировка закончена.\n";
}

bool isEqual(Array * first, Array * second){
    if(first == nullptr && second == nullptr) // если оба нулевые указатели
        return true;
    else if ((first == nullptr && second != nullptr) || (second == nullptr && first != nullptr)) { //если один нулевой указатель, а другой нет
        return false;
    }
    else {
        if (first->size != second->size) { // если размеры отличаются, массивы однозначно не равны
            return false;
        }
    }
    bool equal = true;
    for(int i = 0; i < first->size; i++){ // поэлементное сравнение
        if(first->array[i] != second->array[i]){
            equal = false;
            break;
        }
    }
    return equal;
}

Array *getArrayFromString(string &arrSeq) {
    if(arrSeq.empty())
        return nullptr;
    auto * arrayObj = new Array;
    stringstream myStream; // открывается строковый поток
    myStream << arrSeq; // в него записывается введённая строка
    int indentCounter = 0;
    int size = arrSeq.size();
    for(int i = 0; i < size; i++) { // размер массива формируется исходя из количества пробелов между элементами
        if (arrSeq[i] == ' ')
            indentCounter++;
    }
    arrayObj->size = ++indentCounter;
    arrayObj->array = new int[arrayObj->size];

    for(int i = 0; i < arrayObj->size; i++){  // из строкового потока происходит поэлементная запись в массив
        myStream >> arrayObj->array[i];
    }
    return arrayObj;
}

bool isCorrect(string &arrSeq) {
    if(arrSeq.find("  ") != -1 || arrSeq[arrSeq.size() - 1] == ' ') {
        cerr << "Присутствуют лишние пробелы\n";
        return false;
    }
    int size = arrSeq.size();
    for(int i = 0; i < size; i++)
    {
        if(!isdigit(arrSeq[i]) && arrSeq[i] != ' ' && arrSeq[i] != '-') {
            cerr << "Присутствуют запрещенные символы\n";
            return false;
        }
    }
    return true;
}

void printArray(int *arr, int &size, ostream &out) {
    out << "(  ";
    for(int i = 0; i < size; i++)
        out << arr[i] << "  ";
    out << ")";
}

Array * copyArray(Array * obj){
    if(obj == nullptr) // если пустой экземпляр, возвращается nullptr
        return nullptr;
    auto * copy = new Array; // иначе создаётся экземпляр
    copy->size = obj->size;
    if(copy->size == 0) {
        copy->array = nullptr;
    }
    else {
        copy->array = new int[obj->size]; // если массив у копируемого объекта не пустой
        for (int i = 0; i < copy->size; i++) { // поэлементное копирование
            copy->array[i] = obj->array[i];
        }
    }
 return copy; // возврат копии
}

void destroy(Array * obj){
    if(obj ==  nullptr)
        return;
    delete [] obj->array;
    delete obj;
}



