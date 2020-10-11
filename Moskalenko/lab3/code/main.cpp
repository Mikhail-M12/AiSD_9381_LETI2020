#include <fstream>
#include "Elem.h"
#include "SimpleList.h"

static int readIndex;     //переменная, отвечающая за индекс элемента в строке

tree readBT(string input){
    T sign = input[readIndex];
    readIndex++;
    if (sign == '/'){        //если элемент пустой
        return nullptr;
    }
    else{
        tree buf = new Elem();   //если нет, создаем листок
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

void treePrint(Simple head, tree tree) {
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

    if ((2*count(input, '/') - input.length() != 1) || (input[0] == '/')){ //поверка на то, что '/' на одну больше, чем остальных символов
        cout << "Данные некорректны";
        return 0;
    }
    tree root = readBT(input);
    cout << "Введенное дерево: ";
    recTreePrint(root);
    cout << "\n";
    auto head = new SimpleList();
    treePrint(head,root);
    head->listPrint();
    return 0;
}
