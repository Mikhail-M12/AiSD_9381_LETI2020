#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
#include <map>
#include "BinaryTree.h"

typedef std::vector<bool> BitSequence;
typedef std::map<char, BitSequence> CharacterCodes;


class Decoder {
public:
	virtual std::string decodeText(BitSequence& sequence, BinaryTree<char>* tree) = 0;
};


#endif // DECODER_H
