#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "HList.h"
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
    Logger::instance().log("Проверка идентичности двух иерархических списков.\n");
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
        switch(c) {
            case '1':
                std::cin.ignore(256, '\n');
                consoleInput();
                break;
            case '2':
                std::cin.ignore(256, '\n');
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
    std::string first, second;

    while (!infile.eof()) {
        getline(infile, first);
        // удаляются все пробелы
        first.erase(std::remove(first.begin(), first.end(), ' '), first.end());
        if (!first.length()) continue;

        Logger::instance().log("Первый список: " + first);
        if (first == kDefaultStopString) {
            Logger::instance().log("Встретилась терминальная строка.\n");
            return;
        }

        getline(infile, second);
        second.erase(std::remove(second.begin(), second.end(), ' '), second.end());
        if (!second.length()) continue;

        Logger::instance().log("Второй список: " + second);
        if (second == kDefaultStopString) {
            Logger::instance().log("Встретилась терминальная строка.\n");
            return;
        }

        hlist::HList x(first), y(second);
        x == y ?
            Logger::instance().log("Списки идентичны.\n")
        :
            Logger::instance().log("Списки не идентичны.\n");
    }
}

int main() {
    menu();
    return 0;
}
