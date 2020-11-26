#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
#include <string>
#include <map>
#include "BinaryTree.h"

typedef std::vector<bool> BitSequence;							// ������������������ ��� - ������ �������� ���� bool (true - 1, false - 0)
typedef std::pair<char, size_t> CharacterFrequency;				// ������� ������� - ���� �� �������� ������� � ��� ������� (���������� ��������� � �����)
typedef std::vector<CharacterFrequency> CharactersFrequency;	// ������� �������� - ������ ������� ��������
typedef std::map<char, BitSequence> CharacterCodes;				// ���� �������� - �������, ���� �������� ������������� �������, � �������� - ���� ����� �������


class Encoder {
protected:
	CharactersFrequency frequencies_;	// ������� �������� � ������

public:
	CharactersFrequency getCharacterFrequencies();
	CharactersFrequency calculateTextCharacterFrequencies(const std::string& text);
	virtual BitSequence encodeText(const std::string& text) = 0;
};


#endif // ENCODER_H
