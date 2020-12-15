#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
#include <map>

#include "BinaryTree.h"

using Character = char;
using BitSequence = std::vector<bool>;
using CharacterCodes = std::map<Character, BitSequence>;


class Decoder final {
protected:
	BinaryTree<Character>* tree_ = nullptr;

public:
	~Decoder();

	const BinaryTree<Character>* getCodingTree() const;
	bool setCodingTree(const std::string& expression);
	std::string decodeText(const BitSequence& sequence);
};


#endif // DECODER_H
