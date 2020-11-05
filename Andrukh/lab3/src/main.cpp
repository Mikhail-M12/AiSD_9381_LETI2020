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


void recTreePrint(Tree node) {
    if (!node) {
        cout << '/';
        return;
    }
    cout << node->getData();
    recTreePrint(node->getLeft());      //печать левого
    recTreePrint(node->getRight());     //печать правого
}


void recLeafPrint(Tree root){
    if(!root)
        return;
    if((root->getLeft()== nullptr)&&(root->getRight()== nullptr))
        cout << " " << root->getData();
    recLeafPrint(root->getLeft());
    recLeafPrint(root->getRight());

}



int getMaxDepth(Tree root, int depth) { //находит максимальную глубину дерева
    if (!root)
        return depth;
    return max(getMaxDepth(root->getLeft(), depth + 1), getMaxDepth(root->getRight(), depth + 1));
}



int countelem(Tree root, int level, int i)  //считает количество элементов на уровне level
{
    static int cnt = 0;

    if(!root)
        return 0;
    else if(i == level) {
        cout<<root->getData()<<"\n";
        return 1;
    }
    else {
        cnt += countelem(root->getLeft(), level,i+1);
        cnt += countelem(root->getRight(), level,i+1);
    }
    return (i > 1) ? 0 : cnt;
}


Tree readBT(string input){    //создание дерева
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


int countSymbols(string str, char c){     //подсчет конкретного символа в строке для проверки корректности введенных данных
    int count = 0;
    for (char symbol : str){
        if (symbol == c)
            count++;
    }
    return count;
}


int main() {
    string input;
    ifstream file;
    string name;

    cout << "Выберите:\n1. Ввод строки с консоли\n2. Чтение строки из файла\n";
    int choice = 0;
    cin >> choice;

    switch(choice){
        case 1:
            cout << "Введите дерево в виде строки, начиная с корня, пустой элемент обозначать: '/' \n";
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

    if ((2*countSymbols(input, '/') - input.length() != 1) || (input[0] == '/')){ //проверка на то, что '/' на одну больше, чем остальных символов
        cout << "Введенные данные некорректны";
        return 0;
    }
    Tree root = readBT(input);
    cout << "Введенное дерево: ";
    recTreePrint(root);
    cout << "\n";
    cout << "Листья дерева: ";
    recLeafPrint(root);

    cout << "\nМаксимальная глубина дерева\n";
    cout << getMaxDepth(root,0);

    cout<<"\nПодсчёт количества узлов заданного уровня:";
    cout << "\nВведите число не более " << getMaxDepth(root,0) << "\n";
    int cur;
    cin >> cur;
    if(cur>getMaxDepth(root,0))
        cout << "\nЧисло превышает количество узлов в дереве\n";
    else {
        cout << "\nКоличество узлов на данном уровне:\n" << countelem(root,cur,1);
    }


    return 0;
}


