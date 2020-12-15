#ifndef SHANNON_FANO_ENCODER_H
#define SHANNON_FANO_ENCODER_H

#include "Encoder.h"


class ShannonFanoEncoder final: public Encoder {
private:
	BinaryTree<Character>* calculateCharactersTreeAndCodes(CharacterFrequencies& frequency, BitSequence& path);

public:
	BitSequence encodeText(const std::string& text) override;
};


#endif // SHANNON_FANO_ENCODER_H

