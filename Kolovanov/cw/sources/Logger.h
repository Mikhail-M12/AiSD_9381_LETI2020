#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#include "MessageType.h"
#include "Color.h"


class Logger final {
    int indent_size_ = 4;        // Размер отступа
    bool debug_mode_ = false;    // Режим вывода отладочных сообщений
    bool file_output_ = false;   // Вывод сообщений в файл
    std::ofstream file_;         // Дескриптор выходного файла

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger();

public:
    static Logger& getInstance();
    static void log(const std::string& message, MessageType type = MessageType::Common, int indents = 0);
    static void setConsoleColor(Color text_color, Color background_color);
    void setOutputFile(const std::string& filepath);
    void setDebugMode(bool value);
    bool getDebugMode();
    static std::string getCurrentDateTime();
};


#endif // LOGGER_H
