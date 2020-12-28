#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Logger.h"

char kDefaultStopString[] = "STOP";
char kDefaultFileName[] = "input.txt";

void printTask(); // печатает задание
void printMenu(); // печатает меню
void printVector(const std::vector<int>& vec); // печатает вектор
void shakerSort(std::vector<int>& vec); // шейкерная сортировка
void bubbleSelectionSort(std::vector<int>& vec); // сортировка пузырьком/выбором
void menu(); // вызывает меню
void consoleInput(); // организует ввод с консоли
void fileInput(); // организует ввод с файла
void performTask(std::istream& infile); // принимает поток чтения, начинает работу программы


void printTask() {
    Logger::instance().log("Сортировка пузырьком/выбором, шейкерная сортировка.\n");
}

void printMenu() {
    std::cout << "1. Ввести данные с клавиатуры.\n"
                 "2. Ввести данные с файла.\n"
                 "0. Выход из программы.\n";
}

void printVector(const std::vector<int>& vec) {
    Logger::instance().log("Вектор: ");
    for (auto v : vec) {
        Logger::instance().log(std::to_string(v) + " ");
    }
    Logger::instance().log("\n");
}

void shakerSort(std::vector<int>& vec) {
    if (vec.size() < 2) return;
    size_t left = 0;
    size_t right = vec.size() - 1;
    size_t control = vec.size() - 1;
    while (left < right) {
        // поиск максимального элемента с начала
        for (size_t i = left; i < right; i++) {
            if (vec[i] > vec[i+1]) {
                // меняются два соседних элемента, как в пузырьковой сортировке
                std::swap(vec[i], vec[i+1]);
                printVector(vec);
                control = i;
            }
        }
        right = control; // контроль отсортированной части (чтобы не пробегать по ней лишний раз)
        // поиск минимального элемента с конца
        for (size_t i = right; i > left; i--) {
            if (vec[i] < vec[i-1]) {
                // 
                std::swap(vec[i], vec[i-1]);
                printVector(vec);
                control = i;
            }
        }
        left = control; // контроль отсортированной части (чтобы не пробегать по ней лишний раз)
    }
}

void bubbleSelectionSort(std::vector<int>& vec) {
    if (vec.size() < 2) return;
    size_t begin = 0;
    size_t end = vec.size();
    size_t mid = (end-1)*3/4;
    // часть вектора сортируется сортировкой выбором
    for (size_t i = begin; i < mid; i++) {
        int jmin = i;
        for (size_t j = i+1; j < end; j++) {
            if (vec.at(j) < vec.at(jmin)) {
                jmin = j;
            }
        }
        if (jmin != i) {
            // минимальный элемент вставляется в начало вектора
            std::swap(vec[i], vec[jmin]);
            printVector(vec);
        }
    }

    // оставшаяся часть сортируется пузырьковой сортировкой
    for (size_t i = mid; i < end-1; i++) {
        for (size_t j = mid; j < end-i+mid-1; j++) {
            if (vec.at(j) > vec.at(j+1)) {
                // меняются два соседних элемента
                std::swap(vec[j], vec[j+1]);
                printVector(vec);
            }
        }
    }
}

void menu() {
    printTask();
    printMenu();
    char c = '1';
    do {
        std::cin >> c;
        std::cin.ignore(256, '\n');
        switch(c) {
            case '1':
                consoleInput();
                break;
            case '2':
                fileInput();
                break;
            case '0':
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверное значение.\n";
                break;
        }
        if (c != '0') printMenu();
    } while (c != '0');
}

void consoleInput() {
    std::cout << "Вводите данные:\n"
                 "Чтобы вернуться в меню, введите \"" << kDefaultStopString << "\"\n";
    performTask(std::cin);
}

void fileInput() {
    std::string inputFileName;
    std::ifstream infile;
    std::cout << "Введите название файла:\n"
                 "По умолчанию данные читаются из файла \"" << kDefaultFileName << "\".\n";
    getline(std::cin, inputFileName);

    if (inputFileName.empty()) {
        inputFileName = kDefaultFileName;
    }

    infile.open(inputFileName);
    if (!infile) {
        std::cout << "Файла \"" << inputFileName << "\" не существует.\n";
    } else {
        std::cout << "Чтение данных прекратится на строке \"" << kDefaultStopString << "\".\n";
        performTask(infile);
    }

    if (infile.is_open()) {
        infile.close();
    }
}

void performTask(std::istream& infile)
{
    std::string str;
    std::vector<int> vec;

    while (!infile.eof()) {
        getline(infile, str);
        if (str.empty()) continue;
        if (str == kDefaultStopString) {
            Logger::instance().log("Встретилась терминальная строка.\n\n");
            return;
        }

        const char *cstr = str.c_str();
        for (;;) { // разбиение строки на вектор чисел
            char* pEnd;
            const long i = std::strtol(cstr, &pEnd, 10);
            if (cstr == pEnd) break;
            cstr = pEnd;
            vec.push_back(i);
        }

        Logger::instance().log("\nВведён "); printVector(vec);
        auto vec2 = vec;
        auto vec3 = vec;
        Logger::instance().log("\nСортировка пузырьком/выбором:\n");
        bubbleSelectionSort(vec);
        Logger::instance().log("\nШейкерная сортировка:\n");
        shakerSort(vec2);
        Logger::instance().log("\nstd::sort:\n");
        std::sort(vec3.begin(), vec3.end());
        printVector(vec);
        vec.clear();
        vec2.clear();
        vec3.clear();
    }
}

int main() {
    try {
        menu();
    } catch (std::exception&) {
        std::cout << "menu(): Exception caught\n";
    }
    return 0;
}
