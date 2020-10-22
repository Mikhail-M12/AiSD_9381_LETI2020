#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>
#include "Logger.h"


template <typename T>
class BinaryTree {
private:
    T element;                    // �������� ���� ������
    BinaryTree* right = nullptr;  // ������ ���������
    BinaryTree* left = nullptr;   // ����� ���������

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
    // ���� ��������� ������ �� ���������� � '(', �� �������
    if (*character == '(') {
        character++;

        // ���� ��� ����������� �������� ���� ������, �� ���������� ��� � ����, ����� ������� �� ������������
        if (*character != '(' && *character != ')' && *character != ' ' && *character != '\0') {
            element = *character;
            character++;
        } else {
            return;
        }

        // ���� ����������� ������, �� ���� �� ��������� ������
        if (*character == ' ') {
            character++;
        }

        // ���� ����������� '(', �� ������� ����� ���������
        if (*character == '(') {
            left = new BinaryTree(character);

            // ���� ������� ������� ����� ���������, �� ���� �����, ����� ������� �� ������������
            if (*character == ')') {
                character++;
            } else {
                return;
            }

            // ���� ����������� ������, �� ���� �� ��������� ������
            if (*character == ' ') {
                character++;
            }

            // ���� ����������� '(', �� ������� ������ ���������
            if (*character == '(') {
                right = new BinaryTree(character);

                // ���� ������� ������� ����� ���������, �� ���� �����, ����� ������� �� ������������
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
    size_t rightDepth = 0; // ������� ������� ���������
    size_t leftDepth = 0; // ������� ������ ���������

    // ���� � ���� ���� ����� ���������
    if (left != nullptr) {
        Logger::log("Right binary subtree:\n", DEBUG, depth);
        leftDepth = left->getMaximumDepth(depth + 1) + 1; // �������� ������� ������ ��������� � � ��� ���������� 1 (��� ����� �������� ����)
    }

    // ���� � ���� ���� ������ ���������
    if (right != nullptr) {
        Logger::log("Left binary subtree:\n", DEBUG, depth);
        rightDepth = right->getMaximumDepth(depth + 1) + 1; // �������� ������� ������� ��������� � � ��� ���������� 1 (��� ����� �������� ����)
    }

    // ���������� ���������� ������� ������
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
    size_t leftLength = 0; // ����� ������� ���������
    size_t rigthLength = 0; // ����� ������ ���������

    // ���� � ���� ���� ����� ���������
    if (left != nullptr) {
        Logger::log("Right binary subtree:\n", DEBUG, depth);
        leftLength = left->getInternalPathLength(depth + 1); // �������� ���������� ���� ������ ���������
    }

    // ���� � ���� ���� ������ ���������
    if (right != nullptr) {
        Logger::log("Left binary subtree:\n", DEBUG, depth);
        rigthLength = right->getInternalPathLength(depth + 1); // �������� ���������� ���� ������� ���������
    }

    Logger::log("Method getInternalPathLength() for binary tree " + getString() + " finished: Internal path length: " + std::to_string(leftLength + rigthLength + depth) + "\n\n", DEBUG, depth);
    return leftLength + rigthLength + depth; // ���������� ���������� ���� �������, ������ ��������� � ������� ������� ���� ��� ��������� ���������� ���� ������� ������ 
}

template <>
std::string BinaryTree<char>::getString() {
    std::string result = "(";

    result += std::string(1, element); // ��������� �������� ����

    // ���� ����� ��������� �� �����, �� ���������� ��������� ������ ������ ���������
    if (left != nullptr) {
        result += left->getString();
    }

    // ���� ������ ��������� �� �����, �� ���������� ��������� ������ ������� ���������
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