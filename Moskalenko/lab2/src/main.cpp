#include <iostream>
#include "structures.h"
using namespace std;

void printSpace(int space) {            // печать пробелов
    for (int i = 0; i < space; i++)
        cout << "   ";
}

HListP getHead(HListP list) {
    if (list == nullptr || isAtom(list))  //если список пуст или элемент - атом
        return nullptr;
    return list->Node.pair.head;
}

HListP getTail(HListP list) {
    if (list == nullptr || isAtom(list))  //если элемента нет или это атом, то возвращается нулевой указатель
        return nullptr;
    return list->Node.pair.tail;
}

int isAtom(HListP list) {
    if (list == nullptr)
        return 0;
    return (list->tag);  //возвращается 0 или 1, в зависимости атом это или узел
}

bool isNull(HListP list) {
    return list == nullptr;
}


HListP addNode(HListP head, HListP tail) {  //добавление узла
    if (isAtom(tail))
        return nullptr;
    HListP list;
    list = new hlist;           //создается указатель на новый элемент
    list->tag = 0;
    list->Node.pair.head = head;
    list->Node.pair.tail = tail;
    return list;
}

HListP makeAtom(const char sign) {
    HListP list;
    list = new hlist;
    list->tag = 1;       //1 - атом
    list->Node.atom = sign; //присваием значение
    return list;
}

void readList(HListP &list, istream& stream) {
    char sign;

    do {
        stream >> sign;          //считываем пробелы до первого символа
    } while (sign == ' ');

  /*  if (sign != '('){
        cout << "Элементы списка должны быть в круглых скобках. Попробуйте ещё раз.";
        exit(1);   //обработка ошибки
    } */
    readExp(sign, list, stream);
}

void readExp(char prev, HListP& list, istream& stream) {
    if (prev == ')')
    {
        cerr << "Список не может начинаться с )\n";
        exit(1);
    }
    if (prev != '(')
         list = makeAtom(prev);         //  создается новый атом
    else
        readRecursion(list, stream);
}

void readRecursion(HListP& list, istream& in) {
    char sign;
    HListP p1, p2;
    in >> sign;
    if (sign == ')')
        list = nullptr;
    else {
        readExp(sign, p1, in);
        readRecursion(p2, in);
        list = addNode(p1, p2);         //добавление узла в список
    }
}

void output(HListP list) {
    if (isNull(list))
        cout << "()";
    else if (isAtom(list))
        cout << list->Node.atom;
    else {
        cout << '(';
        outputRecursion(list);
        cout << ')';
    }
}

void outputRecursion(HListP list) {
    if (!isNull(list)) {
        output(getHead(list));          //вывод головы узла
        outputRecursion(getTail(list)); //вывод хвоста узла
    }
}

void makeSimpleList(HListP list, Simple head) {
    if (isNull(list)) //the end of our list
        return;
    static int space = 0;

    if (isAtom(list)) {
        printSpace(space);
        cout << "\033[34m Встретился символ " << list->Node.atom << "\033[0m" << '\n';
        if (head->data == '\0')
            initHead(head, list->Node.atom);   //инициализация головы
        else if (!checkAtomInSimple(head, list->Node.atom)){
            push(head,list->Node.atom);
        }
    }
    else
        {
        cout << "CHECK_HEAD вызов" << '\n';
        space++;
        printSpace(space);
        makeSimpleList(getHead(list), head);
        space--;
        printSpace(space);
         cout << "CHECK_HEAD конец" << '\n';

        cout << "CHECK_TAIL вызов" << '\n';
        space++;
        printSpace(space);
        makeSimpleList(getTail(list), head);
        space--;
        printSpace(space);
        cout << "CHECK_TAIL конец" << '\n';
    }
}


void destroy (HListP s)
{
    if ( s != nullptr) {
        if (!isAtom(s)) {
            destroy(getHead(s));
            destroy(getTail(s));
        }
        delete s;
    }
}

int main() {
    HListP list = nullptr; //инициалиация
    string name;
    ifstream file;
    cout << "Выберите:\n1. Ввод списка с консоли\n2. Ввод списка с файла\n";
    int choice = 0;
    cin >> choice;

    switch(choice){
        case 1:
            cout << "Введите список в формате (x y z (f d)). Будьте внимательнее со скобками.: \n";
            readList(list, cin);
            break;
        case 2:
            cout << "Введите полный путь до файла. В файле не должно быть строки без закрытых скобок.: \n";
            cin >> name;
            file.open(name);
            if (!file.is_open()){
                cout << "Файл не может быть открыт!\n";
                exit(1);
            }
            readList(list, file);
            file.close();  //закрытие файла
            break;
        default:
            cout << "Вы должны ввести 1 или 2";
            return 0;
    }

    cout << "\033[31m Введенный список: \033[0m" << "\n";
    output(list);
    cout << "\n";
    Simple head;
    head = new SimpleList;
    head->next = nullptr;
    head->data = '\0';  //пока head обнулена
    makeSimpleList(list, head);
    listPrint(head);
    destroy(list);
    return 0;
}

