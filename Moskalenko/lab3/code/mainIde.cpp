#include <fstream>
#include <iostream>
using namespace std;

static int readIndex;     //переменная, отвечающая за индекс элемента в строке
typedef char T;
class Elem {
    Elem* left;
    Elem* right;
    T data;
public:
    Elem():left(nullptr), right(nullptr), data('\0') {};

    Elem* getLeft() {
        return left;        //возвращает значение левого поддерева
    }

    void setLeft(Elem* l) {  //устанавливает левое поддерево
        left = l;
    }

    void setRight(Elem* r) {     //устанавливает правое поддерево
        right = r;
    }

    Elem* getRight() {           //возвращает значение правого поддерева
        return right;
    }

    T getData() const {        //возвращает значение элемента
        return data;
    }

    void setData(T t) {       //устанавливает значение элемента
        data = t;
    }
};
typedef Elem* Tree;

static int countSame = 0;  //количество различных одинаковых элементов

class SimpleList {
public:
    T data; //значение
    SimpleList *next; //ссылка на следующий элемент
    int countH;

    SimpleList() : data('\0'), next(nullptr), countH(1) {};

    SimpleList(T sign, SimpleList* elem = nullptr, int count = 1) : data(sign), next(elem), countH(count) {};

    void push(T sign);

    void listPrint();

    void initHead(T sign)
    {
        data = sign;            // инициализация головы линейного списка
    }

    SimpleList* checkSimple(T sign);

};
typedef SimpleList* Simple;

void SimpleList::push(T sign) {
    cout << "Добавляем " << sign << " в линейный список" << "\n";
    Simple current = this;

    while (current->next != nullptr)         //пока не достигнем конца списка
        current = current->next;

    auto node = new SimpleList(sign);
    current->next = node;
}

void SimpleList::listPrint() {
    cout << "\033[34m Посчитаем количество повторений каждого элемента в дереве \033[0m \n";
    Simple p = this;
    do {
        cout <<  "В бинарном дереве элемент " << p->data << " повторяется "; // вывод значения элемента p
        cout << p->countH << " раз\n";
        if (p->countH > 1) {
            cout << "\033[31m Обнаружен повтор элемента " << p->data << "\033[0m \n";
            countSame++;
        }
        p = p->next; // переход к следующему узлу
    } while (p != nullptr);
    if (countSame == 0)
        cout << "\033[31m В дереве нет одинаковых элементов \033[0m" << "\n";
    else
        cout << "\033[31m В дереве " << countSame << " одинаковых элементов разных видов \033[0m" << "\n";
}

Simple SimpleList::checkSimple(T sign){
    Simple p = this;
    do {
        if (p->data == sign) {
            p->countH++;          //если в линейном списке уже есть такой элемент, то его количество увеличивается на 1
            return p;
        }
        p = p->next; // переход к следующему узлу
    } while (p != nullptr);
    return nullptr;
}

void recTreePrint(Tree node) {
    if (!node) {
        cout << '/';
        return;
    }
    cout << node->getData();
    recTreePrint(node->getLeft());      //печать левого
    recTreePrint(node->getRight());     //печать правого
}


Tree readBT(string input){
    T sign = input[readIndex];
    readIndex++;
    if (sign == '/'){        //если элемент пустой
        return nullptr;
    }
    else{
        Tree buf = new Elem();   //если нет, создаем листок
        buf->setData(sign);
        buf->setLeft(readBT(input));
        buf->setRight(readBT(input));
        return buf;
    }
}

int count(string str, char c){     //подсчет конкретного символа в строке
    int count = 0;
    for (char symbol : str){
        if (symbol == c)
            count++;
    }
    return count;
}

void treePrint(Simple head, Tree tree) {
    if (tree != nullptr) { //Пока не встретится пустой узел
        Simple p = head->checkSimple(tree->getData());
        if (!p) {
            if (head->data == '\0') {
                cout << "Головой вспомогательного линейного списка будет " << tree->getData() <<  "\n";
                head->initHead(tree->getData());
            }
            else
                head->push(tree->getData());
        }
        treePrint(head, tree->getLeft()); //Рекурсивная функция для левого поддерева
        treePrint(head, tree->getRight()); //Рекурсивная функция для правого поддерева
    }
}


int main() {
    string input;
    ifstream file;
    string name;

    cout << "Выберите:\n1. Ввод списка с консоли\n2. Ввод списка с файла\n";
    int choice = 0;
    cin >> choice;

    switch(choice){
        case 1:
            cout << "Введите запись дерева в виде строки, где '/' - пустой элемент: \n";
            cin >> input;
            break;
        case 2:
            cout << "Введите полный путь до файла: \n";
            cin >> name;
            file.open(name);
            if (!file.is_open()){
                cout << "Файл не может быть открыт!\n";
                exit(1);
            }
            getline(file, input);    //считывание из файла строки с данными
            file.close();  //закрытие файла
            break;
        default:
            cout << "Вы должны ввести 1 или 2";
            return 0;
    }

    if ((2*count(input, '/') - input.length() != 1) || (input[0] == '/')){ //проверка на то, что '/' на одну больше, чем остальных символов
        cout << "Данные некорректны";
        return 0;
    }
    Tree root = readBT(input);
    cout << "Введенное дерево: ";
    recTreePrint(root);
    cout << "\n";
    auto head = new SimpleList();
    treePrint(head,root);
    head->listPrint();
    return 0;
}
