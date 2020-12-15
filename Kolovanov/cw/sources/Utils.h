#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using BitSequence = std::vector<bool>;


class Utils final {
public:
	static std::string bitSequenceToString(const BitSequence& sequence);
	static void clearInput();
};


#endif // UTILS_H
