#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>
#include "Logger.h"


template <typename T>
class BinaryTree {
private:
    T element;                    // Значение узла дерева
    BinaryTree* right = nullptr;  // Правое поддерево
    BinaryTree* left = nullptr;   // Левое поддерево

public:
    BinaryTree() = default;
    BinaryTree(const char*& character);
    size_t getMaximumDepth(int depth = 0);
    size_t getInternalPathLength(int depth = 0);
    std::string getString();
    ~BinaryTree();
};

template <>
BinaryTree<char>::BinaryTree(const char*& character): element('\0') {
    // Если скобочная запись не начинается с '(', то выходим
    if (*character == '(') {
        character++;

        // Если нам встречается значение узла дерева, то записываем его в узел, иначе выходим из конструктора
        if (*character != '(' && *character != ')' && *character != ' ' && *character != '\0') {
            element = *character;
            character++;
        } else {
            return;
        }

        // Если встречается пробел, то идем на следующий символ
        if (*character == ' ') {
            character++;
        }

        // Если встречается '(', то создаем левое поддерево
        if (*character == '(') {
            left = new BinaryTree(character);

            // Если успешно считали левое поддерево, то идем далее, иначе выходим из конструктора
            if (*character == ')') {
                character++;
            } else {
                return;
            }

            // Если встречается пробел, то идем на следующий символ
            if (*character == ' ') {
                character++;
            }

            // Если встречается '(', то создаем правое поддерево
            if (*character == '(') {
                right = new BinaryTree(character);

                // Если успешно считали левое поддерево, то идем далее, иначе выходим из конструктора
                if (*character == ')') {
                    character++;
                } else {
                    return;
                }
            }
        }
    }
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

    // Если левое поддерево не пусто, то записываем скобочную запись левого поддерева
    if (left != nullptr) {
        result += left->getString();
    }

    // Если правое поддерево не пусто, то записываем скобочную запись правого поддерева
    if (right != nullptr) {
        result += right->getString();
    }

    return result + ")";
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    delete right;
    delete left;
}


#endif // BINARY_TREE_H