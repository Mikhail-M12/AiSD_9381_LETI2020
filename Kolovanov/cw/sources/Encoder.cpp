#include <algorithm>

#include "Encoder.h"
#include "Logger.h"


Encoder::~Encoder() {
	delete tree_;
}


const BinaryTree<Character>* Encoder::getCodingTree() const {
	return tree_;
}


const CharacterCodes& Encoder::getCharacterCodes() const {
	return codes_;
}


const CharacterFrequencies& Encoder::getCharacterFrequencies() const {
	return frequencies_;
}


const CharacterFrequencies& Encoder::calculateCharacterFrequencies(const std::string& text) {
	frequencies_.clear();

	Logger::log("\n[Шаг 1] Считаем частоту вхождений символов текста и сортируем их по убыванию количества вхождений с учетом лексиграфического порядка.\n\n", MessageType::Debug);

	// Пробегаемся по символам текста и подсчитываем их
	for (auto& character : text) {
		bool found = false;

		for (auto& element : frequencies_) {
			if (element.first == character) {
				element.second++;
				found = true;
				break;
			}
		}

		if (!found) {
			frequencies_.push_back(CharacterFrequency(character, 1));
		}
	}

	// Сортируем частоты символов по убыванию с учетом лексеграфического порядка
	std::sort(frequencies_.begin(), frequencies_.end(), [](const CharacterFrequency& f1, const CharacterFrequency& f2) {
		if (f1.second != f2.second) {
			return f1.second > f2.second;
		} else {
			return f1.first < f2.first;
		}
	});

	Logger::log("Частота вхождений символов в текст: ", MessageType::Debug);

	for (auto& f : frequencies_) {
		Logger::log(std::string(1, f.first) + "(" + std::to_string(f.second) + ") ", MessageType::Debug);
	}

	Logger::log("\n", MessageType::Debug);

	return frequencies_;
}
