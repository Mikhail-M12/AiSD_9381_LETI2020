#include "Decoder.h"
#include "Logger.h"
#include "Exception.h"


Decoder::~Decoder() {
    delete tree_;
}


const BinaryTree<Character>* Decoder::getCodingTree() const {
    return tree_;
}


bool Decoder::setCodingTree(const std::string& expression) {
	delete tree_;
	tree_ = new BinaryTree<Character>;
    const char* start = expression.c_str();
    return tree_->createFromString(start);
}


std::string Decoder::decodeText(const BitSequence& sequence) {
	std::stringstream encoded_text;
	BinaryTree<char>* subtree = tree_;

	Logger::log("Спускаемся по дереву кодирования до листьев дерева. Если встречаем 0, то идем в левое поддерева, если 1 - то в правое.\n", MessageType::Debug);
	Logger::log("При встрече листа дерева считываем очередной символ декодированного текста из листа, после чего переходим в корень дерева кодирования.\n", MessageType::Debug);

	// Проход по битам закодированного текста
	for (const auto& bit : sequence) {
		Logger::log(std::to_string(bit), MessageType::Debug);

		// В зависимости от значения бита происходит переход либо в правое поддерево, либо в левое поддерево
		if (bit) {
			subtree = subtree->getRightSubtree();
		} else {
			subtree = subtree->getLeftSubtree();
		}

		if (subtree == nullptr) {
			throw Exception("Subtree is nullptr.");
		}

		// Если достигнут лист дерева (очередной символ текста), то он добавляется в текст, и происходит переход в корень дерева
		if (subtree->isLeaf()) {
			Logger::log(" соответствует символу '" + std::string(1, subtree->getElement()) + "'\n", MessageType::Debug);
			encoded_text << subtree->getElement();
			subtree = tree_;
		}
	}

	return encoded_text.str();
}
