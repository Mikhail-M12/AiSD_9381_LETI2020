#ifndef LAB3_4_SIMPLELIST_H
#define LAB3_4_SIMPLELIST_H
#include <iostream>
using namespace std;

class SimpleList;
typedef SimpleList* Simple;
typedef char T;
static int countSame = 0;
class SimpleList {
public:
    T data; //значение
    SimpleList *next; //ссылка на следующий элемент
    int countH;

    SimpleList() : data('\0'), next(nullptr), countH(1) {};

    SimpleList(T sign, Simple elem = nullptr, int count = 1) : data(sign), next(elem), countH(count) {};

    void push(T sign);

    void listPrint();

    void initHead(T sign)
    {
        data = sign;            // инициализация головы линейного списка
    }

    Simple checkSimple(T sign);

};

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

#endif //LAB3_4_SIMPLELIST_H

