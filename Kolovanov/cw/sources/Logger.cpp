#include <iostream>
#include <ctime>

#include "Logger.h"
#include "Windows.h"


Logger::~Logger() {
    file_.close();
}


Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}


void Logger::setDebugMode(bool value) {
    debug_mode_ = value;
}


bool Logger::getDebugMode() {
    return debug_mode_;
}


void Logger::setOutputFile(const std::string& filepath) {
    file_.close();
    file_.open(filepath);

    // Проверка открытия файла
    if (!file_.is_open()) {
        file_output_ = false;
        Logger::log("An error occurred while opening the file to write logs: " + filepath + "\n", MessageType::Error);
        return;
    }

    file_output_ = true;
}


void Logger::log(const std::string& message, MessageType type, int indents) {
    Logger& logger = Logger::getInstance();

    // Если включен режим отладки и сообщение - отладочное, то происходит выход из функции
    if (type == MessageType::Debug && !logger.debug_mode_) {
        return;
    }

    std::string indent(logger.indent_size_ * indents, ' '); // Отступ от начала строки

    if (type == MessageType::Common || type == MessageType::Debug) {
        std::cout << indent << message;
    } else {
        std::cerr << indent << message;
    }

    if (logger.file_output_) {
        logger.file_ << indent << message;
    }
}


void Logger::setConsoleColor(Color text_color, Color background_color) {
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, (WORD)((static_cast<int>(background_color) << 4) | static_cast<int>(text_color)));
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
