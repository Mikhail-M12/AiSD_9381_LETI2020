#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>


class Exception final {
private:
	const std::string message_;

public:
	explicit Exception(const std::string& message);
	const std::string& getMessage() const;
};


#endif // EXCEPTION_H

