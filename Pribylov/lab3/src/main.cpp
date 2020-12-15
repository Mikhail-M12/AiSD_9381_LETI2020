#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "BinTree.h"
#include "Logger.h"

char kDefaultStopString[] = "STOP";
char kDefaultFileName[] = "input.txt";

void printTask(); // печатает задание
void printMenu(); // печатает меню
void menu(); // вызывает меню
void consoleInput(); // организует ввод с консоли
void fileInput(); // организует ввод с файла
void performTask(std::istream& infile); // принимает поток чтения, начинает работу программы

void printTask() {
    Logger::instance().log("- Для заданной формулы f построить дерево-формулу t;\n"
                           "- Для заданного дерева-формулы t напечатать соответствующую формулу f;\n"
                           "- Построить дерево-формулу t из строки, задающей формулу в\n"
                           "  префиксной форме (перечисление узлов t в порядке КЛП);\n"
                           "- Преобразовать дерево-формулу t, заменяя в нем все поддеревья,\n"
                           "  соответствующие формуле (f + f), на поддеревья, соответствующие формуле (2 * f).\n");
}

void printMenu() {
    std::cout << "1. Ввести данные с клавиатуры.\n"
                 "2. Ввести данные с файла.\n"
                 "0. Выход из программы.\n";
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

    while (!infile.eof()) {
        getline(infile, str);
        // удаляются все пробелы
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        if (!str.length()) continue;

        Logger::instance().log("Введена строка: " + str);
        if (str == kDefaultStopString) {
            Logger::instance().log("Встретилась терминальная строка.\n");
            return;
        }

        BinTree::BinTree<char> tree(str);
        // работа с деревом происходит, только если было передано корректное выражение
        if (tree.isArithmeticExpression() && (str == tree.toStringInOrder() || str == tree.toStringPreOrder())) { //
            Logger::instance().log("Построено дерево: " + tree.toStringInOrder()); //
            tree.sumToMul();
            Logger::instance().log("Результат: " + tree.toStringInOrder() + '\n');
        }
    }
}

int main() {
    menu();
    return 0;
}