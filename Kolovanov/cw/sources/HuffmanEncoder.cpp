#include <algorithm>

#include "HuffmanEncoder.h"
#include "Logger.h"
#include "Utils.h"


void HuffmanEncoder::calculateCharactersTree() {
	std::vector<BinaryTree<Character>*> tree_nodes(frequencies_.size());	// Вектор узлов дерева кодирования

	for (size_t i = 0; i < tree_nodes.size(); i++) {
		tree_nodes[i] = new BinaryTree<Character>(frequencies_[i].first, frequencies_[i].second);
	}

	// До тех пор, пока в векторе узлов дерева кодирования больше 1 узла
	while (tree_nodes.size() > 1) {
		size_t nodes_size = tree_nodes.size();

		Logger::log("\nСписок узлов: ", MessageType::Debug);

		for (size_t i = 0; i < nodes_size; i++) {
			Logger::log(tree_nodes[i]->getElementString() + "(" + std::to_string(tree_nodes[i]->getWeight()) + ") ", MessageType::Debug);
		}

		// Производим объединение двух последних узлов дерева кодирования (с наименьшими весами)
		BinaryTree<Character>* new_node = new BinaryTree<Character>('\0', tree_nodes[nodes_size - 1]->getWeight() + tree_nodes[nodes_size - 2]->getWeight());
		new_node->setLeftSubtree(tree_nodes[nodes_size - 2]);
		new_node->setRightSubtree(tree_nodes[nodes_size - 1]);
		tree_nodes.resize(nodes_size - 2);
		nodes_size -= 2;

		Logger::log("\nСоеденим два узла с наименьшими весами (два последних узла) в один узел: " + new_node->getElementString() + "(" + std::to_string(new_node->getWeight()) + ")\n", MessageType::Debug);
		Logger::log("Вставляем новый узел в список узлов таким образом, чтобы список остался упорядоченным.\n", MessageType::Debug);

		// Вставляем новый узел в вектор узлов дерева кодирования 
		if (nodes_size == 0 || new_node->getWeight() > tree_nodes[0]->getWeight()) {
			tree_nodes.insert(tree_nodes.begin(), new_node);
			Logger::log("Вставка нового узла в начало списка.\n", MessageType::Debug);
		} else if (new_node->getWeight() <= tree_nodes[nodes_size - 1]->getWeight()) {
			tree_nodes.insert(tree_nodes.end(), new_node);
			Logger::log("Вставка нового узла в конец списка.\n", MessageType::Debug);
		} else {
			for (auto i = tree_nodes.begin(); i < tree_nodes.end() - 1; ++i) {
				if ((*i)->getWeight() >= new_node->getWeight() && (*(i + 1))->getWeight() < new_node->getWeight()) {
					tree_nodes.insert(i + 1, new_node);
					Logger::log("Вставка нового узла на место с индексом " + std::to_string(std::distance(tree_nodes.begin(), i + 1)) + ".\n", MessageType::Debug);
					break;
				}
			}
		}
	}

	if (frequencies_.size() == 0) {
		tree_nodes.push_back(new BinaryTree<Character>);
	} else if (frequencies_.size() == 1) {
		BinaryTree<Character>* new_node = new BinaryTree<Character>('\0', tree_nodes[0]->getWeight());
		new_node->setRightSubtree(tree_nodes[0]);
		tree_nodes[0] = new_node;
	}

	// Устанавливаем новое дерево кодирования
	delete tree_;
	tree_ = tree_nodes[0];
}


void HuffmanEncoder::calculateCharacterCodes(const BinaryTree<Character>* tree, BitSequence& path) {
	// Если достигли листа дерева - то добавляем в словарь кодов символ и соответствующий ему код
	if (tree->isLeaf()) {
		Logger::log("Символу '" + std::string(1, tree->getElement()) + "' соответствует код " + Utils::bitSequenceToString(path) + "\n", MessageType::Debug);
		codes_[tree->getElement()] = path;
		return;
	}
	
	// Иначе производим поиск листьев в поддеревьях данного дерева
	const BinaryTree<Character>* left = tree->getLeftSubtree();
	const BinaryTree<Character>* right = tree->getRightSubtree();

	if (left != nullptr) {
		path.push_back(false);
		calculateCharacterCodes(left, path);
		path.pop_back();
	}

	if (right != nullptr) {
		path.push_back(true);
		calculateCharacterCodes(right, path);
		path.pop_back();
	}
}


BitSequence HuffmanEncoder::encodeText(const std::string& text) {
	BitSequence encoded_text;

	// Находим частоту символов текста
	calculateCharacterFrequencies(text);

	// Строим дерево Хаффмана
	Logger::log("\n[Шаг 2] Построение дерева кодирования Хаффмана:\n", MessageType::Debug);
	
	calculateCharactersTree();

	Logger::log("\n[Шаг 3] Сопоставление кода каждому символу алфавита текста при помощи обхода дерева кодирования:\n\n", MessageType::Debug);

	calculateCharacterCodes(tree_, encoded_text);

	Logger::log("\n[Шаг 4] Кодирование каждого символа текста:\n\n", MessageType::Debug);

	// Пробегаемся по символам текста и кодируем их
	for (auto& character : text) {
		std::stringstream code_string;
		BitSequence& code = codes_[character];

		for (size_t i = 0; i < code.size(); i++) {
			encoded_text.push_back(code[i]);
			code_string << code[i];
		}

		Logger::log("'" + std::string(1, character) + "' -> " + code_string.str() + "\n", MessageType::Debug);
	}
	Logger::log("\n", MessageType::Debug);

	return encoded_text;
}
