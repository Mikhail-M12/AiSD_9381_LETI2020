#include <sstream>
#include <cmath>

#include "ShannonFanoEncoder.h"
#include "Logger.h"
#include "Utils.h"


BinaryTree<Character>* ShannonFanoEncoder::calculateCharactersTreeAndCodes(CharacterFrequencies& frequency, BitSequence& path) {
	BinaryTree<Character>* tree = new BinaryTree<Character>;	// Новый узел дерева кодирования
	CharacterFrequencies left;									// Частота символов для левого поддерева
	CharacterFrequencies right;									// Частота символов для правого поддерева
	std::string path_string = Utils::bitSequenceToString(path);	// Путь до текущего узла дерева
	long long sum = 0;					// Сумма частот символов текущего узла дерева

	Logger::log("Частота символов для текущего узла дерева (путь до узла - " + path_string + "): ", MessageType::Debug, path.size());
	
	for (size_t i = 0; i < frequency.size(); i++) {
		Logger::log(std::string(1, frequency[i].first), MessageType::Debug);
		sum += frequency[i].second;
	}

	Logger::log("(" + std::to_string(sum) + ")\n", MessageType::Debug);

	tree->setWeight(sum);

	// Если кодировать нечего - то возвращается пустое дерево
	if (frequency.size() == 0) {
		return tree;
	}
	// Если в списке частоты символов осталось одно значение, то происходит присваивание текущему узлу дерева символа
	// и добавление кода текущего символа в массив кодов символов алфавита
	else if (frequency.size() == 1) {
		if (path.size() == 0) {
			path.push_back(true);
			tree->setRightSubtree(calculateCharactersTreeAndCodes(frequency, path));
			path.pop_back();
		} else {
			Logger::log("Помещаем символ '" + std::string(1, frequency[0].first) + "' в текущий узел дерева (путь до узла - " + path_string + ") и задаем в качестве кода текущего символа путь до текущего узла дерева.\n", MessageType::Debug, path.size());
			codes_[frequency[0].first] = path;
			tree->setElement(frequency[0].first);
		}
		return tree;
	}
	// Если в списке частоты символов осталось более одного значение, то происходит разделение этого списка на два
	else {
		size_t middle_index = 0;
		long long left_sum = 0;
		long long right_sum = 0;
		long long min_delta = LLONG_MAX;

		for (size_t i = 0; i < frequency.size(); i++) {
			right_sum += frequency[i].second;
		}

		// Находим такой k, при котором различие между суммой частот двух списков минимально 
		for (size_t k = 0; k < frequency.size(); k++) {
			left_sum += frequency[k].second;
			right_sum -= frequency[k].second;

			if (abs(right_sum - left_sum) < abs(min_delta)) {
				middle_index = k;
				min_delta = right_sum - left_sum;
			}
		}

		Logger::log("Разделяем список частот. Индекс разделяющего элемента: " + std::to_string(middle_index) + ".\n", MessageType::Debug, path.size());

		// Заполняем левый и правый подсписки списка
		for (size_t i = 0; i <= middle_index; i++) {
			left.push_back(frequency[i]);
		}

		for (size_t i = middle_index + 1; i < frequency.size(); i++) {
			right.push_back(frequency[i]);
		}

		// Если правая сумма меньше левой, то меняем их местами
		if (min_delta < 0) {
			std::swap(left, right);
		}

		left_sum = 0;
		right_sum = 0;

		Logger::log("Частоты символов для левого поддерева: ", MessageType::Debug, path.size());

		for (size_t i = 0; i < left.size(); i++) {
			Logger::log(std::string(1, left[i].first), MessageType::Debug);
			left_sum += left[i].second;
		}

		Logger::log("(" + std::to_string(left_sum) + ")\n", MessageType::Debug);
		Logger::log("Частоты символов для правого поддерева: ", MessageType::Debug, path.size());

		for (size_t i = 0; i < right.size(); i++) {
			Logger::log(std::string(1, right[i].first), MessageType::Debug);
			right_sum += right[i].second;
		}

		Logger::log("(" + std::to_string(right_sum) + ")\n", MessageType::Debug);
	}

	// Создаем левое поддерево
	Logger::log("Создаем левое поддерево для текущего узла дерева (путь до узла - " + path_string + "0):\n", MessageType::Debug, path.size());
	path.push_back(false);
	tree->setLeftSubtree(calculateCharactersTreeAndCodes(left, path));
	path.pop_back();

	// Создаем правое поддерево
	Logger::log("Создаем правое поддерево для текущего узла дерева (путь до узла - " + path_string + "1):\n", MessageType::Debug, path.size());
	path.push_back(true);
	tree->setRightSubtree(calculateCharactersTreeAndCodes(right, path));
	path.pop_back();

	return tree;
}


BitSequence ShannonFanoEncoder::encodeText(const std::string& text) {
	BitSequence encoded_text;

	// Находим частоту символов текста
	calculateCharacterFrequencies(text);

	// Строим дерево Шеннона-Фано
	Logger::log("\n[Шаг 2] Построение дерева кодирования Шеннона-Фано и сопоставление кода каждому символу алфавита текста.\n\n", MessageType::Debug);
	
	delete tree_;
	tree_ = calculateCharactersTreeAndCodes(frequencies_, encoded_text);
	encoded_text.clear();

	Logger::log("\n[Шаг 3] Кодирование каждого символа текста:\n\n", MessageType::Debug);

	// Пробегаемся по символам текста и кодируем их
	for (auto& character : text) {
		std::stringstream code_string;
		BitSequence& code = codes_[character];
		
		for (size_t i = 0; i < code.size(); i++) {
			encoded_text.push_back(code[i]);
			code_string << code[i];
		}

		Logger::log("Символу '" + std::string(1, character) + "' соответствует код " + code_string.str() + "\n", MessageType::Debug);
	}

	Logger::log("\n", MessageType::Debug);

	return encoded_text;
}
