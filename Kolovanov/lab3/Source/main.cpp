#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "BinaryTree.h"
#include "Logger.h"

void printHelp() {
    std::cout << "List of available options:\n";
    std::cout << "    -f    Input from file.\n";
    std::cout << "    -t    Conduct testing.\n";
    std::cout << "    -s    Enable silent mode.\n";
    std::cout << "    -h    Print help.\n";
    std::cout << "\n";
}

std::string getCurrentDateTime() {
    time_t timestamp; // Временная метка
    tm timeinfo;      // Структура с информацией о времени
    char buffer[80] = { '\0' };

    time(&timestamp); // Получение временной метки
    localtime_s(&timeinfo, &timestamp); // Получение информации о времени
    strftime(buffer, sizeof(buffer), "%d-%m-%y_%H-%M-%S", &timeinfo);

    return std::string(buffer);
}

void test(const std::string& path) {
    size_t testCount = 0; // Общее количество тестов
    size_t successTestCount = 0; // Колчество успешных тестов
    std::ifstream file(path);

    // Проверка на то, что файл был открыт
    if (!file.is_open()) {
        Logger::log("Cannot open file: " + path + "\n");
        return;
    }

    Logger::log("File with tests: " + path + "\n");

    while (!file.eof()) { // Пока не пройдемся по всем строкам файла
        std::string line, result1, result2;
        std::getline(file, line);

        // Поиск и проверка разделтеля
        size_t separatorIndex1 = line.find('|');
        size_t separatorIndex2 = line.rfind('|');
        if (separatorIndex1 != -1 && separatorIndex2 != -1 && separatorIndex1 != separatorIndex2) {
            std::string expression = line.substr(0, separatorIndex1); // Входная строка
            std::string correctResult1 = line.substr(separatorIndex1 + 1, separatorIndex2 - separatorIndex1 - 1); // Корректный результат теста 1
            std::string correctResult2 = line.substr(separatorIndex2 + 1); // Корректный результат теста 2

            BinaryTree<char> tree;
            const char* end = expression.c_str();
            bool correct = tree.createFromString(end);

            // Проверка на корректность скобочной записи списка
            if (*end != '\0' || !correct) {
                result1 = "invalid"; // Результат теста 1
                result2 = "invalid"; // Результат теста 2
            } else if (tree.isEmpty()) {
                result1 = "empty";
                result2 = "empty";
            } else {
                result1 = std::to_string(tree.getMaximumDepth()); // Результат теста 1
                result2 = std::to_string(tree.getInternalPathLength()); // Результат теста 2
            }

            // Вывод результатов теста
            if (result1 == correctResult1 && result2 == correctResult2) {
                successTestCount++;
                Logger::log("\n[Test #" + std::to_string(++testCount) + " OK]\n");
            } else {
                Logger::log("\n[Test #" + std::to_string(++testCount) + " WRONG]\n");
            }

            Logger::log("Input binary tree: " + expression + "\n");
            Logger::log("Correct result: Maximum depth = " + correctResult1 + " and internal path length = " + correctResult2 + "\n");
            Logger::log("Test result: Maximum depth = " + result1 + " and internal path length = " + result2 + "\n");
        }
    }

    Logger::log("\nPassed tests: " + std::to_string(successTestCount) + "/" + std::to_string(testCount) + "\n");
}

int main(int argc, char* argv[]) {
    std::string expression;
    bool isFromFile = false;
    bool isTesting = false;
    bool isSilentMode = false;

    // Создание и настройка логгера
    Logger& logger = Logger::getInstance();
    logger.setFileOutput("Logs\\" + getCurrentDateTime() + ".txt");

    // Обработка аргументов командной строки
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-f") == 0) {
                isFromFile = true;
            }
            else if (strcmp(argv[i], "-t") == 0) {
                isTesting = true;
            }
            else if (strcmp(argv[i], "-s") == 0) {
                isSilentMode = true;
            }
            else if (strcmp(argv[i], "-h") == 0) {
                printHelp();
                return 0;
            }
            else {
                Logger::log("Unknown option: " + std::string(argv[i]) + "\n");
                return 0;
            }
        }
    }

    // Установка тихого режима
    logger.setSilentMode(isSilentMode);

    // Тестирование алгоритма при помощи набора тестов
    if (isTesting) {
        test("Tests\\tests.txt");
        return 0;
    }

    // Ввод выражения из файла
    if (isFromFile) {
        std::fstream file("input.txt");

        // Проверка на то, что файл был открыт
        if (!file.is_open()) {
            Logger::log("Cannot open file: input.txt\n");
            return 0;
        }

        std::getline(file, expression);
        Logger::log("Expression from file: " + expression + "\n");

    }
    // Ввод выражения с клавиатуры
    else {
        std::cout << "[Enter binary tree expression] ";
        std::getline(std::cin, expression);
        Logger::log("Entered binary tree expression: " + expression + "\n");
    }
    
    // Создание бинарного дерева
    BinaryTree<char> tree;
    const char* end = expression.c_str();
    bool correct = tree.createFromString(end);

    // Проверка на корректность скобочной записи списка
    if (*end != '\0' || !correct) {
        Logger::log("Invalid binary tree expression.\n");
        return 0;
    } else if (tree.isEmpty()) {
        Logger::log("Binary tree is empty.\n");
        return 0;
    }

    Logger::log("Created binary tree: " + tree.getString() + "\n\n");

    // Получение результатов
    size_t maximumDepth = tree.getMaximumDepth();
    size_t internalPathLength = tree.getInternalPathLength();

    // Вывод результата работы программы
    Logger::log("Binary tree maximum depth: " + std::to_string(maximumDepth) + "\n");
    Logger::log("Binary tree internal path length: " + std::to_string(internalPathLength) + "\n");

    return 0;
}