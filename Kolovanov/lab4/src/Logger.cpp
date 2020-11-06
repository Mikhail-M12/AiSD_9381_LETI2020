#include "Logger.h"
#include <iostream>
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setSilentMode(bool value) {
    silentMode_ = value;
}

bool Logger::getSilentMode() {
    return silentMode_;
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

    std::string indent(logger.indentSize_ * indents, ' '); // Формирование отступа

    std::cout << indent << message; // Вывод на консоль
    if (logger.fileOutput_) {
        logger.file_ << indent << message; // Вывод в файл
    }
}

std::string Logger::getCurrentDateTime() {
    tm timeinfo;                                        // Структура с информацией о времени
    char buffer[80] = { '\0' };                         // Буфер для строки
    time_t timestamp = time(nullptr);                   // Временная метка
    errno_t error = localtime_s(&timeinfo, &timestamp); // Получение информации о времени

    // Если возникла ошибка при получении информации о времени, то возвращаем "00-00-00_00-00-00"
    if (error) {
        return "00-00-00_00-00-00";
    }
    else {
        strftime(buffer, sizeof(buffer), "%d-%m-%y_%H-%M-%S", &timeinfo);
    }

    return buffer;
}
