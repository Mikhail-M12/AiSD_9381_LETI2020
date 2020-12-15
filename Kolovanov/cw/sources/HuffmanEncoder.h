#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "Encoder.h"


class HuffmanEncoder final: public Encoder {
private:
	void calculateCharactersTree();
	void calculateCharacterCodes(const BinaryTree<Character>* tree, BitSequence& path);

public:
	BitSequence encodeText(const std::string& text) override;
};


#endif // HUFFMAN_ENCODER_H
