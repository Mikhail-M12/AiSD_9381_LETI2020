#include "Logger.h"
#include <iostream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setSilentMode(bool value) {
    silentMode_ = value;
}

void Logger::setFileOutput(const std::string& filePath) {
    file_.close();
    file_.open(filePath);

    // Проверка открытия файла
    if (!file_.is_open()) {
        filePath_ = "";
        fileOutput_ = false;
        Logger::log("Cannot open file: " + filePath + "\n");
        return;
    }

    filePath_ = filePath;
    fileOutput_ = true;
}

void Logger::log(const std::string& message, MessageType type, int indents) {
    Logger& logger = Logger::getInstance();

    // Если включен тихий режим и сообщение - отладочное, то происходит выход из функции
    if (logger.silentMode_ && type == DEBUG) {
        return;
    }

    std::string indent(logger.indentSize_ * indents, ' '); // Получение отступа

    std::cout << indent << message; // Вывод на консоль
    if (logger.fileOutput_) {
        logger.file_ << indent << message; // Вывод в файл
    }
}
