#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

class Node {
public:
    int key_;       //Значение в узле
    unsigned char height_; //высота узла
    Node* left_;         //левый сын
    Node* right_;        //правый сын
    int count_;              //Количество узлов с одинаковым ключом
    Node(int key): key_(key), height_(1), left_(nullptr), right_(nullptr), count_(1){};
};

void printTree(Node* root, int n, int flagRight = 0){   //Вывод дерева, "лежащего на левом боку"
    if(!root){
        std::cout << "Дерево пусто\n";
        return;
    }
    if(root->right_)
        printTree(root->right_, n+4, 1);
    for(auto i = 0; i<n; i++)
        std::cout << " ";
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
        printTree(root->left_, n+4);
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
    printTree(N, 0);
    Node* x = N->left_;
    Node* y = x->right_;

    // Выполнить вращение
    x->right_ = N;
    N->left_ = y;

    // Обновление высоты
    N->height_ = max(height(N->left_), height(N->right_)) + 1;
    x->height_ = max(height(x->left_), height(x->right_)) + 1;

    // Возвращаем новый корень
    return x;
}

Node* leftRotate(Node* N) //Левый поворот
{
    std::cout << "Выполнение левого поворота относительно узла с ключом " << N->key_ << "\n";
    printTree(N, 0);
    Node* x = N->right_;
    Node* y = x->left_;

    // Выполнить вращение
    x->left_ = N;
    N->right_ = y;

    // Обновление высоты
    N->height_ = max(height(N->left_), height(N->right_)) + 1;
    x->height_ = max(height(x->left_), height(x->right_)) + 1;

    return x;
}

int getBalance(Node* N) //Баланс узла
{
    if (!N)
        return 0;

    return height(N->left_) - height(N->right_);
}

