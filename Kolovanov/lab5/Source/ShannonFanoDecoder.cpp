#include "ShannonFanoDecoder.h"
#include "Logger.h"
#include <sstream>

std::string ShannonFanoDecoder::decodeText(BitSequence& sequence) {
	std::stringstream characterStream;
	BinaryTree<char>* subtree = tree_;
	
	// Проход по битам закодированного текста
	for (auto bit : sequence) {
		Logger::log(std::to_string(bit), MessageType::Debug);

		// В зависимости от значения бита происходит переход либо в правое поддерево, либо в левое поддерево
		if (bit) {
			subtree = subtree->getRightSubtree();
		} else {
			subtree = subtree->getLeftSubtree();
		}
		
		// Если достгнут лист дерева (очередной символ текста), то он добавляется в текст, и происходит переход в корень дерева
		if (subtree->isLeaf()) {
			Logger::log(" -> '" + std::string(1, subtree->getElement()) + "'\n", MessageType::Debug);
			characterStream << subtree->getElement();
			subtree = tree_;
		}
	}

	return characterStream.str();
}

ShannonFanoDecoder::ShannonFanoDecoder(const std::string& expression) {
	tree_ = new BinaryTree<char>(expression);
}

ShannonFanoDecoder::~ShannonFanoDecoder() {
	delete tree_;
}
