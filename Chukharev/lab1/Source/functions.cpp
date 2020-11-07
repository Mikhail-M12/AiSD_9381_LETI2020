#include <iostream>
#include <fstream>
#include "functions.h"

// Построить синтаксический анализатор для понятия скобки.
// скобки::=квадратные | круглые
// квадратные:: = [ [ квадратные ] ( круглые ) ] | B
// круглые::=( ( круглые ) [ квадратные ] ) | А

void log(const std::string& message, std::ofstream& file, int indent) {
    std::cout << std::string(4 * indent, ' ') << message;
    file << std::string(4 * indent, ' ') << message;
}

bool isChar(const char*& str, char c, std::ofstream& logfile, int indent) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    log("Function isChar('" + std::string(1, *str) + "', '" + c + "') is called [deep=" + std::to_string(indent) + "]\n", logfile, indent);

    if (*str == c) {
        str++; // Идем на следующий символ
        result = true;
    }

    // Вывод результата
    if (result) {
        log("Result: '" + std::string(1, *start) + "' is '" + c + "'\n", logfile, indent);
    } else {
        log("Result: '" + std::string(1, *start) + "' is not '" + c + "'\n", logfile, indent);
    }

    return result;
}

bool isRound(const char*& str, std::ofstream& logfile, int indent) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    log("Function isRound() is called [deep=" + std::to_string(indent) + "]\n", logfile, indent);

    if (isChar(str, 'A', logfile, indent + 1)) {
        result = true;
    } else if (isChar(str, '(', logfile, indent + 1) && isChar(str, '(', logfile, indent + 1) && 
               isRound(str, logfile, indent + 1) && isChar(str, ')', logfile, indent + 1) && 
               isChar(str, '[', logfile, indent + 1) && isSquare(str, logfile, indent + 1) && 
               isChar(str, ']', logfile, indent + 1) && isChar(str, ')', logfile, indent + 1)) {
        result = true;
    }

    if (!result) {
        str = start;
    }

    std::string round(start, str - start); // Найденные функцией круглые скобки

    // Вывод результата
    if (result) {
        log("Result: '" + round + "' is round\n", logfile, indent);
    } else {
        log("Result: is not round\n", logfile, indent);
    }

    return result;
}

bool isSquare(const char*& str, std::ofstream& logfile, int indent) {
    const char* start = str; // Первый символ в строке до начала работы функции
    bool result = false;

    log("Function isSquare() is called [deep=" + std::to_string(indent) + "]\n", logfile, indent);

    if (isChar(str, 'B', logfile, indent + 1)) {
        result = true;
    } else if (isChar(str, '[', logfile, indent + 1) && isChar(str, '[', logfile, indent + 1) && 
               isSquare(str, logfile, indent + 1) && isChar(str, ']', logfile, indent + 1) && 
               isChar(str, '(', logfile, indent + 1) && isRound(str, logfile, indent + 1) && 
               isChar(str, ')', logfile, indent + 1) && isChar(str, ']', logfile, indent + 1)) 
    {
        result = true;
    }

    if (!result) {
        str = start;
    }

    std::string square(start, str - start); // Найденные функцией квадратные скобки

    // Вывод результата
    if (result) {
        log("Result: '" + square + "' is square\n", logfile, indent);
    } else {
        log("Result: is not square\n", logfile, indent);
    }

    return result;
}

bool isBrackets(const std::string& expression, std::ofstream& logfile) {
    const char* end = expression.c_str(); // Получение С-style строки
    bool result = false;

    log("Function isSquare() is called [deep=0]\n", logfile);

    if (isRound(end, logfile, 1) || isSquare(end, logfile, 1)) {
        if (*end == '\0') { // Проверяем, что вся строка соответствует определению
            result = true;
        }
    }

    return result;
}
