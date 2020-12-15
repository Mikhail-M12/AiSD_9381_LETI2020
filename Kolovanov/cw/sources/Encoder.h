#ifndef ENCODER_H
#define ENCODER_H

#include <map>
#include <vector>
#include <string>

#include "BinaryTree.h"

using Character = char;
using BitSequence = std::vector<bool>;
using CharacterCodes = std::map<Character, BitSequence>;
using CharacterFrequency = std::pair<Character, size_t>;
using CharacterFrequencies = std::vector<CharacterFrequency>;


class Encoder {
protected:
	CharacterFrequencies frequencies_;		// Частота символов в тексте
	BinaryTree<Character>* tree_;			// Дерево кодирования
	CharacterCodes codes_;					// Коды символов алфавита

public:
	virtual ~Encoder();

	const BinaryTree<Character>* getCodingTree() const;
	const CharacterCodes& getCharacterCodes() const;
	const CharacterFrequencies& getCharacterFrequencies() const;
	const CharacterFrequencies& calculateCharacterFrequencies(const std::string& text);
	virtual BitSequence encodeText(const std::string& text) = 0;
};


#endif // ENCODER_H
