#include <iostream>
#include <sstream>

#include "Utils.h"


std::string Utils::bitSequenceToString(const BitSequence& sequence) {
	std::stringstream string;

	for (const auto& bit : sequence) {
		string << std::to_string(bit);
	}

	return string.str();
}


void Utils::clearInput() {
	// Удаляем из потока несчитанные символы до перевода на новую строку, включая его
	std::cin.clear();
	while (std::cin.get() != '\n');
}
