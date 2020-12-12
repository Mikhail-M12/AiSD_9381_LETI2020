#include "Logger.h"

Logger::Logger() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char logFileName[32];
    strftime(logFileName, 32, "log_%F_%T.txt", now);
    stream.open(logFileName);
}

Logger::~Logger() {
    stream.close();
}

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& str, bool toConsole, bool toFile) {
    if (toConsole) std::cout << str << '\n';
    if (toFile) stream << str << '\n';
}

void Logger::logNodeOperatorEquals(const std::string &first, const std::string &second, bool res) {
    std::cout << "Узлы \"" << first << "\" и \"" << second << (res ? "\" идентичны.\n" : "\" не идентичны.\n");
    stream << "Узлы \"" << first << "\" и \"" << second << (res ? "\" идентичны.\n" : "\" не идентичны.\n");
}