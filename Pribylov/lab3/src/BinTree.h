#ifndef ALG_LAB3_BINTREE_H
#define ALG_LAB3_BINTREE_H

#include <string>
#include <cstring>
#include <stdexcept>
#include "Logger.h"

namespace BinTree {

    template<typename T>
    class BinTree {
        T data;
        BinTree* leftTree = nullptr;
        BinTree* rightTree = nullptr;

    public:
        explicit BinTree(T val);
        explicit BinTree(const std::string& str);
        ~BinTree();
        bool operator==(const BinTree& other);
        bool operator!=(const BinTree& other);

        bool isLeaf() const; // проверяет, является ли текущее дерево листом (не имеет потомков)
        bool isArithmeticExpression() const; // проверяет, явлется ли дерево корректным арифметическим выражений
        std::string toStringPreOrder() const; // преобразует дерево в строку с арифметическим выражением в префиксной нотации
        std::string toStringInOrder() const; // преобразует дерево в строку с арифметическим выражением в классической (инфиксной) нотации
        void sumToMul(); // преобразует узлы вида (f+f) в (2*f)
    private:
        BinTree(const BinTree&) = delete;
        BinTree(BinTree&&) = delete;
        BinTree& operator=(const BinTree&) = delete;
        BinTree&& operator=(BinTree&&) = delete;
        void readFromStringPrefix(const std::string& str, int& pos); // создаёт дерево на основе строки с арифметическим выражением в префиксной нотации
        void readFromStringInfix(const std::string& str, int& pos); // создаёт дерево на основе строки с арифметическим выражением в классической (инфиксной) нотации
    };


    template<>
    bool BinTree<char>::isArithmeticExpression() const {

        if ((leftTree == nullptr) != (rightTree == nullptr))
            return false; // дерево не может иметь только одного потомка
        if (isLeaf())
            return std::isalnum(static_cast<unsigned char>(data)); // в листьях могут быть только символы-терминалы
        if (!isLeaf() && !strchr("+-*", data))
            return false; // в узлах, не являющихся листьями, могут быть только +, - или *
        return leftTree->isArithmeticExpression() && rightTree->isArithmeticExpression();

    }

    template<>
    void BinTree<char>::readFromStringPrefix(const std::string& str, int &pos) {
        // чтение префиксной записи (КЛП)
        // текущий узел уже заполнен в предыдущем вызове метода
        // сначала заполняется левое поддерево
        leftTree = new BinTree(str.at(pos)); // заполняется узел левого поддерева
        if (!std::isalnum(static_cast<unsigned char>(str.at(pos)))) {
            leftTree->readFromStringPrefix(str, ++pos); // затем само поддерево
            pos--;
        }
        pos++;

        rightTree = new BinTree(str.at(pos)); // заполняется узел правого поддерева
        if (!std::isalnum(static_cast<unsigned char>(str.at(pos)))) {
            rightTree->readFromStringPrefix(str, ++pos); // затем само поддерево
            pos--;
        }
        pos++;

    }

    template<>
    void BinTree<char>::readFromStringInfix(const std::string& str, int &pos) {
        // чтение классической (инфиксной, ЛКП) записи
        if (str.at(pos) == '(') {
            leftTree = new BinTree('?'); // создаётся фиктивный узел левого поддерева
            leftTree->readFromStringInfix(str, ++pos); // заполняется левое поддерево
            data = str.at(pos); // затем корень
            rightTree = new BinTree('?'); // создаётся фиктивный узел правого поддерева
            rightTree->readFromStringInfix(str, ++pos); // заполняется правое поддерево
            pos++;
        } else if (std::isalnum(static_cast<unsigned char>(str.at(pos)))) {
            data = str[pos++]; // если встретился символ-терминал, он заносится в текущий узел
        }
    }

    template<>
    BinTree<char>::BinTree(const std::string& str) {
        try {
            int pos = 0;
            // если строка начинается со скобки, или с символа-терминала, выполняется чтение строки как инфиксной записи выражения
            if (std::isalnum(static_cast<unsigned char>(str.at(pos))) || str.at(pos) == '(') {
                data = '!';
                readFromStringInfix(str, pos);
            // если строка начинается с символа-оператора, выполняется чтение строки как префиксной записи выражения
            } else if (strchr("+-*", str.at(pos))) {
                data = str.at(pos);
                readFromStringPrefix(str, ++pos);
            }
            if (!isArithmeticExpression() || pos != str.length()) { // если формула была некорректной, конструктор сообщает об этом
                Logger::instance().log("Ошибка: Дерево построено некорректно из-за ошибочного выражения.\n");
            }
        } catch (std::out_of_range &) { // если произошёл выход за границу массива - переданная формула некорректна
            Logger::instance().log("Ошибка: Дерево построено некорректно из-за ошибочного выражения.\n");
        }

    }

    template<typename T>
    BinTree<T>::BinTree(T val) : data(val) {}

    template<typename T>
    BinTree<T>::~BinTree() {
        delete leftTree;
        delete rightTree;
    }

    template<>
    bool BinTree<char>::operator==(const BinTree<char>& other) {
        if (this->isLeaf() && other.isLeaf()) { // если оба узла - листья, сравниваются их значения
            return this->data == other.data;
        }
        if (this->isLeaf() != other.isLeaf()) { // если узлы имеют разный тип, деревья не одинаковы
            return false;
        }
        if (this->data != other.data) {
            return false;
        }
        // проверяется равенство левых и правых поддеревьев
        return *(this->leftTree) == *(other.leftTree) && *(this->rightTree) == *(other.rightTree);
    }

    template<>
    bool BinTree<char>::operator!=(const BinTree& other) {
        return !(*this == other);
    }

    template<typename T>
    bool BinTree<T>::isLeaf() const {
        return !leftTree && !rightTree;
    }

    template<>
    std::string BinTree<char>::toStringPreOrder() const {
        // преобразование в префиксную (КЛП) запись
        std::string str;
        str += data; // добавляется корень
        if (leftTree)
            str += leftTree->toStringPreOrder(); // добавляется левое поддерево
        if (rightTree)
            str += rightTree->toStringPreOrder(); // добавляется правое поддерево
        return str;
    }

    template<>
    std::string BinTree<char>::toStringInOrder() const {
        // преобразование в инфиксную (ЛКП) запись
        std::string str;
        if (!isLeaf()) str+='(';
        if (leftTree)
            str += leftTree->toStringInOrder(); // добавляется левое поддерево
        str += data; // добавляется корень
        if (rightTree)
            str += rightTree->toStringInOrder(); // добавляется правое поддерево
        if (!isLeaf()) str+=')';
        return str;
    }

    template<>
    void BinTree<char>::sumToMul() {
        if (isLeaf()) return;
        if (leftTree && rightTree) {
            leftTree->sumToMul();
            rightTree->sumToMul();
            // спускается в самый низ дерева и начинает преобразования снизу вверх
            Logger::instance().log("Анализ: " + leftTree->toStringInOrder() + data + rightTree->toStringInOrder());
            if (data == '+' && *leftTree == *rightTree) { // если узел '+' и левое поддерево равно правому,
                delete leftTree;                          // левое поддерево заменяется на '2', узел - на '*'
                leftTree = new BinTree<char>('2');
                data = '*';
                Logger::instance().log("Выражение заменено на " + leftTree->toStringInOrder() + data + rightTree->toStringInOrder());
            } else {
                Logger::instance().log("Выражение не изменено");
            }
        }
    }

}
#endif //ALG_LAB3_BINTREE_H
