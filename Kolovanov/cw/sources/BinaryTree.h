#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <sstream>


template <typename T>
class BinaryTree {
private:
    T element_;                    // Корень дерева
    size_t weight_ = 0;            // Вес корня дерева
    BinaryTree* right_ = nullptr;  // Указатель на правое поддерево
    BinaryTree* left_ = nullptr;   // Указатель на левое поддерево

public:
    BinaryTree();
    explicit BinaryTree(const T& element, size_t weight = 0);
    explicit BinaryTree(const std::string& expression);
    ~BinaryTree();

    bool createFromString(const char*& character);
    void setElement(const T& value);
    T getElement() const;
    size_t getWeight() const;
    void setWeight(size_t value);
    BinaryTree* getRightSubtree();
    BinaryTree* getLeftSubtree();
    const BinaryTree* getRightSubtree() const;
    const BinaryTree* getLeftSubtree() const;
    void setRightSubtree(BinaryTree* subtree);
    void setLeftSubtree(BinaryTree* subtree);
    bool isLeaf() const;
    std::string getString() const;
    std::string getElementString() const;
};

template<>
inline BinaryTree<char>::BinaryTree(): element_('\0') {}


template<typename T>
BinaryTree<T>::BinaryTree(const T& element, size_t weight): element_(element), weight_(weight) {}


template<>
inline BinaryTree<char>::BinaryTree(const std::string& expression) {
    const char* start = expression.c_str();
    bool correct = createFromString(start);

    if (!correct) {
        delete left_;
        delete right_;
        left_ = nullptr;
        right_ = nullptr;
    }
}


template <typename T>
BinaryTree<T>::~BinaryTree() {
    delete right_;
    delete left_;
}


template<>
inline bool BinaryTree<char>::createFromString(const char*& character) {
    // Очищаем поддеревья (в случае, если до вызова метода дерево уже использовалось)
    delete right_;
    delete left_;
    right_ = nullptr;
    left_ = nullptr;

    // Если скобочная запись начинается с '(', то это непустое БД
    if (*character == '(') {
        character++;

        if (*character == '\'') {
            character++;

            if (*character == '\\') {
                character++;

                if (*character == '0') {
                    element_ = '\0';
                    character++;
                } else {
                    return false;
                }

            } else if (*character != '\0') {
                element_ = *character;
                character++;
            } else {
                return false;
            }

            if (*character == '\'') {
                character++;
            } else {
                return false;
            }
        }

        // Создаем левое поддерево
        if (*character != '/') {
            left_ = new BinaryTree;
            bool correct = left_->createFromString(character);

            // Если не удалось корректно считать скобочную запись, то выходим
            if (!correct) {
                return false;
            }

        } else {
            character++;
        }

        // Создаем правое поддерево
        if (*character != '/') {
            right_ = new BinaryTree;
            bool correct = right_->createFromString(character);

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


template<typename T>
void BinaryTree<T>::setElement(const T& value) {
    element_ = value;
}


template<typename T>
T BinaryTree<T>::getElement() const {
    return element_;
}


template<typename T>
size_t BinaryTree<T>::getWeight() const {
    return weight_;
}


template<typename T>
void BinaryTree<T>::setWeight(size_t value) {
    weight_ = value;
}


template<typename T>
BinaryTree<T>* BinaryTree<T>::getRightSubtree() {
    return right_;
}


template<typename T>
BinaryTree<T>* BinaryTree<T>::getLeftSubtree() {
    return left_;
}


template<typename T>
const BinaryTree<T>* BinaryTree<T>::getRightSubtree() const {
    return right_;
}


template<typename T>
const BinaryTree<T>* BinaryTree<T>::getLeftSubtree() const {
    return left_;
}


template<typename T>
void BinaryTree<T>::setRightSubtree(BinaryTree* subtree) {
    delete right_;
    right_ = subtree;
}


template<typename T>
void BinaryTree<T>::setLeftSubtree(BinaryTree* subtree) {
    delete left_;
    left_ = subtree;
}


template<typename T>
bool BinaryTree<T>::isLeaf() const {
    return right_ == nullptr && left_ == nullptr;
}


template <>
inline std::string BinaryTree<char>::getString() const {
    std::ostringstream result;

    result << "('";

    if (element_ != '\0') {
        result << std::string(1, element_);
    } else {
        result << "\\0";
    }

    result << "'";

    if (left_ != nullptr) {
        result << left_->getString();
    } else {
        result << '/';
    }

    if (right_ != nullptr) {
        result << right_->getString();
    } else {
        result << '/';
    }
    
    result << ")";

    return result.str();
}


template<>
inline std::string BinaryTree<char>::getElementString() const {
    std::ostringstream result;

    if (element_ != '\0') {
        result << std::string(1, element_);
    }

    if (left_ != nullptr) {
        result << left_->getElementString();
    }

    if (right_ != nullptr) {
        result << right_->getElementString();
    }

    return result.str();
}


#endif // BINARY_TREE_H