#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>
#include "Logger.h"


template <typename T>
class BinaryTree {
private:
    T element;                    // Корень дерева
    BinaryTree* right = nullptr;  // Правое поддерево
    BinaryTree* left = nullptr;   // Левое поддерево

public:
    BinaryTree();
    bool createFromString(const char*& character);
    bool isEmpty();
    size_t getMaximumDepth(int depth = 0);
    size_t getInternalPathLength(int depth = 0);
    std::string getString();
    ~BinaryTree();
};

template<>
inline BinaryTree<char>::BinaryTree(): element('\0') {}

template <>
bool BinaryTree<char>::createFromString(const char*& character) {
	// Очищаем поддеревья (в случае, если до вызова метода дерево уже использовалось)
    delete right;
    delete left;
    right = nullptr;
    left = nullptr;
	
    // Если скобочная запись начинается с '\', то это пуcтое БД
    if (*character == '/') {
        character++;
        return true;
    }

    // Если скобочная запись начинается с '(', то это непустое БД
    if (*character == '(') {
        character++;

        // Если нам встречается значение узла дерева, то записываем его в узел
        if (*character != '(' && *character != ')' && *character != '/' && *character != ' ' && *character != '\0') {
            element = *character;
            character++;
        } else {
            return false;
        }

        // Если встречаем пробел, то пропускаем его
        if (*character == ' ') {
            character++;
        }
        // Если встречаем конец скобочной записи, то выходим
        else if (*character == ')') {
            character++;
            return true;
        }

        // Создаем левое поддерево
        if (*character != '/') {
            left = new BinaryTree;
            bool correct = left->createFromString(character);

            // Если не удалось корректно считать скобочную запись, то выходим
            if (!correct) {
                return false;
            }

        } else {
            character++;
        }

        // Если встречаем пробел, то пропускаем его
        if (*character == ' ') {
            character++;
        } 
        // Если встречаем конец скобочной записи, то выходим
        else if (*character == ')') {
            character++;
            return true;
        }

        // Создаем правое поддерево
        if (*character != '/') {
            right = new BinaryTree;
            bool correct = right->createFromString(character);

            // Если не удалось корректно считать скобочную запись, то выходим
            if (!correct) {
                return false;
            }

        } else {
            character++;
        }

        // Если встречаем конец скобочной записи, то выходим
        if (*character == ')') {
            character++;
            return true;
        }
    }

    return false;
}

template<>
inline bool BinaryTree<char>::isEmpty() {
    if (right == nullptr && left == nullptr && element == '\0') {
        return true;
    }
    return false;
}

template <typename T>
size_t BinaryTree<T>::getMaximumDepth(int depth) {
    Logger::log("Calling method getMaximumDepth() for binary tree " + getString() + ":\n", DEBUG, depth);
    size_t rightDepth = 0; // Глубина правого поддерева
    size_t leftDepth = 0; // Глубина левого поддерева

    // Если у узла есть левое поддерево
    if (left != nullptr) {
        Logger::log("Right binary subtree:\n", DEBUG, depth);
        leftDepth = left->getMaximumDepth(depth + 1) + 1; // Получаем глубину левого поддерева и к ней прибавляем 1 (для учета теукщего узла)
    }

    // Если у узла есть правое поддерево
    if (right != nullptr) {
        Logger::log("Left binary subtree:\n", DEBUG, depth);
        rightDepth = right->getMaximumDepth(depth + 1) + 1; // Получаем глубину правого поддерева и к ней прибавляем 1 (для учета теукщего узла)
    }

    // Возвращаем наибольшую глубину дерева
    if (rightDepth > leftDepth) {
        Logger::log("Method getMaximumDepth() for binary tree " + getString() + " finished: Maximum depth: " + std::to_string(rightDepth) + "\n\n", DEBUG, depth);
        return rightDepth;
    } else {
        Logger::log("Method getMaximumDepth() for binary tree " + getString() + " finished: Maximum depth: " + std::to_string(leftDepth) + "\n\n", DEBUG, depth);
        return leftDepth;
    }
}

template <typename T>
size_t BinaryTree<T>::getInternalPathLength(int depth) {
    Logger::log("Calling method getInternalPathLength() for binary tree " + getString() + ":\n", DEBUG, depth);
    size_t leftLength = 0; // Длина правого поддерева
    size_t rigthLength = 0; // Длина левого поддерева

    // Если у узла есть левое поддерево
    if (left != nullptr) {
        Logger::log("Right binary subtree:\n", DEBUG, depth);
        leftLength = left->getInternalPathLength(depth + 1); // Получаем внутренний путь левого поддерева
    }

    // Если у узла есть правое поддерево
    if (right != nullptr) {
        Logger::log("Left binary subtree:\n", DEBUG, depth);
        rigthLength = right->getInternalPathLength(depth + 1); // Получаем внутренний путь правого поддерева
    }

    Logger::log("Method getInternalPathLength() for binary tree " + getString() + " finished: Internal path length: " + std::to_string(leftLength + rigthLength + depth) + "\n\n", DEBUG, depth);
    return leftLength + rigthLength + depth; // Возвращаем внутренний путь правого, левого поддерева и глубину данного узла для получения внутрннего пути данного дерева 
}

template <>
std::string BinaryTree<char>::getString() {
    std::string result = "(";

    result += std::string(1, element); // Записыаем значение узла

    // Если левое поддерево не пусто, то добавляем его скобочную запись, иначе добавляем скобочную запись пустого БД
    if (left != nullptr) {
        result += left->getString();
    } else {
        result += "/";
    }

    // Если правое поддерево не пусто, то добавляем его скобочную запись, иначе добавляем скобочную запись пустого БД
    if (right != nullptr) {
        result += right->getString();
    } else {
        result += "/";
    }

    return result + ")";
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    delete right;
    delete left;
}


#endif // BINARY_TREE_H