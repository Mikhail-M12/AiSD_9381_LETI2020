#include "Exception.h"

Exception::Exception(const std::string& error): error_(error) {};

const std::string& Exception::getError() {
    return error_;
}
