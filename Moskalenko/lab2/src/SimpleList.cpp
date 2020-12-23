#include "structures.h"
#include <iostream>
using namespace std;

void push(Simple head, char data){
    cout << "Добавляем " << data << " в линейный список" << "\n";
    Simple current = head;
    while (current->next != nullptr)
        current = current->next;
    Simple node;
    node = new SimpleList;
    node->data = data;
    node->next = nullptr;
    current->next = node;
}

void listPrint(Simple list)
{
    int count = 0;
    Simple p;
    p = list;
    do {
        cout << "\033[32mВ линейном списке:  " << p->data << "\n"; // вывод значения элемента p
        p = p->next; // переход к следующему узлу
        count++;
    } while (p != nullptr);
    cout << "\033[34m" "Количество элементов: " << count;
}

bool checkAtomInSimple(Simple head, char atom){
    cout << "Проверка, есть ли " << atom << " в линейном списке" << "\n";
    Simple p;
    p = head;
    do {
        if (p->data == atom)
            return true;
        p = p->next; // переход к следующему узлу
    } while (p != nullptr);
    return false;
}

void initHead(Simple head, char data) // datа- значение первого узла
{
    cout << "Создаем НАЧАЛО линейного списка" << "\n";
    head->data = data;
}