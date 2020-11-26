#ifndef BINARY_TREE_H
#define BINARY_TREE_H


template <typename T>
class BinaryTree {
private:
    T element_;                    // Корень дерева
    BinaryTree* right_ = nullptr;  // Правое поддерево
    BinaryTree* left_ = nullptr;   // Левое поддерево

public:
    BinaryTree();
    BinaryTree(const std::string& expression);
    bool createFromString(const char*& character);
    void setElement(const T& value);
    T getElement();
    BinaryTree* getRightSubtree();
    BinaryTree* getLeftSubtree();
    void setRightSubtree(BinaryTree* subtree);
    void setLeftSubtree(BinaryTree* subtree);
    bool isLeaf();
    std::string getString() const;
    ~BinaryTree();
};

template<>
inline BinaryTree<char>::BinaryTree(): element_('\0') {}

template<>
inline BinaryTree<char>::BinaryTree(const std::string& expression) {
    const char* start = expression.c_str();
    createFromString(start);
}

template<>
inline bool BinaryTree<char>::createFromString(const char*& character) {
    // Очищаем поддеревья (в случае, если до вызова метода дерево уже использовалось)
    delete right_;
    delete left_;
    right_ = nullptr;
    left_ = nullptr;

    // Если скобочная запись начинается с '/', то это пуcтое БД
    if (*character == '/') {
        character++;
        return true;
    }

    // Если скобочная запись начинается с '(', то это непустое БД
    if (*character == '(') {
        character++;

        // Если нам встречается значение узла дерева, то записываем его в узел
        if (*character != '(' && *character != ')' && *character != '/' && *character != '\0') {
            element_ = *character;
            character++;
        }

        // Если встречаем конец скобочной записи, то выходим
        if (*character == ')') {
            character++;
            return true;
        }

        // Создаем левое поддерево
        if (*character != '/') {
            left_ = new BinaryTree;
            bool correct = left_->createFromString(character);

            // Если не удалось корректно считать скобочную запись, то выходим
            if (!correct) {
                return false;
            }

        }
        else {
            character++;
        }

        // Если встречаем конец скобочной записи, то выходим
        if (*character == ')') {
            character++;
            return true;
        }

        // Создаем правое поддерево
        if (*character != '/') {
            right_ = new BinaryTree;
            bool correct = right_->createFromString(character);

            // Если не удалось корректно считать скобочную запись, то выходим
            if (!correct) {
                return false;
            }

        }
        else {
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
inline void BinaryTree<T>::setElement(const T& value) {
    element_ = value;
}

template<typename T>
inline T BinaryTree<T>::getElement() {
    return element_;
}

template<typename T>
inline BinaryTree<T>* BinaryTree<T>::getRightSubtree() {
    return right_;
}

template<typename T>
inline BinaryTree<T>* BinaryTree<T>::getLeftSubtree() {
    return left_;
}

template<typename T>
inline void BinaryTree<T>::setRightSubtree(BinaryTree* subtree) {
    delete right_;
    right_ = subtree;
}

template<typename T>
inline void BinaryTree<T>::setLeftSubtree(BinaryTree* subtree) {
    delete left_;
    left_ = subtree;
}

template<>
inline bool BinaryTree<char>::isLeaf() {
    return right_ == nullptr && left_ == nullptr;
}

template <>
inline std::string BinaryTree<char>::getString() const {
    std::string result = "(";

    if (element_ != '\0') {
        result += std::string(1, element_);
    }

    if (left_ != nullptr) {
        result += left_->getString();
    } else {
        result += '/';
    }

    if (right_ != nullptr) {
        result += right_->getString();
    } else {
        result += '/';
    }

    return result + ")";
}

template <typename T>
inline BinaryTree<T>::~BinaryTree() {
    delete right_;
    delete left_;
}


#endif // BINARY_TREE_H