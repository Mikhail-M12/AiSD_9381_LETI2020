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
    time_t timestamp; // ��������� �����
    tm timeinfo;      // ��������� � ����������� � �������
    char buffer[80] = { '\0' };

    time(&timestamp); // ��������� ��������� �����
    localtime_s(&timeinfo, &timestamp); // ��������� ���������� � �������
    strftime(buffer, sizeof(buffer), "%d-%m-%y_%H-%M-%S", &timeinfo);

    return std::string(buffer);
}

void test(const std::string& path) {
    size_t testCount = 0; // ����� ���������� ������
    size_t successTestCount = 0; // ��������� �������� ������
    std::ifstream file(path);

    // �������� �� ��, ��� ���� ��� ������
    if (!file.is_open()) {
        Logger::log("Cannot open file: " + path + "\n");
        return;
    }

    Logger::log("File with tests: " + path + "\n");

    while (!file.eof()) { // ���� �� ��������� �� ���� ������� �����
        std::string line, result1, result2;
        std::getline(file, line);

        // ����� � �������� ����������
        size_t separatorIndex1 = line.find('|');
        size_t separatorIndex2 = line.rfind('|');
        if (separatorIndex1 != -1 && separatorIndex2 != -1 && separatorIndex1 != separatorIndex2) {
            std::string expression = line.substr(0, separatorIndex1); // ������� ������
            std::string correctResult1 = line.substr(separatorIndex1 + 1, separatorIndex2 - separatorIndex1 - 1); // ���������� ��������� ����� 1
            std::string correctResult2 = line.substr(separatorIndex2 + 1); // ���������� ��������� ����� 2

            const char* end = expression.c_str();
            BinaryTree<char> tree(end);

            // �������� �� ������������ ��������� ������ ������
            if (*end != ')' || *(end + 1) != '\0' || expression.length() < 2) {
                result1 = "invalid"; // ��������� ����� 1
                result2 = "invalid"; // ��������� ����� 2
            } else {
                result1 = std::to_string(tree.getMaximumDepth()); // ��������� ����� 1
                result2 = std::to_string(tree.getInternalPathLength()); // ��������� ����� 2
            }

            // ����� ����������� �����
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

    Logger::log("Passed tests: " + std::to_string(successTestCount) + "/" + std::to_string(testCount) + "\n");
}

int main(int argc, char* argv[]) {
    std::string expression;
    bool isFromFile = false;
    bool isTesting = false;
    bool isSilentMode = false;

    // �������� � ��������� �������
    Logger& logger = Logger::getInstance();
    logger.setFileOutput("logs\\" + getCurrentDateTime() + ".txt");

    // ��������� ���������� ��������� ������
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

    // ��������� ������ ������
    logger.setSilentMode(isSilentMode);

    // ������������ ��������� ��� ������ ������ ������
    if (isTesting) {
        test("tests\\tests.txt");
        return 0;
    }

    // ���� ��������� �� �����
    if (isFromFile) {
        std::fstream file("input.txt");

        // �������� �� ��, ��� ���� ��� ������
        if (!file.is_open()) {
            Logger::log("Cannot open file: input.txt\n");
            return 0;
        }

        std::getline(file, expression);
        Logger::log("Expression from file: " + expression + "\n");

    }
    // ���� ��������� � ����������
    else {
        std::cout << "[Enter binary tree expression] ";
        std::getline(std::cin, expression);
        Logger::log("Entered binary tree expression: " + expression + "\n");
    }

    // �������� ��������� ������
    const char* end = expression.c_str();
    BinaryTree<char> tree(end);

    // �������� �� ������������ ��������� ������ ������
    if (*end != ')' || *(end + 1) != '\0' || expression.length() < 2) {
        Logger::log("Invalid binary tree expression.\n");
        return 0;
    }

    Logger::log("Created binary tree: " + tree.getString() + "\n\n");

    // ��������� �����������
    size_t maximumDepth = tree.getMaximumDepth();
    size_t internalPathLength = tree.getInternalPathLength();

    // ����� ���������� ������ ���������
    Logger::log("Binary tree maximum depth: " + std::to_string(maximumDepth) + "\n");
    Logger::log("Binary tree internal path length: " + std::to_string(internalPathLength) + "\n");

    return 0;
}