Node* insert(Node* node, int key){

    if (!node)
        return (new Node(key));

    // Если ключ уже существует, увеличить счетчик и вернуть
    if (key == node->key_) {
        (node->count_)++;
        return node;
    }

    /* В противном случае вернемся вниз по дереву */
    if (key < node->key_)
        node->left_ = insert(node->left_, key);
    else
        node->right_ = insert(node->right_, key);

    /* 2. Обновить высоту этого узла-предка */
    node->height_ = max(height(node->left_), height(node->right_)) + 1;

    /* 3. Получить коэффициент баланса этого узла-предка, чтобы проверить уравновешенность*/
    int balance = getBalance(node);

    // Если этот узел становится несбалансированным, то есть 4 случая
    // Левый левый регистр
    if (balance > 1 && key < node->left_->key_) {
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance
                    << " и ключ меньше ключа левого сына - выполнем поворот вправо\n";
        return rightRotate(node);
    }

    // правый правый случай
    if (balance < -1 && key > node->right_->key_) {
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance
                  << " и ключ больше ключа правого сына - выполнем поворот влево\n";
        return leftRotate(node);
    }

    // левый правый регистр
    if (balance > 1 && key > node->left_->key_) {
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance <<
                    " и ключ больше ключа левого сына- выполнем поворот левого сына влево\n";
        node->left_ = leftRotate(node->left_);
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance <<
                  " - выполнем поворот вправо\n";
        return rightRotate(node);
    }

    // Правый левый регистр
    if (balance < -1 && key < node->right_->key_) {
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance <<
                  " и ключ меньше ключа правого сына - выполнем поворот правого сына вправо\n";
        node->right_ = rightRotate(node->right_);
        std::cout << "Баланс узла с ключом " << node->key_ << ": " << balance <<
                  " - выполнем поворот влево\n";
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

Node* deleteNode(Node* root, int key){
    if (!root)
        return nullptr;

    // Если удаляемый ключ меньше ключа root,
    // тогда он лежит в левом поддереве
    if (key < root->key_)
        root->left_ = deleteNode(root->left_, key);

        // Если удаляемый ключ больше ключа root,
        // тогда оно лежит в правом поддереве
    else if (key > root->key_)
        root->right_ = deleteNode(root->right_, key);

        // если ключ совпадает с ключом root, удаляем
    else {
        // Если ключ присутствует более одного раза, просто уменьшить счётчик
        if (root->count_ > 1) {
            (root->count_)--;
            return root;
        }

        // иначе удалим узел

        // узел только с одним дочерним элементом или без него
        if (!root->left_|| !root->right_) {
            Node* temp = root->left_ ? root->left_ : root->right_;

            // Нет дочернего случая
            if (!temp) {
                temp = root;
                root = nullptr;
            }

            else // Один дочерний случай
                *root = *temp; // Копируем содержимое непустого потомка

            delete temp;
        }

        else {
            // узел с двумя дочерними элементами: Получить преемника по порядку (наименьший
            // в правом поддереве)
            Node* temp = minValueNode(root->right_);

            // Копируем данные преемника inorder в этот узел и обновляем счетчик
            root->key_ = temp->key_;
            root->count_ = temp->count_;
            temp->count_ = 1;

            // Удалить наследник преемника
            root->right_ = deleteNode(root->right_, temp->key_);

        }

    }

    // Если у дерева был только один узел, возвращаем
    if (!root)
        return root;

    // ОБНОВЛЕНИЕ ВЫСОТЫ ТЕКУЩЕГО УЗЛА
    root->height_ = max(height(root->left_), height(root->right_)) + 1;

    //проверка сбалансированности
    int balance = getBalance(root);

    // Если этот узел становится несбалансированным, то есть 4 случая
    // Левый левый регистр
    if (balance > 1 && getBalance(root->left_) >= 0) {
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance
                  << " и баланс левого сына: " << getBalance(root->left_) << " >=0 => выполняем поворот влево";
        return rightRotate(root);
    }

    // левый правый регистр
    if (balance > 1 && getBalance(root->left_) < 0) {
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance
                  << " и баланс левого сына: " << getBalance(root->left_)
                  << " <0 => выполнем поворот левого сына влево";
        root->left_ = leftRotate(root->left_);
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance <<
                  " - выполнем поворот вправо\n";
        return rightRotate(root);
    }

    // правый правый случай
    if (balance < -1 && getBalance(root->right_) <= 0) {
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance
                  << " и баланс правого сына: " << getBalance(root->right_)
                  << " <=0 => выполнем поворот влево";
        return leftRotate(root);
    }
    // Правый левый регистр
    if (balance < -1 && getBalance(root->right_) > 0) {
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance
                  << " и баланс правого сына: " << getBalance(root->right_)
                  << " >0 => выполнем поворот правого сына вправо";
        root->right_ = rightRotate(root->right_);
        std::cout << "Баланс узла с ключом " << root->key_ << ": " << balance <<
                  " - выполнем поворот влево\n";
        return leftRotate(root);
    }

    return root;
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
    bool fileOpenFlag = true;
    std::string key;
    Node* root = nullptr;
    while(chooseInput != '2'){
        std::cout << "Выберите действие(0 - консоль, 1 - файл, 2 - выход из программы)\n";
        std::cin >> chooseInput;
        switch(chooseInput){
            case '0':
                while(chooseAction != '*') {
                    std::cout << "Выберите действие(+ - добавить элемент, - - удалить элемент, "
                                 "# - очистить текущее дерево, * - выход)\n";
                    std::cin >> chooseAction;
                    switch(chooseAction){
                        case '+':
                            std::cout << "Введите значение ключа добавляемого элемента\n";
                            std::cin >> key;
                            if(!isDigit(key)){
                                std::cout << "Ключом должно быть целое положительное число\n";
                                continue;
                            }
                            root = insert(root, atoi(key.c_str()));
                            std::cout << "Получившееся дерево:\n";
                            printTree(root, 0);
                            break;
                        case '-':
                            std::cout << "Введите значение ключа удаляемого элемента\n";
                            std::cin >> key;
                            if(!isDigit(key)){
                                std::cout << "Ключом должно быть целое положительное число\n";
                                continue;
                            }
                            root = deleteNode(root, atoi(key.c_str()));
                            std::cout << "Получившееся дерево:\n";
                            printTree(root, 0);
                            break;
                        case '#':
                            std::cout<< "Очищаем дерево\n";
                            clearTree(root);
                            root = nullptr;
                            break;
                        case '*':
			    chooseInput = '2';
                            break;
                        default:
                            std::cout << "Данное действие не поддерживается программой\n";
                            continue;
                    }
                }
                break;
            case '1':{
                std::string fileName;
                while(fileOpenFlag) {
                    std::cout << "Введите название файла или q для выхода\n";
                    std::cin >> fileName;
		    if(fileName == "q"){
			std::cout << "Выход\n";
			chooseInput = '2';
			break;
		    }
                    std::fstream file(fileName);
                    if (!file.is_open()) {
                        std::cout << "Файл не может быть открыт\n";
                        continue;
                    }
                    fileOpenFlag = false;
                }
		if(fileName == "q")
		    break;
                std::fstream file(fileName);
                while(chooseAction != '*') {
                    std::cout << "Выберите действие(+ - добавить элемент, - - удалить элемент, "
                                 "# - очистить дерево, * - выход)\n";
                    file >> chooseAction;
                    std::cout << chooseAction << '\n';
                    if (chooseAction != '-' && chooseAction != '+' && chooseAction != '*' && chooseAction != '#') {
                    }
                    switch(chooseAction){
                        case '+':
                            std::cout << "Введите значение добавляемого ключа\n";
                            file >> key;
                            std::cout << key << '\n';
                            if(!isDigit(key)){
                                std::cout << "Ключом должно быть целое положительное число\n";
                                continue;
                            }
                            root = insert(root, atoi(key.c_str()));
                            std::cout << "Получившееся дерево:\n";
                            printTree(root, 0);
                            break;
                        case '-':
                            std::cout << "Введите значение ключа удаляемого элемента\n";
                            file >> key;
                            std::cout << key << '\n';
                            if(!isDigit(key)){
                                std::cout << "Ключом должно быть целое положительное число\n";
                                continue;
                            }
                            root = deleteNode(root, atoi(key.c_str()));
                            std::cout << "Получившееся дерево:\n";
                            printTree(root, 0);
                            break;
                        case '#':
                            std::cout<< "Очищаем дерево\n";
                            clearTree(root);
                            root = nullptr;
                            break;
                        case '*':
			    chooseInput = '2';
                            break;
                        default:
                            std::cout << "Данное действие не поддерживается программой\n";
                            continue;
                    }
                }
            break;
            }
            case '2':
                std::cout << "Выход из программы\n";
                break;
            default:
                std::cout << "Программа не поддерживает такой формат ввода\n";
                break;
        }
    }
    clearTree(root);
    return 0;
}
