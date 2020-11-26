#ifndef SHANNON_FANO_DECODER_H
#define SHANNON_FANO_DECODER_H

#include "Decoder.h"


class ShannonFanoDecoder {
private:
	BinaryTree<char>* tree_ = nullptr;	// Дерево Шеннона-Фано

public:
	ShannonFanoDecoder(const std::string& expression);
	std::string decodeText(BitSequence& sequence);
	~ShannonFanoDecoder();
};


#endif // SHANNON_FANO_DECODER_H
