#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

template <class T>
class HuffmanTree{
private:
    HuffmanTree* left; // 0
    HuffmanTree* right; // 1
    bool flag = false; //true если лист
    T value;

public:
    HuffmanTree(ifstream& s);
    bool isLeaf(){ //возвращает true, если элемент является листом дерева
        return flag;
    }
    HuffmanTree *get_left() { //возвращает указатель на левый элемент
        return left;
    }
    HuffmanTree *get_right() { //возвращает указатель на првый элемент
        return right;
    }
    T val() { //возвращает кодируемый элемент
        cout << "символ декодированного текста: " << value << endl;
        return value;
    }
    ~HuffmanTree();
};

template <class T>
HuffmanTree<T>::HuffmanTree(ifstream& s/*элемент класса ifstream*/)  {
    flag = false;
    left = NULL;
    right = NULL;
    char ch;
    if (s.peek() == '('){ //.peek() Считывает байт из файла, но не переходит к следующему
        s >> ch; // извлекаем '('
        cout << "скобка: " << ch << endl;
    }
    else
        return;
    if (s.peek() == '('){
        left = new HuffmanTree(s);
        if (s.peek() == ')'){
            s >> ch; // извлекаем ')'
            cout << "скобка: " << ch << endl;
        }
    }
    else{
        flag = true;
        s >> value;
        cout << "элемент словаря: " << value << endl;
        return;
    }
    if (s.peek() == '('){
        cout << "скобка: " << ch << endl;
        right = new HuffmanTree(s);
        s >> ch; // извлекаем ')'
        if(ch != ')')
            cout << "буква кода: " << ch << endl;
    }
    if (s.peek() == ')'){
        s >> ch; // извлекаем ')'
        cout << "скобка: " << ch << endl;
    }
}

template <class T>
HuffmanTree<T>::~HuffmanTree(){//деструктор
    if (left)
        delete left;
    if (right)
        delete right;

}

int main(){
    int  c;
    string str_i, str_o;//названия входного и выходного файлов
    while(true){
        cout << "Нажмите 1, чтобы декодировать файл\n" << "Нажмите 2, чтобы выйти" << endl;
        cin >> str_i;
        if (!isdigit(str_i[0])) //проверка
            continue;
        c = stoi(str_i);
        str_i.clear();
        switch (c)
        {
            case 1:
                break;
            case 2:
                return 0;
            default:
                cout << "Введите 1 или 2" << endl;
                continue;
        }
        cout << "Введите файл с данными: ";
        cin >> str_i;
        cout << "Введите файл для записи: ";
        cin >> str_o;
        if (str_i == str_o){
            cout << "Названия файлов не могут совпадать" <<endl;
            continue;
        }
        ifstream f;
        ofstream o;
        char b;
        f.open(str_i);
        o.open(str_o);
        if (!f){//проверка на существование входного файла
            cout << "Невозможно открыть файл с данными" << endl;
            continue;
        }
        if (!o)//проверка на существование выходного файла
        {
            cout <<"Невозможно открыть файл для записи" << endl;
            continue;
        }
        HuffmanTree<char> *Dictionary = new HuffmanTree<char>(f); //создание и выделение памяти под словарь
        HuffmanTree<char> *tmp = Dictionary;
        while (!f.eof()){//пока не достигнут конец файла
            b = f.get();//считываем символ из файла f и возвращаем егo значение
            if ((b!='0')&&(b!='1')) {//если в закодированном сообщении встречен недопустимый символ, выводим в файл предупреждение
                o << "введенный файл не корректен";
                break;
            }
            else {
                cout << "символ кода: " << b << endl;

                if (f.peek() == EOF)
                    if (b == '\n')
                        break;
                if (tmp)
                    tmp = ((b & 1) == 0 ? tmp->get_left(): tmp->get_right()); //если 1, то спускаемся к правому поддереву, если 0, то к левому
                if (tmp && tmp->isLeaf()) {
                    o << tmp->val();//если дошли до листа, то запись раскодированного символа
                    tmp = Dictionary;
                }
            }
        }
        f.close();
        o.close();
        if (tmp)
            cout << str_i << " был декодирован в " << str_o << " успешно." << endl;
        else
        cout << str_i << " не корректен." << endl;
        delete Dictionary;
    }
}
