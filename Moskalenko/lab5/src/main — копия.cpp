#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "node.h"

Node* fillBdp(Node* p){   // заполнение БДП с консоли
    cin.get();
    string str;
    getline(cin, str); // считываем строку чисел через пробел
    istringstream ss(str);
    vector<int>arr;   //вектор введенных чисел
    int x;
    while(ss >> x){
        arr.push_back(x);
        if(ss.peek() == ' ')  //игнорируем пробелы
            ss.ignore();
    }
    if (!ss.eof())   //если были введены символы кроме цифер
    {
        std::cout << "Строка имеет неправильный формат.\n";
        exit(1);
    }
    for(int val : arr) {   //добавляем элементы из вектора в БДП
        p = p->insert(p, val);
        cout << "\nДобавлен элемент " << val << '\n';
        p->recTreePrint(p);
    }
    return p;
}

Node* fillMas(Node* p, string name, int count){  // заполнение БДП с файла
    ifstream in(name);  //открываем файл
    if (!in.is_open()) {
        cout << "Файл не может быть открыт!\n";
        return p;
    }
    int x[count];
    for (int i = 0; i < count - 1; i++)
        in >> x[i];
    for (int i = 0; i < count - 1; i++) {
        p = p->insert(p, x[i]);
        cout << "Добавлен элемент " << x[i] << '\n';
        p->recTreePrint(p);
    }
    in.close(); //под конец закроем файла
    return p;
}

Node* fillBdpFile(Node* p, string name){  //подсчет количества чисел в файле
    //Создаем файловый поток и связываем его с файлом
    ifstream in(name);
    if (!in.is_open()) {
        cout << "Файл не может быть открыт!\n";
        return p;
    }
        int count = 0; // количество чисел в файле
        int temp;  //Временная переменная

        while (!in.eof()) // пробегаем пока не встретим конец файла eof
        {
            in >> temp;  //в пустоту считываем из файла числа
            count++; // увеличиваем счетчик количества чисел
        }

        in.close();
        return fillMas(p, name, count);
}

void info(){
    cout << "\n\t\tВведите:\n"
            "a - Для поиска элемента в БДП\n"
            "b - Для выхода из программы\n";
}

void choose(){
    cout << "\n\t\tДля выбора введите:\n"
           "1 - Считывание элементов с консоли\n"
           "2 - Считывание из файла\n";
}

Node* foo(Node* p, int k){
    switch(k){
        case 1:{
            cout << "\t\tВведите числа для построения дерева. \n";
            p = fillBdp(p);     //заполнение с консоли
            break;
        }

        case 2:{
            string name;
            cout << "Введите путь до файла.\n";
            cin >> name;
            p = fillBdpFile(p, name);      //заполнение с файла
            break;
        }

        default:
            cout << "Попробуйте еще раз.\n";
            break;
    }
    return p;
}

void destroy(Node* p)   //удаление дерева
{
    if(!p)
        return;
    destroy(p->getLeft());
    destroy(p->getRight());
    p = nullptr;
}

int main() {
    srand(time(0));
    Node *p = nullptr;
    choose();
    char choice;
    int k;
    cin >> k;
    p = foo(p, k);
    while (choice != 'b') {  //цикл, пока пользователь не выйдет из программы
        info();
        cin >> choice;
        switch (choice) {
            case 'a':{
                cout << "Введите искомый элемент:\n";
                cin >> k;
                int count = p->find(p, k);
                if (count)
                    cout << k << " содержится в дереве в количестве " << count << endl;
                else {
                    cout << k << " не входит в дерево." << endl;
                    p = p->insert(p, k);
                    cout << "Добавлен элемент " << k << endl;
                    p->recTreePrint(p);
                }
                break;
            }
            case 'b':
                cout << "Конец выполнения программы";
                break;
            default:
                cout << "Попробуйте ещё раз\n";
                break;
        }
    }
    destroy(p);  //очистка дерева
    return 0;
}