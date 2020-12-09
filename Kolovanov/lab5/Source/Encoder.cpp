#include "Encoder.h"
#include "Logger.h"
#include <algorithm>

CharactersFrequency Encoder::calculateTextCharacterFrequencies(const std::string& text) {
	frequencies_.clear();
	Logger::log("\nCounting the frequency of characters in text...\n", MessageType::Debug);

	// Пробегаемся по символам текста и считаем их
	for (auto symbol : text) {
		size_t position = 0;
		bool inData = false;

		for (auto& element : frequencies_) {
			if (element.first == symbol) {
				inData = true;
				break;
			}

			position++;
		}

		if (inData) {
			frequencies_[position].second++;
		} else {
			frequencies_.push_back(CharacterFrequency(symbol, 1));
		}
	}

	// Сортируем частоты по убыванию с учетом лексеграфического порядка
	std::sort(frequencies_.begin(), frequencies_.end(), [](const CharacterFrequency& f1, const CharacterFrequency& f2) {
		if (f1.second != f2.second) {
			return f1.second > f2.second;
		} else {
			return f1.first < f2.first;
		}
	});

	Logger::log("Frequency of characters in text: ", MessageType::Debug);
	for (auto& f : frequencies_) {
		Logger::log(std::string(1, f.first) + "(" + std::to_string(f.second) + ") ", MessageType::Debug);
	}
	Logger::log("\n", MessageType::Debug);

	return frequencies_;
}

CharactersFrequency Encoder::getCharacterFrequencies() {
	return frequencies_;
}
