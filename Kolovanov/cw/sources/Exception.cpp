#include "Exception.h"


Exception::Exception(const std::string& message): message_(message) {}


const std::string& Exception::getMessage() const {
    return message_;
}
