#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>


class Exception {
    const std::string error_; // C�������� ������

public:
    Exception(const std::string& error);
    const std::string& getError();
};


#endif // EXCEPTION_H