#ifndef ALG_LAB2_LOGGER_H
#define ALG_LAB2_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    static Logger& instance();
    void log(const std::string& str, bool toConsole = true, bool toFile = true);
    void logNodeOperatorEquals(const std::string& first, const std::string& second, bool res);
private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;
    
    std::ofstream stream;
};


#endif //ALG_LAB2_LOGGER_H
