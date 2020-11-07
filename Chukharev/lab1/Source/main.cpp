#include <iostream>
#include <fstream>
#include <conio.h>
#include "functions.h"

void test(const std::string& path, std::ofstream& logfile) {
    size_t testCount = 0; // Общее количество тестов
    size_t testCountSuccess = 0; // Количество успешных тестов
    std::ifstream file(path);

    // Проверка открытия файла
    if (!file.is_open()) {
        log("Cannot open file: " + path + "\n", logfile);
        return;
    }

    log("File with tests: " + path + "\n", logfile);

    while (!file.eof()) { // Пока не пройдемся по всем строкам файла
        std::string line;
        file >> line;

        // Поиск и проверка разделтеля
        size_t separatorIndex = line.find('|'); 
        if (separatorIndex != -1) {
            std::string expression = line.substr(0, separatorIndex); // Входная строка
            bool correctResult = line.substr(separatorIndex + 1, separatorIndex + 2) == "T"; // Корректный результат теста
            bool result = isBrackets(expression, logfile); // Результат теста

            // Вывод сравнения результата с корректным результатом теста
            if (correctResult == result) {
                testCountSuccess++;
                log("[Test №" + std::to_string(++testCount) + " OK] ", logfile);
            } else {
                log("[Test №" + std::to_string(++testCount) + " WRONG] ", logfile);
            }   

            // Вывод результата теста
            if (result) {
                log("Result: '" + expression + "' is brackets.\n\n", logfile);
            } else {
                log("Result: '" + expression + "' is not brackets.\n\n", logfile);
            }
        }
    }

    log("Passed tests: " + std::to_string(testCountSuccess) + "/" + std::to_string(testCount) + "\n", logfile);
}

int main(int argc, char* argv[]) {
    std::ofstream logfile("log.txt");
    std::string expression;

    if (!logfile.is_open()) {
        std::cout << "Cannot open file: log.txt\n";
        _getch();
        return 0;
    }

    // Считывание выбора действия пользователя
    log("Available actions:\n\n  1) Read expression from console.\n  2) Read expression from file.\n  3) Run testing.\n\nSelect the action: ", logfile);

    int action = -1;
    std::cin >> action;

    while (action < 1 || action > 3) {
        log("Incorrect action. Select the action again: ", logfile);
        std::cin >> action;
    }

    // Тестирование алгоритма при помощи набора тестов
    if (action == 3) {
        test("tests.txt", logfile);
        _getch();
        return 0;
    }

    if (action == 2) { // Ввод выражения из файла
        std::ifstream file("input.txt");

        // Проверка открытия файла
        if (!file.is_open()) {
            log("Cannot open file: input.txt\n", logfile);
            _getch();
            return 0;
        } else {
            file >> expression;
            log("Expression from file: " + expression + "\n", logfile);
        }

    } else { // Ввод выражения с клавиатуры
        std::cout << "[Enter expression] ";
        std::cin >> expression;
        log("Entered expression: " + expression + "\n", logfile);
    }

    // Вывод результата работы программы на экран
    if (isBrackets(expression, logfile)) {
        log("Result: '" + expression + "' is brackets.\n", logfile);
    } else {
        log("Result: '" + expression + "' is not brackets.\n", logfile);
    }

    _getch();
    return 0;
}