#include "Logger.h"
#include "Windows.h"
#include <iostream>
#include <ctime>

Logger::~Logger() {
    file_.close();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setDebugMode(bool value) {
    debugMode_ = value;
}

bool Logger::getDebugMode() {
    return debugMode_;
}

void Logger::setOutputFile(const std::string& filePath) {
    file_.close();
    file_.open(filePath);

    // Проверка открытия файла
    if (!file_.is_open()) {
        fileOutput_ = false;
        Logger::log("Cannot open file: " + filePath + "\n", MessageType::Error);
        return;
    }

    fileOutput_ = true;
}

void Logger::log(const std::string& message, MessageType type, int indents) {
    Logger& logger = Logger::getInstance();

    // Если включен режим отладки и сообщение - отладочное, то происходит выход из функции
    if (type == MessageType::Debug && !logger.debugMode_) {
        return;
    }

    std::string indent(logger.indentSize_ * indents, ' '); // Отступ от начала строки

    if (type == MessageType::Common || type == MessageType::Debug) {
        std::cout << indent << message;
    } else {
        std::cerr << indent << message;
    }

    if (logger.fileOutput_) {
        logger.file_ << indent << message;
    }
}

void Logger::setConsoleColor(Color textColor, Color backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((static_cast<int>(backgroundColor) << 4) | static_cast<int>(textColor)));
}

std::string Logger::getCurrentDateTime() {
    tm timeinfo;                                        // Структура с информацией о времени
    time_t timestamp = time(nullptr);                   // Временная метка
    errno_t error = localtime_s(&timeinfo, &timestamp); // Получение информации о времени
    char buffer[40];                                    // Буфер для строки

    // Если возникла ошибка при получении информации о времени, то возвращаем "00-00-00_00-00-00"
    if (error) {
        return "00-00-00_00-00-00";
    } else {
        strftime(buffer, sizeof(buffer), "%d-%m-%y_%H-%M-%S", &timeinfo);
    }

    return buffer;
}
