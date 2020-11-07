#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

void log(const std::string& message, std::ofstream& file, int indent = 0);
bool isChar(const char*& str, char c, std::ofstream& logfile, int indent = 0);
bool isRound(const char*& str, std::ofstream& logfile, int indent = 0);
bool isSquare(const char*& str, std::ofstream& logfile, int indent = 0);
bool isBrackets(const std::string& expression, std::ofstream& logfile);

#endif // FUNCTIONS_H
