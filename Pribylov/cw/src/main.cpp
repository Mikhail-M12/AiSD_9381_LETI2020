#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Treap.h"
#include "Logger.h"

using namespace treap;

char kDefaultStopString[] = "STOP";
char kDefaultFileName[] = "input.txt";

void printTask(); // печатает задание
void printMenu(); // печатает меню
void printVector(const std::vector<int>& vec); // печатает вектор
void menu(); // вызывает меню
void consoleInput(); // организует ввод с консоли
void fileInput(); // организует ввод с файла
void performTask(std::istream& infile); // принимает поток чтения, начинает работу программы
void treapMenu(TreapPtr& tree); // вызывает меню добавления/исключения элемента из дерамиды
void printTreapMenu(); // печатает меню добавления/исключения элемента из дерамиды


void printTask() {
    Logger::instance().log("Демонстрация добавления/удаления элемента в рандомизированной дерамиде поиска.\n"
                           "Предполагается, что в дереве не могут находиться элементы с одинаковыми ключами.\n");
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

void printTreapMenu() {
    std::cout << "1. Добавить элемент в дерамиду.\n"
                           "2. Удалить элемент из дерамиды.\n"
                           "0. Вернуться назад и ввести новые данные.\n";
}

void treapMenu(TreapPtr& tree) {
    printTreapMenu();
    char c = '1';
    int key;
    std::string str;
    do {
        std::cin >> c;
        std::cin.ignore(256, '\n');
        switch(c) {
            case '1':
                std::cout << "Введите значение ключа: ";
                std::cin >> key;
                for (;;) {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Необходимо ввести число: ";
                        std::cin >> key;
                    }
                    if (!std::cin.fail()) {
                        insert(tree, key);
                        break;
                    }
                }
                break;
            case '2':
                std::cout << "Введите значение ключа: ";
                std::cin >> key;
                for (;;) {
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Необходимо ввести число: ";
                        std::cin >> key;
                    }
                    if (!std::cin.fail()) {
                        remove(tree, key);
                        break;
                    }
                }
                break;
            case '0':
                std::cout << "Вводите новые данные:\n";
                return;
            default:
                std::cout << "Неверное значение.\n";
                break;
        }
        if (c != '0') printTreapMenu();
    } while (c != '0');
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
        for (;;) { // преобразование строки в вектор чисел
            char* pEnd;
            const long i = std::strtol(cstr, &pEnd, 10);
            if (cstr == pEnd) break;
            cstr = pEnd;
            vec.push_back(i);
        }

        Logger::instance().log("\nВведён "); printVector(vec);
        if (vec.empty()) continue;
        auto tree = build(vec);
        Logger::instance().log("Построено дерево:\n");
        printTree(tree, nullptr, false, 99999999);

        treapMenu(tree);

        vec.clear();
    }
}

int main() {
    try {
        srand(time(nullptr));
        menu();
    } catch (std::exception&) {
        std::cout << "menu(): Exception caught\n";
    }
    return 0;
}

