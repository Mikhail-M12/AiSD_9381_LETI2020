#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

template <typename Elem>
class BinTree{//  бинарное дерево
private:
    Elem info = 0; // данные узла
    BinTree * leftTree; // левое поддерево
    BinTree * rightTree; // правое поддерево
public:
    BinTree() {
        leftTree = nullptr;
        rightTree = nullptr;
    }// конструктор класса БД

    // геттеры
    BinTree * getLeft(){
        return this->leftTree;
    }
    BinTree * getRight(){
        return this->rightTree;
    }

    [[nodiscard]] Elem rootBT() const{
        return this->info;
    }

    // сеттеры
    void setLeft(BinTree *pointer){
        this->leftTree = pointer;
    }
    void setRight(BinTree *pointer){
        this->rightTree = pointer;
    }
    void setRoot(Elem elem){
        this->info = elem;
    }

    ~BinTree() = default; // деструктор класса БД

    static bool isNull(BinTree  *  node){ // проверка на пустой узел
        return (node == nullptr);
    }

    static void destroy (BinTree * node) // рекурсивно удаляет выделенную под узлы память
    {
        if (!isNull(node)){
            destroy (node->getLeft());
            destroy (node->getRight());
            delete node;
            node = nullptr;
        }
    }
    static BinTree * consBT(const Elem &x, BinTree<char> *left, BinTree<char> *right)// конструктор БД (создаёт элемент бинарного дерева)
    {
        auto* p = new BinTree<char>;
        if (!isNull(p))	{
            p->setRoot(x);
            p->setLeft(left);
            p->setRight(right);
            return p;
        }
        else {
            std::cerr << "Memory not enough\n";
            exit(0);
        }
    }

    static BinTree<Elem> * restoreBT(std::string &formatKLP, std::string &formatLKP, int &move, std::ostream & out, int  n){
        // функция восстанавливающая БД по КЛП И ЛКП записи

        if(move >= formatKLP.size()){
            out << "Невозможно восстановить дерево. Проверьте корректность перечислений\n";
            exit(0);
        }
        char key = formatKLP[move]; // клп-запись - это ориентир для лкп-записи

        if(formatLKP.find(key) == -1){
            out << "Ключ (" << key << ") не найден в ЛКП-подстроке (" << formatLKP << ").\n"
                <<"По данной записи невозможно восстановить бинарное дерево. Проверьте корректность перечислений\n";
            exit(0);
        }
        //условие конца рекурсии
        if(formatLKP == ""){
            return nullptr;
        }

        BinTree <Elem>* leftNode = nullptr;
        BinTree<Elem> * rightNode = nullptr;
        printIndent(n, out);
        out << "Текущий ключ: (" << key << "), его номер в КЛП-строке: (" << formatKLP.find(key) + 1 << "), в текущей ЛКП-строке: (" << formatLKP.find(key) + 1 << ")\n";
        std::string left = formatLKP.substr(0, formatLKP.find(key) ); //выделение левого поддерева ( всё что слева от корня )
        std::string right = formatLKP.substr(formatLKP.find(key) + 1); //выделение левого поддерева ( всё что справа от корня )
        printIndent(n, out);
        out << "Левое поддерево: (" << left << "), корень: (" << key  << "), правое поддерево: (" << right << ")\n";
        if(!left.empty()) {
            printIndent(n, out);
            out << "Анализ левого поддерева\n";
            leftNode = restoreBT(formatKLP, left, ++move, out, n + 1); // если левая часть лкп непуста, создаётся левое поддерево
        }
        printIndent(n, out);
        out << "Анализ левого поддерева завершён\n";
        if(!right.empty()) {
            printIndent(n, out);
            out << "Анализ правого поддерева\n";
            rightNode = restoreBT(formatKLP, right, ++move, out, n + 1); //  если правая часть лкп непуста, создаётся правое поддерево
        }
        printIndent(n, out);
        out << "Анализ правого поддерева завершён\n";

        printIndent(n, out);
        out << "Создание узла\n";
        return BinTree<Elem>::consBT(key, leftNode, rightNode); // генерация узла
    }

