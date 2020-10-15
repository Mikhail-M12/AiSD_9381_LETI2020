#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>


enum MessageType {
    COMMON,
    DEBUG
};


class Logger {
    int indentSize_ = 4;        // Размер отступа
    bool silentMode_ = false;   // Тихий режим
    bool fileOutput_ = false;   // Вывод сообщений в файл
    std::string filePath_;      // Путь к выходному файлу
    std::ofstream file_;        // Дескриптор выходного файла

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger() = default;

public:
    static Logger& getInstance();
    static void log(const std::string& message, MessageType type = COMMON, int indents = 0);
    void setSilentMode(bool value);
    void setFileOutput(const std::string& filePath);
};


#endif // LOGGER_H
