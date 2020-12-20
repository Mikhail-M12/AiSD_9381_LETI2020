#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>

class Node *globalTree = nullptr;

class Node {
public:
    int key_;       //Значение в узле
    unsigned char height_; //высота узла
    Node* left_;         //левый сын
    Node* right_;        //правый сын
    int count_;              //Количество узлов с одинаковым ключом
    Node(int key): key_(key), height_(1), left_(nullptr), right_(nullptr), count_(1){};
};

void printTree(Node* root, int n = 0, int flagRight = 0, int key = -1){   //Вывод дерева, "лежащего на левом боку"
    if(!root){
        std::cout << "Дерево пусто\n";
        return;
    }
    if(root->right_)
        printTree(root->right_, n+4, 1, key);
    for(auto i = 0; i<n; i++)
        std::cout << " ";
    if(root->key_ == key)
        std::cout << "\x1b[31m" << root->key_ << "(" << root->count_ << ")" << "\x1b[0m" << '\n';
    else
        std::cout << root->key_ << '(' << root->count_ << ")\n";
    if(flagRight || root->left_) {
        for (auto i = 0; i < n + 1; i++) {
            if (i == n - 3 && flagRight)
                std::cout << '/';
            if (i == n && root->left_)
                std::cout << "\\";
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    if(root->left_)
        printTree(root->left_, n+4, 0, key);
}

int height(Node* N){ //получение высоты дерева
    if (!N)
        return 0;

    return N->height_;
}

int max(int a, int b){ //Получение максимума из двух чисел
    return (a > b) ? a : b;
}

Node* rightRotate(Node* N) //Правый поворот
{
    std::cout << "Выполнение правого поворота относительно узла с ключом " << N->key_ << '\n';
    printTree(globalTree, 0, 0, N->key_);
    Node* x = N->left_;
    Node* y = x->right_;

    // Выполнить вращение
    x->right_ = N;
    N->left_ = y;

    // Обновление высоты
    N->height_ = max(height(N->left_), height(N->right_)) + 1;
    x->height_ = max(height(x->left_), height(x->right_)) + 1;

    std::cout << "\nДерево после поворота:\n";
    printTree(x);
    // Возвращаем новый корень
    return x;
}

Node* leftRotate(Node* N) //Левый поворот
{
    std::cout << "Выполнение левого поворота относительно узла с ключом " << N->key_ << "\n";
    printTree(globalTree, 0, 0, N->key_);
    Node* x = N->right_;
    Node* y = x->left_;

    // Выполнить вращение
    x->left_ = N;
    N->right_ = y;

    // Обновление высоты
    N->height_ = max(height(N->left_), height(N->right_)) + 1;
    x->height_ = max(height(x->left_), height(x->right_)) + 1;

    std::cout << "\nДерево после поворота:\n";
    printTree(x);

    return x;
}

int getBalance(Node* N) //Баланс узла
{
    if (!N)
        return 0;

    return height(N->left_) - height(N->right_);
}

Node* insert(Node* node, int key) {

    if (!node) {
        std::cout << "Добавляем ключ " << key << '\n';
        return (new Node(key));
    }

    // Если ключ уже существует, увеличить счетчик и вернуть
    if (key == node->key_) {
        (node->count_)++;
        return node;
    }

    /* В противном случае движемся вниз по дереву */
    if (key < node->key_) {
        std::cout << "Добавляемый ключ " << key << " меньше узла с ключом " << node->key_ << ", движемся влево\n";
        node->left_ = insert(node->left_, key);
    } else{
        std::cout << "Добавляемый ключ " << key << " больше узла с ключом " << node->key_ << ", движемся вправо\n";
        node->right_ = insert(node->right_, key);
    }
    /* Обновить высоту этого узла-предка */
    node->height_ = max(height(node->left_), height(node->right_)) + 1;

    /* Получить коэффициент баланса этого узла-предка, чтобы проверить уравновешенность*/
    int balance = getBalance(node);

    // Если этот узел становится несбалансированным, то есть 4 случая
    // Левый левый регистр
    if (balance > 1 && key < node->left_->key_) {
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance
                    << " и ключ добаемого элемента " << key << " меньше ключа левого сына "
                    << node->left_->key_ << " => выполняем поворот вправо\n";
        return rightRotate(node);
    }

    // правый правый случай
    if (balance < -1 && key > node->right_->key_) {
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance
                  << " и ключ добавляемого элемента " << key << " больше ключа правого сына "
                  << node->right_->key_ << " => выполняем поворот влево\n";
        return leftRotate(node);
    }

    // левый правый регистр
    if (balance > 1 && key > node->left_->key_) {
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance <<
                    " и ключ добавляемого элемента " << key << " больше ключа левого сына"
                    << node->left_->key_ << " => выполняем поворот левого сына влево\n";
        node->left_ = leftRotate(node->left_);
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance <<
                  " => выполнем поворот вправо\n";
        return rightRotate(node);
    }

    // Правый левый регистр
    if (balance < -1 && key < node->right_->key_) {
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance <<
                  " и ключ добавляемого элемента " << key << " меньше ключа правого сына"
                  << node->right_->key_ << " => выполнем поворот правого сына вправо\n";
        node->right_ = rightRotate(node->right_);
        std::cout << "В узле с ключом " << node->key_ << ": \nбаланс = " << balance <<
                  " => выполнем поворот влево\n";
        return leftRotate(node);
    }

    /* вернуть (неизмененный) указатель узла */
    return node;
}

// Если дано непустое двоичное дерево, вернуть узел с минимальным значением ключа, найденного в этом дереве.
Node* minValueNode(Node* node){

    Node* current = node;

    //поиск самого левого листа

    while (current->left_ != NULL)
        current = current->left_;

    return current;
}

void clearTree(Node* root){
    if(!root)
        return;
    if(root->left_)
        clearTree(root->left_);
    if(root->right_)
        clearTree(root->right_);
    delete root;
}

bool isDigit(std::string key) {
    for (auto i = 0; i < key.length(); i++)
        if (!std::isdigit(key[i]))
            return false;
    return true;
}

int main()
{
    char chooseInput = 0;
    char chooseAction = 0;
    std::string key;
    std::string keys;
    std::string fileName;
    std::cout << "Выберите формат ввода(0 - консоль, 1 - файл)\n";
    std::cin >> chooseInput;
    switch(chooseInput) {
        case '0':
            while (chooseAction != '*') {
                std::cout << "Выберите действие: + - добавление элемента, * - выход из программы\n";
                std::cin >> chooseAction;
                switch (chooseAction) {
                    case '+':
                        std::cout << "Введите значение ключа добавляемого элемента\n";
                        std::cin >> key;
                        if (!isDigit(key)) {
                            std::cout << "Ключом должно быть целое положительное число\n";
                            continue;
                        }
                        globalTree = insert(globalTree, atoi(key.c_str()));
                        std::cout << "Получившееся дерево:\n";
                        printTree(globalTree, 0);
                        break;
                    case '*':
                        std::cout << "Выход из программы\n";
                        break;
                    default:
                        std::cout << "Данное действие не поддерживается программой\n";
                        break;
                }
            }
            break;
        case '1': {
            std::cout << "Введите название файла\n";
            std::cin >> fileName;
            std::fstream file(fileName);
            if (!file.is_open()) {
                std::cout << "Файл не может быть открыт\n";
                break;
            }
            std::getline(file, keys);
            if(keys.empty()){
                std::cout << "Строка пуста\n";
                break;
            }
            std::cout << "Элементы дерева:\n" << keys << '\n';
            file.close();
            std::istringstream stream(keys);
            int x = 0;
            while(stream >> x) {
                std::cout << "Добавляемый элемент: " << x << '\n';
                globalTree = insert(globalTree, x);
                std::cout << "Получившееся дерево:\n";
                printTree(globalTree, 0);
            }
            break;
        }
        default:
            std::cout << "Данный формат ввода не поддерживается программой\n";
            break;
    }
    clearTree(globalTree);
    return 0;
}
