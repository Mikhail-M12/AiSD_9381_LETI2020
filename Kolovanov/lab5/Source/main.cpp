#include <iostream>
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "Windows.h"
#include "ShannonFanoEncoder.h"
#include "ShannonFanoDecoder.h"

void clearInput() {
	// Удаляем из потока несчитанные символы до перевода на новую строку, включая его
	std::cin.clear();
    while (std::cin.get() != '\n');
}

int main() {
	bool isLoopEnabled = true;
	bool isDebugMode = true;
	Logger& logger = Logger::getInstance();

	// Настройка русского языка
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Настройка файла вывода сообщений логгера и режима вывода промежуточных данных
	logger.setOutputFile("Logs\\" + Logger::getCurrentDateTime() + ".log");
    logger.setDebugMode(true);

    while (isLoopEnabled) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Считывание выбора действия пользователя
        Logger::log("\nAvailable actions:\n\n  1) Encode text (input from console).\n  2) Encode text (input from file).\n  3) Decode text (input from file).\n");

        if (isDebugMode) {
            Logger::setConsoleColor(Color::Green, Color::Black);
        }
        Logger::log("  4) Enable output of intermediate data.\n");
        Logger::setConsoleColor(Color::LightGray, Color::Black);

        if (!isDebugMode) {
            Logger::setConsoleColor(Color::Green, Color::Black);
        }
        Logger::log("  5) Disable output of intermediate data.\n");
        Logger::setConsoleColor(Color::LightGray, Color::Black);

        Logger::log("  6) Exit.\n\n");
        std::cout << "Choose one of the actions: ";

        int action = -1;
        std::cin >> action;
        clearInput();

        while (action < 1 || action > 6) {
            Logger::log("Incorrect action. Select the action again: ");
            std::cin >> action;
            clearInput();
        }

        Logger::log("Choosed action: " + std::to_string(action) + "\n\n");

        // Кодирование текста
        if (action == 1 || action == 2) {
            std::stringstream text;

            // Считывание текста с консоли
            if (action == 1) {
                std::string line;
                std::cout << "Enter text: ";

                std::getline(std::cin, line);
                text << line;

                Logger::log("Entered text: " + text.str() + "\n\n");
            }
            // Считывание текста с файла
            else {
                std::ifstream inputFile("input_text.txt");

                // Если файл не удалось открыть
                if (!inputFile.is_open()) {
                    Logger::log("Cannot open file: input_text.txt\n");
                    continue;
                }

                std::string line;
                while (!inputFile.eof()) {
                    std::getline(inputFile, line);
                    text << line << "\n";
                }

                Logger::log("Reading text from file 'input_text.txt'...\n[Text from file]\n" + text.str() + "\n");
            }

            ShannonFanoEncoder encoder;     // Декодировщик
            const BinaryTree<char>* tree;   // Дерево Шеннона-Фано
            CharacterCodes characterCodes;  // Коды символов
            BitSequence encodedText;        // Последовательность бит закодированного текста

            Logger::log("Encoding text started...\n");

            // Кодирование текста
            encodedText = encoder.encodeText(text.str());
            tree = encoder.getTree();
            characterCodes = encoder.getCharacterCodes();

            Logger::log("Encoding text finished.\n\n");
            Logger::log("[Encoded text] ");
            for (auto bit : encodedText) {
                Logger::log(std::to_string(bit));
            }
            Logger::log("\n\nSaving encoded text to file 'encoded_text.txt'.\n");

            // Сохранение результата в файл
            std::ofstream outputFile("encoded_text.txt");

            // Если файл не удалось открыть
            if (!outputFile.is_open()) {
                Logger::log("Cannot open file: encoded_text.txt\n");
                continue;
            }

            outputFile << tree->getString() << "\n\n";

            for (auto bit : encodedText) {
                outputFile << bit;
            }

        }
        // Декодирование текста
        else if (action == 3) {
            std::ifstream inputFile("encoded_text.txt");

            // Если файл не удалось открыть
            if (!inputFile.is_open()) {
                Logger::log("Cannot open file: encoded_text.txt\n");
                continue;
            }

            std::string line("()");
            std::stringstream expression;

            // Считываем строки, содержащие скобочную запись дерева Шеннона-Фано
            while (line != "") {
                std::getline(inputFile, line);
                expression << line << "\n";
            }
            Logger::log("Reading encoded text and coding tree from file 'encoded_text.txt'...\n[Coding tree] " + expression.str() + "\n");

            ShannonFanoDecoder decoder(expression.str());
            BitSequence encodedText;
            std::getline(inputFile, line); // Считываем строку, содержащую последовательность бит закодированного текста
            Logger::log("[Encoded text] " + line + "\n\n");

            for (auto character : line) {
                if (character == '1') {
                    encodedText.push_back(true);
                } else if (character == '0') {
                    encodedText.push_back(false);
                }
            }

            Logger::log("Decoding text started...\n");

            // Декодирование текста
            std::string decodedText = decoder.decodeText(encodedText);

            Logger::log("Decoding text finished.\n\n");
            Logger::log("[Decoded text]\n" + decodedText + "\n\n");
            Logger::log("Saving decoded text to file 'decoded_text.txt'.\n");

            // Сохранение результата в файл
            std::ofstream outputFile("decoded_text.txt");
            
            // Если файл не удалось открыть
            if (!outputFile.is_open()) {
                Logger::log("Cannot open file: decoded_text.txt\n");
                continue;
            }

            outputFile << decodedText;

        } else if (action == 4 || action == 5) {
            // Включение режима отладки (вывода промежуточной информации)
            if (action == 4) {
                isDebugMode = true;
                Logger::log("Intermediate data output enabled.\n");
            }
            // Отключение режима отладки (вывода промежуточной информации)
            else {
                isDebugMode = false;
                Logger::log("Intermediate data output disabled.\n");
            }
            logger.setDebugMode(isDebugMode);

        } else {
            // Выход из программы
            isLoopEnabled = false;
        }
    }
	
	return 0;
}