    static void getLPK (BinTree<Elem>* node, std::string & result, std::ostream & out, int n) // вывод в лпк-формате
    {
        if (!BinTree<Elem>::isNull(node)) {
            printIndent( n, out);
            out << "Начало обхода левого поддерева. Текущий корень: (" << node->rootBT() <<")\n";
            getLPK(node->getLeft(), result, out, n + 1);
            printIndent( n, out);
            out << "Конец обхода левого поддерева\n";
            printIndent( n, out);
            out << "Начало обхода правого поддерева. Текущий корень: (" << node->rootBT() << ")\n";
            getLPK(node->getRight(), result, out, n + 1);
            printIndent( n, out);
            out << "Конец обхода правого поддерева\n";
            printIndent( n, out);
            out << "Добавление члена в ЛПК-запись: (" << node->rootBT() << ")\n";
            result += node->rootBT();
        }
    }

    static void printPKL (BinTree<Elem> *node, int move, std::ostream & out) // функция, изображающая бинарное дерево (повернутое) в удобном формате
    { // БД выводится справа налево с необходимым количеством отступов
        // это позволяет визуализировать БД в привычном виде
        if (!BinTree<Elem>::isNull(node)) {
            printPKL (node->getRight(), move + 2, out);
            for (int i = 0; i < move; i++)
                out << "_";
            out << node->rootBT() << std::endl;
            printPKL (node->getLeft(), move + 2, out);
        }
    }

    static void printIndent(int n, std::ostream & out){
        for(int i = 0; i < n; i++ )
            out << "\t";
    }

};



namespace file{
    ifstream inFile;
    ofstream outFile;
}

int main(){
    char flag;
    string path;
    BinTree <char> * tree; // корень БД
    string formatKLP;
    string formatLKP;
    string formatLPK;
    int keyMover = 0;
    int n = 0;
    char info;
    cout << "0 - ввод с консоли\n1 - ввод с файла\n";
    cin >> flag;
    switch(flag){
        case '0':
            cout << "Введите сначала в КЛП-формате, затем перейдите на следующую строку в введите в ЛКП-формате:\n";
            cin >> formatKLP; //ввод КЛП-записи
            cin >> formatLKP; // ввод ЛКП-записи
            break;
        case '1':
            cout << "Введите путь до файла:\n";
            cin >> path;
            file::inFile.open(path);
            if(!file::inFile.is_open()){
                cout << "Невозможно открыть файл на чтение\n";
                return 0;
            }
            file::inFile >> formatKLP;
            file::inFile >> formatLKP;
            file::inFile.close();
            break;
        default:
            cout << "Неверный формат\n";
            return 0;
    }
    // отлов ошибок

    cout << "0 - вывод в консоль\n1 - вывод в файл\n";
    cin >> flag;
    switch(flag) {
        case '0':
            break;
        case '1':
            cout << "Введите путь до файла:\n";
            cin >> path;
            file::outFile.open(path);
            if(!file::outFile.is_open()){ // обработка ошибочных данных
                cout << "Невозможно открыть файл на запись\n";
                return 0;
            }
            break;
        default:
            cout << "Неверный формат\n";
            return 0;
    }
    ostream & out = flag == '0' ? cout : file::outFile; // установка потока вывода
    if(formatKLP.size() != formatLKP.size()){
        out << "ОШИБКА! Количество элементов должно совпадать\n";
        return 0;
    }

    for(char i : formatKLP){
        if(formatLKP.find(i) == -1){
            out << "ОШИБКА! Символы в строках должны быть одни и те же\n";
            return 0;
        }
    }
    out << "КЛП-запись: (" << formatKLP << ")\n";
    out << "ЛКП-запись: (" << formatLKP << ")\n";
    tree =  BinTree <char>::restoreBT(formatKLP, formatLKP, keyMover, out, n); // восстановление БД по КЛП и ЛКП видам записи
    out <<"\nВосстановленное дерево:\n";
    BinTree <char>::printPKL(tree, 1, out); // вывод на экран БД
    out << "\nОбход дерева в порядке ЛПК:\n";
    BinTree<char>::getLPK(tree, formatLPK, out, 0);
    out << "\nЛПК-запись дерева: (" << formatLPK <<")\n"; // вывод в лпк-формате
    BinTree <char>::destroy(tree); // освобождение памяти
    file::outFile.close();
    return 0;
}





