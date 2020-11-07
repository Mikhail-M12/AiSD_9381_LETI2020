#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include "Logger.h"
#include <Windows.h>

void printHelp() {
    std::cout << "List of available options:\n";
    std::cout << "    -s    Enable silent mode.\n";
    std::cout << "    -h    Print help.\n";
    std::cout << "\n";
}

void clearInput() {
    // Удаляем из потока несчитанные символы
    std::cin.clear();
    while (std::cin.get() != '\n');
}

template<typename T>
void printArray(T* array, int size, MessageType type = COMMON, int indent = 0, int cycleStart = -1, int position = -1, bool isEmpty = false, int index = -1) {
    Logger::log("", type, indent);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Выводим элементы массива при помощи логгера
    for (int i = 0; i < size; i++) {
        if (i == position && i == cycleStart) {
            SetConsoleTextAttribute(hConsole, (WORD)((5 << 4) | 3));
            if (isEmpty) {
                Logger::log(".", type);
            } else {
                Logger::log(std::to_string(array[i]), type);
            }
        }
        else if (i == cycleStart) {
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
            if (isEmpty) {
                Logger::log(".", type);
            } else {
                Logger::log(std::to_string(array[i]), type);
            }
        }
        else if (i == position) {
            SetConsoleTextAttribute(hConsole, (WORD)((5 << 4) | 7));
            Logger::log(std::to_string(array[i]), type);
        }
        else if (i == index) {
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
            Logger::log(std::to_string(array[i]), type);
        }
        else {
            Logger::log(std::to_string(array[i]), type);
        }
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
        Logger::log(" ", type);
    }
    Logger::log("\n", type);
}

