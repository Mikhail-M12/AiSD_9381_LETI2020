#include <iostream>
#include <fstream>
#include <ctime>
#include "HierarchicalList.h"
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
    time_t t = time(nullptr);
    char buffer[80] = {'\0'};

    strftime(buffer, sizeof(buffer), "%d-%m-%y_%H-%M-%S", localtime(&t));

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
        std::string line, result;
        std::getline(file, line);

        // Поиск и проверка разделтеля
        size_t separatorIndex = line.find('|');
        if (separatorIndex != -1) {
            std::string expression = line.substr(0, separatorIndex); // Входная строка
            char elementToDelete = line.substr(separatorIndex + 1, separatorIndex + 2)[0]; // Элемент для удаления
            std::string correctResult = line.substr(separatorIndex + 3); // Корректный результат теста

            const char* end = expression.c_str();
            HierarchicalList list(end);

            // Проверка на корректность скобочной записи списка
            if (*end != ')' || *(end + 1) != '\0' || expression.size() <= 1) {
                result = "invalid"; // Результат теста
            } else {
                list.deleteElements(elementToDelete);
                result = list.getListString(); // Результат теста
            }

            // Вывод результатов теста
            if (correctResult == result) {
                successTestCount++;
                Logger::log("\n[Test #" + std::to_string(++testCount) + " OK]\n");
                Logger::log("Input list: " + expression + "\n");
                Logger::log("Deleting element: " + std::string(1, elementToDelete) + "\n");
                Logger::log("Correct result: " + correctResult + "\n");
                Logger::log("Test result: " + result + "\n\n");
            }
            else {
                Logger::log("\n[Test #" + std::to_string(++testCount) + " WRONG]\n");
                Logger::log("Input list: " + expression + "\n");
                Logger::log("Deleting element: " + std::string(1, elementToDelete) + "\n");
                Logger::log("Correct result: " + correctResult + "\n");
                Logger::log("Test result: " + result + "\n\n");
            }
        }
    }

    Logger::log("Passed tests: " + std::to_string(successTestCount) + "/" + std::to_string(testCount) + "\n");
}

int main(int argc, char* argv[]) {
    std::string expression;
    bool isFromFile = false;
    bool isTesting = false;
    bool isSilentMode = false;

    // Создание и настройка логгера
    Logger& logger = Logger::getInstance();
    logger.setFileOutput("logs\\" + getCurrentDateTime() + ".txt");

    // Обработка аргументов командной строки
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-f") == 0) {
                isFromFile = true;
            } else if (strcmp(argv[i], "-t") == 0) {
                isTesting = true;
            } else if (strcmp(argv[i], "-s") == 0) {
                isSilentMode = true;
            } else if (strcmp(argv[i], "-h") == 0) {
                printHelp();
                return 0;
            } else {
                Logger::log("Unknown option: " + std::string(argv[i]) + "\n");
                return 0;
            }
        }
    }

    // Установка тихого режима
    logger.setSilentMode(isSilentMode);

    // Тестирование алгоритма при помощи набора тестов
    if (isTesting) {
        test("tests\\tests.txt");
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
        std::cout << "[Enter list expression] ";
        std::getline(std::cin, expression);
        Logger::log("Entered list expression: " + expression + "\n");
    }

    // Создание иерархического списка
    const char* end = expression.c_str();
    HierarchicalList list(end);

    // Проверка на корректность скобочной записи списка
    if (*end != ')' || *(end + 1) != '\0' || expression.size() <= 1) {
        Logger::log("Invalid list expression.\n");
        return 0;
    }
    Logger::log("Created list: " + list.getListString() + "\n\n");

    // Ввод значения элементов, которые требуется удалить
    char element;
    std::cout << "[Enter element to delete] "; 
    std::cin >> element;
    Logger::log("Entered element to delete: " + std::string(1, element) + "\n\n");

    // Удаляем элементы из списка
    Logger::log("Deleting elements...\n");
    list.deleteElements(element);

    // Вывод результата работы программы
    Logger::log("Deleting completed!\n\n");
    Logger::log("List with removed elements '" + std::string(1, element) + "': " + list.getListString() + "\n\n");

    return 0;
}