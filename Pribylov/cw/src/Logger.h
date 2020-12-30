#ifndef TREAP_LOGGER_H
#define TREAP_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    static Logger& instance();
    void log(const std::string& str, bool toConsole = true, bool toFile = true);

    std::ofstream stream;

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
};


#endif //TREAP_LOGGER_H
