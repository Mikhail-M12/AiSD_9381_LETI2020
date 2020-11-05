#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include "Logger.h"
#include <Windows.h>

template<typename T>
void printArray(T* array, int size, MessageType type = COMMON, int indent = 0, int cycleStart = -1, int position = -1, bool isEmpty = false, int index = -1) {
    Logger::log("", type, indent);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // ������� �������� ������� ��� ������ �������
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
        int position = cycleStart;              // ������ �������� �������� � �������
        T value = std::move(array[cycleStart]); // �������� �������� ��������

        Logger::log("\n[Outer loop iteration #" + std::to_string(cycleStart) + "]\n", DEBUG);
        Logger::log("Finding a place for an array element '" + std::to_string(value) + "':\n", DEBUG, 1);

        // ������� ����� ������� ��� �������� ��������
        for (int i = cycleStart + 1; i < size; i++) {
            printArray(array, size, DEBUG, 2, cycleStart, position, false, i);
            if (array[i] < value) {
                position++;
            }
        }
        printArray(array, size, DEBUG, 2, cycleStart, position, false);
        Logger::log("\n", DEBUG);

        // ���� ����� ������� �������� ������ ��������
        if (position != cycleStart) {
            // ���������� ������ �� �������� ��������
            while (value == array[position]) {
                Logger::log("Skipping elements with the same value: '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ".\n", DEBUG, 1);
                position++;
            }

            Logger::log("A new position was found for element '" + std::to_string(value) + "' with index " + std::to_string(cycleStart) + ": index " + std::to_string(position) + ".\n", DEBUG, 1);
            Logger::log("Placing element '" + std::to_string(value) + "' instead element '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ":\n", DEBUG, 1);

            // ������ �������� �������� �������� � ��������, ������� ����� �� ����� ������� �������� ��������
            std::swap(array[position], value);

            // ���� ����� ������� ��� ������ �������� �������� 
            while (position != cycleStart) {
                printArray(array, size, DEBUG, 2, cycleStart, position, true);
                Logger::log("\n", DEBUG);
                Logger::log("Finding a place for an array element '" + std::to_string(value) + "':\n", DEBUG, 1);
                position = cycleStart;

                // ������� ����� ������� ��� �������� ��������
                for (int i = cycleStart + 1; i < size; i++) {
                    printArray(array, size, DEBUG, 2, cycleStart, position, true, i);
                    if (array[i] < value) {
                        position++;
                    }
                }
                printArray(array, size, DEBUG, 2, cycleStart, position, true);
                Logger::log("\n", DEBUG);

                // ���������� ������ �� �������� ��������
                while (value == array[position]) {
                    Logger::log("Skipping elements with the same value: '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ".\n", DEBUG, 1);
                    position++;
                }

                Logger::log("A new position was found for element '" + std::to_string(value) + "': index " + std::to_string(position) + ".\n", DEBUG, 1);
                if (position != cycleStart) {
                    Logger::log("Placing element '" + std::to_string(value) + "' instead element '" + std::to_string(array[position]) + "' with index " + std::to_string(position) + ":\n", DEBUG, 1);
                }

                // ������ �������� �������� �������� � ��������, ������� ����� �� ����� ������� �������� ��������
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
    }

    Logger::log("\nCycle sorting end.\n");
}

void printHelp() {
    std::cout << "List of available options:\n";
    std::cout << "    -s    Enable silent mode.\n";
    std::cout << "    -h    Print help.\n";
    std::cout << "\n";
}

void clearInput() {
    // ������� �� ������ ����������� �������
    std::cin.clear();
    while (std::cin.get() != '\n');
}

int main(int argc, char* argv[]) {
    bool isLoopEnabled = true;
    bool isSilentMode = false;
    Logger& logger = Logger::getInstance();

    // ��������� ����� ������ ��������� �������
    logger.setFileOutput("logs\\" + Logger::getCurrentDateTime() + ".txt");

    // ��������� ���������� ��������� ������
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

    // ��������� ������ ������ �������
    logger.setSilentMode(isSilentMode);

    while (isLoopEnabled) {
        // ���������� ������ �������� ������������
        Logger::log("Available actions:\n\n  1) Read array from console.\n  2) Read array from file.\n  3) Generate a random array.\n  4) Exit.\n\nChoose one of the actions: ");
        int action = -1;
        std::cin >> action;

        while (action < 1 || action > 4) {
            clearInput();
            Logger::log("Incorrect action. Select the action again: ");
            std::cin >> action;
        }

        if (action == 4) {
            isLoopEnabled = false;
            continue;
        }

        int arraySize = 0;
        int* array(nullptr);

        if (action == 1 || action == 3) {
            // ���������� ������� �������
            Logger::log("Enter array size: ");
            std::cin >> arraySize;

            if (arraySize <= 0) {
                Logger::log("Invalid size!\n");
                clearInput();
                continue;
            }

            array = new int[arraySize];

            // ��������� �������� ������� � �������
            if (action == 1) {
                for (int i = 0; i < arraySize; i++) {
                    std::cin >> array[i];

                    // ���������� ������������ ��������
                    if (std::cin.fail()) {
                        clearInput();
                        i--;
                    }
                }
            }
            // ��������� ��������� �������� �������
            else {
                srand(time(nullptr));
                for (int i = 0; i < arraySize; i++) {
                    array[i] = rand() % 2001 - 1000; // ���������� ����� �� -1000 �� 1000
                }
            }
        }
        // ���� � �����
        else { 
            std::ifstream file("input.txt");

            // ���� ���� �� ������� �������
            if (!file.is_open()) {
                Logger::log("Cannot open file: input.txt\n");
                continue;
            }

            // ��������� ������ ������� �� �����
            file >> arraySize;

            if (arraySize <= 0) {
                Logger::log("Invalid size!\n");
                continue;
            }

            array = new int[arraySize];

            // ��������� �������� ������� �� �����
            for (int i = 0; i < arraySize; i++) {
                file >> array[i];
            }
        }

        // ������� ����� ������������������ �������
        std::vector<int> arrayCopy(arraySize);
        for (int i = 0; i < arraySize; i++) {
            arrayCopy[i] = array[i];
        }

        // ������� ����������������� ������
        Logger::log("\nUnsorted array:\n");
        printArray(array, arraySize);

        // ��������� �������
        cycleSort(array, arraySize);
        std::sort(arrayCopy.begin(), arrayCopy.end());

        // ��������� ������������ ����������
        bool correct = true;
        for (int i = 0; i < arraySize; i++) {
            if (array[i] != arrayCopy[i]) {
                correct = false;
                break;
            }
        }

        // ������� ��������������� ������
        Logger::log("\nSorted array:\n");
        printArray(array, arraySize);

        // ������� ��������� ������������
        if (correct) {
            Logger::log("\nCycle sort algorithm sorted the array correctly.\n\n");
        } else {
            Logger::log("\nCycle sort algorithm sorted the array incorrectly.\n\n");
        }

        delete[] array;
    }

    return 0;
}