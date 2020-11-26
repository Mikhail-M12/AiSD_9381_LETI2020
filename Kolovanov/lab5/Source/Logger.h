#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include "MessageType.h"
#include "Color.h"


class Logger {
    int indentSize_ = 4;        // ������ �������
    bool debugMode_ = false;    // ����� ������ ���������� ���������
    bool fileOutput_ = false;   // ����� ��������� � ����
    std::ofstream file_;        // ���������� ��������� �����

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger();

public:
    static Logger& getInstance();
    static void log(const std::string& message, MessageType type = MessageType::Common, int indents = 0);
    static void setConsoleColor(Color textColor, Color backgroundColor);
    void setOutputFile(const std::string& filePath);
    void setDebugMode(bool value);
    bool getDebugMode();
    static std::string getCurrentDateTime();
};


#endif // LOGGER_H
