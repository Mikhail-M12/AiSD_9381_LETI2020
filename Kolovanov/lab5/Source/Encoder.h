#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
#include <string>
#include <map>
#include "BinaryTree.h"

typedef std::vector<bool> BitSequence;							// Последовательность бит - вектор значений типа bool (true - 1, false - 0)
typedef std::pair<char, size_t> CharacterFrequency;				// Частота символа - пара из значения символа и его частоты (количество вхождений в текст)
typedef std::vector<CharacterFrequency> CharactersFrequency;	// Частота символов - вектор частоты символов
typedef std::map<char, BitSequence> CharacterCodes;				// Коды символов - словарь, ключ которого соответствуют символу, а значение - коду этого символа


class Encoder {
protected:
	CharactersFrequency frequencies_;	// Частота символов в тексте

public:
	CharactersFrequency getCharacterFrequencies();
	CharactersFrequency calculateTextCharacterFrequencies(const std::string& text);
	virtual BitSequence encodeText(const std::string& text) = 0;
};


#endif // ENCODER_H
