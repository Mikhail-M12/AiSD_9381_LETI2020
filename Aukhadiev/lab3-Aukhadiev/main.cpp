#include <iostream>
#include <fstream>
#include <string>

template<typename Elem>
class BinTree{
private:
    Elem info_;
    BinTree *left_;
    BinTree *right_;
public:
    BinTree(): left_(nullptr), right_(nullptr){};
    BinTree(Elem info):info_(info), left_(nullptr), right_(nullptr){}
//getters:
    Elem getInfo(){ return info_;}
    BinTree* getLeft(){return left_;}
    BinTree* getRight(){return right_;}
//setters
    void setInfo(Elem info){ info_ = info;}
    void setLeft(BinTree* left){left_ = left;}
    void setRight(BinTree* right){right_ = right;}

    BinTree<Elem>* createBinTree(std::string& LPK, const std::string LKP, int n){ //рекурсвный метод восстановления дерева
        if(LPK.empty()) //условие выхода из рекурсии
            return nullptr;
        char c = LPK[LPK.length()-1];           //сохранение последнего символа
        BinTree *binTree = new BinTree<Elem>(c);//ЛПК-формата - корня
        LPK.erase(LPK.length()-1,1);     //удаление последнего символа из ЛПК-формата
        int index = LKP.find(c);                  //Поиск символа в ЛКП-формате
        if(index == -1){                          //Если символ не найден
            std::cout << "Введённые данные некорректны\n";
            exit(0);
        }
        std::string right = LKP.substr(index+1);
        std::string left  = LKP.substr(0, index);
        printTab(n);
        std::cout << "Корень: " << binTree->getInfo() <<", "
                  << "Правое поддерево: " <<  right << ", "
                  << "Левое поддерево:" << left << '\n';
        if(!right.empty()){                                          //создание правого сына из
            printTab(n);
            std::cout << "Анализ правого поддерева " << right << '\n';
            binTree->setRight(createBinTree(LPK, right, n+1)); //строки из ЛКП-формата,
            printTab(n);
            std::cout << "Анализ правого поддерева завершён\n";
        }                                                                     //стоящей справа от index

        if(!left.empty()) {                                         //содание левого сына из
            printTab(n);
            std::cout << "Анализ левого поддерева " << left << '\n';
            binTree->setLeft(createBinTree(LPK, left, n+1)); //строки из ЛКП-формата,
            printTab(n);
            std::cout << "Анализ левого поддерева завершён\n";
        }                                                               //стоящей слева от index

        return binTree;
    }

    void printTreeKLP(){    //Вывод в КЛП-формате
        std::cout << this->getInfo();
        if(left_)
            left_->printTreeKLP();
        if(right_)
            right_->printTreeKLP();
    }

    void printTree(int n, int flagRight = 0){   //Вывод дерева, "лежащего на левом боку"
        if(right_)
            right_->printTree(n+4, 1);
        for(auto i = 0; i<n; i++)
            std::cout << " ";
        std::cout << info_ << "\n";
        if(flagRight || left_) {
            for (auto i = 0; i < n + 1; i++) {
                if (i == n - 3 && flagRight)
                    std::cout << '/';
                if (i == n && left_)
                    std::cout << "\\";
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        if(left_)
            left_->printTree(n+4);
    }

    void printTab(int n){
        for(auto i = 0; i<n; i++)
            std::cout <<'\t';
    }

    ~BinTree(){
        if(left_)
            delete left_;
        if(right_)
            delete right_;
    }
};

int main() {
    std::string LPK;
    std::string LKP;
    std::cout << "Выберите формат ввода: 0 - консоль, 1 - файл\n";
    int choise;
    std::cin >> choise;
    switch(choise){
        case 0:
            std::cout << "Введите строку в ЛПК-формате\n";
            std::cin >> LPK;
            std::cout << "Введите строку в ЛКП-формате\n";
            std::cin >> LKP;
            break;
        case 1: {
            std::string fileName;
            std::cout << "Введите название файла\n";
            std::cin >> fileName;
            std::ifstream file(fileName);
            if (!file.is_open()) {
                std::cerr << "Файл не найден\n";
                return 0;
            }
            file >> LPK;
            file >> LKP;
            std::cout << "ЛПК: " << LPK << "\nЛКП: " << LKP << '\n';
            file.close();
            break;
        }
        default:
            std::cerr << "Неверный формат ввода\n";
            return 0;
    }
    if(LKP.empty() || LPK.empty()) {
        std::cerr << "Введены пустые строки\n";
        return 0;
    }
    if(LKP.length() != LPK.length()){
        std::cerr << "Введённые данные некорректны\n";
        return 0;
    }
    BinTree<char>* binTree;
    binTree = binTree->createBinTree(LPK, LKP, 0);
    std::cout << "\nКЛП-формат: ";
    binTree->printTreeKLP();
    std::cout << "\nРисунок дерева:\n";
    binTree->printTree(0);
    delete binTree;
    return 0;
}
