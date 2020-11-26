#include "ShannonFanoEncoder.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <cmath>

BinaryTree<char>* ShannonFanoEncoder::calculateCharactersTreeAndCodes(CharactersFrequency& frequency, CharacterCodes& codes, BitSequence& path) {
	BinaryTree<char>* tree = new BinaryTree<char>;
	CharactersFrequency left;
	CharactersFrequency right;
	long long minDelta = LLONG_MAX;

	std::string pathString;
	for (size_t i = 0; i < path.size(); i++) {
		pathString += std::to_string(path[i]);
	}

	// Если кодировать нечего - то возвращается пустое дерево
	if (frequency.size() == 0) {
		return tree;
	}
	// Если в списке частоты символов осталось одно значение, то происходит присваивание текущему узлу дерева символа
	// и добавление кода текущего символа в массив кодов символов алфавита
	else if (frequency.size() == 1) {
		if (path.size() == 0) {
			path.push_back(false);
			tree->setLeftSubtree(calculateCharactersTreeAndCodes(frequency, codes, path));
			path.pop_back();
		} else {
			Logger::log("Placing character '" + std::string(1, frequency[0].first) + "' to node " + pathString + "\n", MessageType::Debug, path.size());
			codes[frequency[0].first] = path;
			tree->setElement(frequency[0].first);
		}
		return tree;
	}
	// Если в списке частоты символов осталось более одного значение, то происходит разделение этого списка на два
	else {
		size_t middleIndex = 0;
		long long leftSum = 0;
		long long rightSum = 0;

		for (size_t i = 0; i < frequency.size(); i++) {
			rightSum += frequency[i].second;
		}

		// Находим такой k, при котором различие между суммой частот двух списков минимально 
		for (size_t k = 0; k < frequency.size(); k++) {
			leftSum += frequency[k].second;
			rightSum -= frequency[k].second;

			if (abs(rightSum - leftSum) < abs(minDelta)) {
				middleIndex = k;
				minDelta = rightSum - leftSum;
			}
		}

		// Заполняем левый и правый подсписки списка
		for (size_t i = 0; i <= middleIndex; i++) {
			left.push_back(frequency[i]);
		}
		for (size_t i = middleIndex + 1; i < frequency.size(); i++) {
			right.push_back(frequency[i]);
		}

		leftSum = 0;
		rightSum = 0;

		Logger::log("Characters frequency: ", MessageType::Debug, path.size());
		for (size_t i = 0; i < left.size(); i++) {
			Logger::log(std::string(1, left[i].first), MessageType::Debug);
			leftSum += left[i].second;
		}
		Logger::log("(" + std::to_string(leftSum) + ") ", MessageType::Debug);
		for (size_t i = 0; i < right.size(); i++) {
			Logger::log(std::string(1, right[i].first), MessageType::Debug);
			rightSum += right[i].second;
		}
		Logger::log("(" + std::to_string(rightSum) + ")\n", MessageType::Debug);
	}

	// Если правая сумма меньше левой, то меняем их местами
	if (minDelta < 0) {
		std::swap(left, right);
	}

	// Создаем левое поддерево
	Logger::log("Creating left subtree (" + pathString + "0):\n", MessageType::Debug, path.size());
	path.push_back(false);
	tree->setLeftSubtree(calculateCharactersTreeAndCodes(left, codes, path));
	path.pop_back();

	// Создаем правое поддерево
	Logger::log("Creating right subtree (" + pathString + "1):\n", MessageType::Debug, path.size());
	path.push_back(true);
	tree->setRightSubtree(calculateCharactersTreeAndCodes(right, codes, path));
	path.pop_back();

	return tree;
}

const BinaryTree<char>* ShannonFanoEncoder::getTree() {
	return tree_;
}

CharacterCodes ShannonFanoEncoder::getCharacterCodes() {
	return codes_;
}

BitSequence ShannonFanoEncoder::encodeText(const std::string& text) {
	BitSequence encodedText;

	// Получаем частоту символов текста
	calculateTextCharacterFrequencies(text);

	// Строим дерево Шеннона-Фано
	Logger::log("\nBuilding Shennon-Fano tree...\n", MessageType::Debug);
	delete tree_;
	tree_ = calculateCharactersTreeAndCodes(frequencies_, codes_, encodedText);
	encodedText.clear();

	Logger::log("\nReplace text characters with their codes:\n", MessageType::Debug);
	// Пробегаемся по символам текста и кодируем их
	for (auto character : text) {
		std::stringstream codeString;
		BitSequence& code = codes_[character];
		
		for (size_t i = 0; i < code.size(); i++) {
			encodedText.push_back(code[i]);
			codeString << code[i];
		}

		Logger::log("'" + std::string(1, character) + "' -> " + codeString.str() + "\n", MessageType::Debug);
	}
	Logger::log("\n", MessageType::Debug);

	return encodedText;
}

ShannonFanoEncoder::~ShannonFanoEncoder() {
	delete tree_;
}