template<typename T>
void cycleSort(T* array, int size) {
    Logger::log("\nCycle sorting start.\n");

    for (int cycleStart = 0; cycleStart < size; cycleStart++) {
        int position = cycleStart;              // Индекс текущего элемента в массиве
        T value = std::move(array[cycleStart]); // Значение текущего элемента

        Logger::log("\n[Outer loop iteration #" + std::to_string(cycleStart) + "]\n", DEBUG);
        Logger::log("Finding a place for an array element '" + std::to_string(value) + "':\n", DEBUG, 1);

        // Находим новую позицию для текущего элемента
        for (int i = cycleStart + 1; i < size; i++) {
            printArray(array, size, DEBUG, 2, cycleStart, position, false, i);
            if (array[i] < value) {
                position++;
            }
        }
        printArray(array, size, DEBUG, 2, cycleStart, position, false);
        Logger::log("\n", DEBUG);

        // Если новую позицию занимает другой элеменет
        if (position != cycleStart) {
            // Пропускаем равные по значению элементы
            while (value == array[position]) {
                Logger::log("Skipping elements with the same value: '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ".\n", DEBUG, 1);
                position++;
            }

            Logger::log("A new position was found for element '" + std::to_string(value) + "' with index " + std::to_string(cycleStart) + ": index " + std::to_string(position) + ".\n", DEBUG, 1);
            Logger::log("Placing element '" + std::to_string(value) + "' instead element '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ":\n", DEBUG, 1);

            // Меняем значения текущего элемента и элемента, который стоит на новой позиции текущего элемента
            std::swap(array[position], value);

            // Ищем новую позицию для нового текущего элемента 
            while (position != cycleStart) {
                printArray(array, size, DEBUG, 2, cycleStart, position, true);
                Logger::log("\n", DEBUG);
                Logger::log("Finding a place for an array element '" + std::to_string(value) + "':\n", DEBUG, 1);
                position = cycleStart;

                // Находим новую позицию для текущего элемента
                for (int i = cycleStart + 1; i < size; i++) {
                    printArray(array, size, DEBUG, 2, cycleStart, position, true, i);
                    if (array[i] < value) {
                        position++;
                    }
                }
                printArray(array, size, DEBUG, 2, cycleStart, position, true);
                Logger::log("\n", DEBUG);

                // Пропускаем равные по значению элементы
                while (value == array[position]) {
                    Logger::log("Skipping elements with the same value: '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ".\n", DEBUG, 1);
                    position++;
                }

                Logger::log("A new position was found for element '" + std::to_string(value) + "': index " + std::to_string(position) + ".\n", DEBUG, 1);
                if (position != cycleStart) {
                    Logger::log("Placing element '" + std::to_string(value) + "' instead element '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ":\n", DEBUG, 1);
                }

                // Меняем значения текущего элемента и элемента, который стоит на новой позиции текущего элемента
                std::swap(array[position], value);
            }

            Logger::log("Placing element on index " + std::to_string(position) + ":\n", DEBUG, 1);
            printArray(array, size, DEBUG, 2, cycleStart, position, false);
        } else {
            Logger::log("A new position was found for element '" + std::to_string(value) + "': index " + std::to_string(position) + ".\n", DEBUG, 1);
            array[position] = std::move(value);
            Logger::log("Placing element on index " + std::to_string(position) + ":\n", DEBUG, 1);
            printArray(array, size, DEBUG, 2, cycleStart, position, false);
        }

        if (size <= 10 && !Logger::getInstance().getSilentMode()) {
            Logger::log("\nOuter loop iteration #" + std::to_string(cycleStart) + " is over. Press 'Enter' to move to the next iteration...\n", DEBUG);
            clearInput();
        }
    }

    Logger::log("\nCycle sorting end.\n");
}

int main(int argc, char* argv[]) {
    bool isLoopEnabled = true;
    bool isSilentMode = false;
    Logger& logger = Logger::getInstance();

    // Настройка файла вывода сообщений логгера
    logger.setFileOutput("logs\\" + Logger::getCurrentDateTime() + ".txt");

    // Обработка аргументов командной строки
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-s") == 0) {
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

    // Установка тихого режима логгера
    logger.setSilentMode(isSilentMode);

    while (isLoopEnabled) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Считывание выбора действия пользователя
        Logger::log("Available actions:\n\n  1) Read array from console.\n  2) Read array from file.\n  3) Generate a random array.\n");

        if (!isSilentMode) {
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
        }
        Logger::log("  4) Enable output of intermediate data.\n");
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));

        if (isSilentMode) {
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
        }
        Logger::log("  5) Disable output of intermediate data.\n");
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));

        Logger::log("  6) Exit.\n\nChoose one of the actions: ");

        int action = -1;
        std::cin >> action;

        while (action < 1 || action > 6) {
            clearInput();
            Logger::log("Incorrect action. Select the action again: ");
            std::cin >> action;
        }

        if (action == 6) {
            isLoopEnabled = false;
            continue;
        }

        if (action == 4) {
            isSilentMode = false;
            logger.setSilentMode(isSilentMode);
            Logger::log("Intermediate data output enabled.\n");
            continue;
        }
        else if (action == 5) {
            isSilentMode = true;
            logger.setSilentMode(isSilentMode);
            Logger::log("Intermediate data output disabled.\n");
            continue;
        }

        int arraySize = 0;
        int* array(nullptr);

        if (action == 1 || action == 3) {
            // Считывание размера массива
            Logger::log("Enter array size: ");
            std::cin >> arraySize;

            if (arraySize <= 0) {
                Logger::log("Invalid size!\n");
                clearInput();
                continue;
            }

            array = new int[arraySize];

            // Считываем значения массива с консоли
            if (action == 1) {
                Logger::log("Enter array:\n");

                for (int i = 0; i < arraySize; i++) {
                    std::cin >> array[i];

                    // Пропускаем некорректные значения
                    if (std::cin.fail()) {
                        clearInput();
                        i--;
                    }
                }
            }
            // Рандомная генерация значений массива
            else {
                srand(time(nullptr));
                for (int i = 0; i < arraySize; i++) {
                    array[i] = rand() % 2001 - 1000; // Генерируем числа от -1000 до 1000
                }
            }

            clearInput();
        }
        // Ввод с файла
        else { 
            std::ifstream file("input.txt");

            // Если файл не удалось открыть
            if (!file.is_open()) {
                Logger::log("Cannot open file: input.txt\n");
                continue;
            }

            // Считываем размер массива из файла
            file >> arraySize;

            if (arraySize <= 0) {
                Logger::log("Invalid size!\n");
                continue;
            }

            array = new int[arraySize];

            // Считываем значения массива из файла
            for (int i = 0; i < arraySize; i++) {
                file >> array[i];
            }
        }

        // Создаем копию неотсортированного массива
        std::vector<int> arrayCopy(arraySize);
        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i];
        }

        // Выводим неотсортированный массив
        Logger::log("\nUnsorted array:\n");
        printArray(array, arraySize);

        // Сортируем массивы
        cycleSort(array, arraySize);
        std::sort(arrayCopy.begin(), arrayCopy.end());

        // Проверяем правильность сортировки
        bool correct = true;
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != arrayCopy[i]) {
                correct = false;
                break;
            }
        }

        // Выводим отсортированный массив
        Logger::log("\nSorted array:\n");
        printArray(array, arraySize);

        // Выводим результат тестирования
        if (correct) {
            Logger::log("\nCycle sort algorithm sorted the array correctly.\n\n");
        } else {
            Logger::log("\nCycle sort algorithm sorted the array incorrectly.\n\n");
        }

        delete[] array;
    }

    return 0;
}