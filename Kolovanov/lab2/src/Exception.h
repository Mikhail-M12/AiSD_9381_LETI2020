#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>


class Exception {
    const std::string error_; // Cообщение ошибки

public:
    Exception(const std::string& error);
    const std::string& getError();
};


#endif // EXCEPTION_H
