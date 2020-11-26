#ifndef SHANNON_FANO_ENCODER_H
#define SHANNON_FANO_ENCODER_H

#include "Encoder.h"
#include "BinaryTree.h"


class ShannonFanoEncoder: public Encoder {
private:
	BinaryTree<char>* tree_ = nullptr;	// Дерево Шеннона-Фано
	CharacterCodes codes_;				// Коды символов алфавита

	BinaryTree<char>* calculateCharactersTreeAndCodes(CharactersFrequency& frequency, CharacterCodes& codes, BitSequence& path);

public:
	const BinaryTree<char>* getTree();
	CharacterCodes getCharacterCodes();
	BitSequence encodeText(const std::string& text);
	~ShannonFanoEncoder();
};


#endif // SHANNON_FANO_ENCODER_H

