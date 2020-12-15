#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "Logger.h"
#include "Exception.h"
#include "Windows.h"
#include "ShannonFanoEncoder.h"
#include "HuffmanEncoder.h"
#include "Decoder.h"
#include "Utils.h"


int main() {
	bool is_loop_enabled = true;    // Продолжать ли работу основного цикла работы программы
	bool is_debug_mode = true;      // Включен ли режим вывода промежуточных данных
	Logger& logger = Logger::getInstance();

	// Настройка русского языка для консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Настройка файла вывода сообщений логгера и установка режима вывода промежуточных данных
	logger.setOutputFile("logs\\" + Logger::getCurrentDateTime() + ".log");
    logger.setDebugMode(is_debug_mode);

    // Основной цикл работы программы
    while (is_loop_enabled) {
        int action = -1;    // Выбранное действие
        int algorithm = -1; // Выбранный алгоритм

        // Считывание выбора действия пользователя
        Logger::log("\nДоступные действия:\n\n  1) Закодировать текст - Ввод с консоли.\n  2) Закодировать текст - Ввод с файла.\n  3) Раскодировать текст - Ввод с файла.\n");

        if (is_debug_mode) {
            Logger::setConsoleColor(Color::Green, Color::Black);
            Logger::log("  4) Включить вывод промежуточных данных (уже включен).\n");
            Logger::setConsoleColor(Color::LightGray, Color::Black);
        } else {
            Logger::log("  4) Включить вывод промежуточных данных.\n");
        }

        if (!is_debug_mode) {
            Logger::setConsoleColor(Color::Green, Color::Black);
            Logger::log("  5) Отключить вывод промежуточных данных (уже выключен).\n");
            Logger::setConsoleColor(Color::LightGray, Color::Black);
        } else {
            Logger::log("  5) Отключить вывод промежуточных данных.\n");
        }

        Logger::log("  6) Выйти из программы.\n\n");
        std::cout << "Выберите одно из вышеперечисленных действий: ";
        std::cin >> action;
        Utils::clearInput();

        if (action < 1 || action > 6) {
            Logger::log("Выбрано некорректное действие.\n");
            continue;
        }

        Logger::log("Выбранное действие: " + std::to_string(action) + "\n");

        // Выбор алгоритма кодирования
        if (action < 3) {
            Logger::log("\nДоступные алгоритмы кодирования:\n\n  1) Алгоритм Шеннона-Фано.\n  2) Алгоритм Хаффмана.\n\n");
            std::cout << "Выберите одно из вышеперечисленных алгоритмов: ";
            std::cin >> algorithm;
            Utils::clearInput();

            while (algorithm < 1 || algorithm > 2) {
                std::cout << "Выбран некорректный алгоритм. Выберите алгоритм снова: ";
                std::cin >> algorithm;
                Utils::clearInput();
            }

            Logger::log("Выбранный алгоритм: " + std::to_string(algorithm) + "\n\n");
        }

        // Кодирование текста
        if (action == 1 || action == 2) {
            std::stringstream text;

            // Считывание текста с консоли
            if (action == 1) {
                std::string line;

                std::cout << "Введите текст: ";
                std::getline(std::cin, line);
                text << line;

                Logger::log("Введенный текст: " + line + "\n\n");
            }
            // Считывание текста с файла
            else {
                std::string path, line;
                std::ifstream input_file;

                std::cout << "Введите путь к файлу: ";
                std::getline(std::cin, path);
                Logger::log("Введенный путь к файлу: " + path + "\n");

                input_file.open(path);

                // Если файл не удалось открыть
                if (!input_file.is_open()) {
                    Logger::log("При открытии файла произошла ошибка: " + path + "\n", MessageType::Error);
                    input_file.close();
                    continue;
                }

                Logger::log("Считывание текста из файла '" + path + "'...\n");

                while (!input_file.eof()) {
                    std::getline(input_file, line);
                    text << line << "\n";
                }

                Logger::log("[Текст из файла]\n" + text.str() + "\n");
                input_file.close();
            }

            std::shared_ptr<Encoder> encoder;    // Указатель на кодировщик текста
            std::string tree_expression;         // Скобочная запись дерева кодирования
            std::string encoded_text_string;     // Строка, содержащая закодированный текст
            CharacterCodes character_codes;      // Коды закодированных символов
            BitSequence encoded_text;            // Последовательность бит закодированного текста

            if (algorithm == 1) {
                encoder = std::make_shared<ShannonFanoEncoder>();   // Кодировщик Шеннона-Фано
            } else {
                encoder = std::make_shared<HuffmanEncoder>();       // Кодировщик Хаффмана
            }

            Logger::log("Кодирование текста...\n");

            // Кодирование текста
            encoded_text = encoder->encodeText(text.str());
            tree_expression = encoder->getCodingTree()->getString();
            character_codes = encoder->getCharacterCodes();
            encoded_text_string = Utils::bitSequenceToString(encoded_text);

            Logger::log("Кодирование текста завершено.\n\n");
            Logger::log("[Дерево кодирования] " + tree_expression + "\n");
            Logger::log("[Закодированный текст] " + encoded_text_string + "\n\n");

            // Сохранение результата в файл
            std::ofstream output_file("encoded_text.txt");

            // Если файл не удалось открыть
            if (!output_file.is_open()) {
                Logger::log("При открытии файла произошла ошибка: encoded_text.txt\n", MessageType::Error);
                output_file.close();
                continue;
            }

            output_file << tree_expression << "\n\n" << encoded_text_string;

            Logger::log("Закодированный текст записан в файл 'encoded_text.txt'.\n");
            output_file.close();
        }
        // Декодирование текста
        else if (action == 3) {
            std::ifstream input_file("encoded_text.txt");
            std::stringstream expression; // Скобочная запись дерева кодирования
            std::string line("\\");

            // Если файл не удалось открыть
            if (!input_file.is_open()) {
                Logger::log("При открытии файла произошла ошибка: encoded_text.txt\n", MessageType::Error);
                input_file.close();
                continue;
            }

            Logger::log("Считывание дерева кодирования из файла 'encoded_text.txt'...\n\n");

            // Считываем скобочную запись дерева кодирования
            while (line != "") {
                line = "";
                std::getline(input_file, line);
                expression << line << "\n";
            }

            Decoder decoder;            // Декодировщик
            BitSequence encoded_text;   // Последовательность бит закодированного текста
            
            if (!decoder.setCodingTree(expression.str())) {
                Logger::log("Скобочная запись дерева кодирования некорректна: " + expression.str() + "\n", MessageType::Error);
                continue;
            } else {
                Logger::log("[Дерево кодирования] " + decoder.getCodingTree()->getString() + "\n\n");
            }

            Logger::log("Считывание последовательности бит из файла 'encoded_text.txt'...\n\n");

            // Считываем последовательность бит закодированного текста
            std::getline(input_file, line);
            encoded_text.reserve(line.size());
            input_file.close();

            for (auto& character : line) {
                if (character == '1') {
                    encoded_text.push_back(true);
                }
                else if (character == '0') {
                    encoded_text.push_back(false);
                }
            }

            Logger::log("[Закодированный текст] " + line + "\n\n");
            Logger::log("Декодирование текста...\n\n");

            // Декодирование текста
            std::string decoded_text;

            try {
                decoded_text = decoder.decodeText(encoded_text);
            } catch (Exception& error) {
                Logger::log("Произошла ошибка при декодировании текста: " + error.getMessage() + "\n", MessageType::Error);
                continue;
            }

            Logger::log("\nДекодирование текста завершено.\n\n");
            Logger::log("[Декодированный текст]\n" + decoded_text + "\n\n");

            // Сохранение результата в файл
            std::ofstream output_file("decoded_text.txt");
            
            // Если файл не удалось открыть
            if (!output_file.is_open()) {
                Logger::log("При открытии файла произошла ошибка: decoded_text.txt\n", MessageType::Error);
                output_file.close();
                continue;
            } 

            output_file << decoded_text;

            Logger::log("Декодированный текст записан в файл 'decoded_text.txt'.\n");
            output_file.close();
        }
        // Включение или отключение вывода промежуточной информации
        else if (action == 4 || action == 5) {
            // Включение
            if (action == 4) {
                is_debug_mode = true;
                Logger::log("Вывод промежуточных данных включен.\n");
            }
            // Отключение
            else {
                is_debug_mode = false;
                Logger::log("Вывод промежуточных данных выключен.\n");
            }

            logger.setDebugMode(is_debug_mode);
        }
        // Выход из программы
        else {
            is_loop_enabled = false;
        }
    }
	
	return 0;
}