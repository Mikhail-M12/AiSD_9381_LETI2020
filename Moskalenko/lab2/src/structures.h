#ifndef LAB3EXAMPLE_STRUCTURES_H
#define LAB3EXAMPLE_STRUCTURES_H
#include <fstream>
using namespace std;

struct hlist;

typedef hlist* HListP;

struct Pair {
    HListP head; //предыдущий узел
    HListP tail; //следующий
};

struct hlist {
    int tag; //0 - pair, 1 - atom
    union {
        char atom;
        Pair pair;
    } Node;
};

struct SimpleList{
    char data;  //значение
    struct SimpleList* next; //ссылка на следующий элемент
};
 typedef SimpleList* Simple;

int isAtom(HListP list); //проверка, является ли элемент списка атомом
void readList(HListP &list, istream& stream); //считывает пробелы до списка
void readExp(char prev, HListP& list, istream& stream); //создает атомы и вызывает readRecursion
void readRecursion(HListP& list, istream& stream); //Рекурсивная функция, которая обрабатывает строку и создает и скрепляет узлы между собой.
void output(HListP list); //Выводит на экран список в виде атомов и узлов  в виде скобок.
void outputRecursion(HListP list);
HListP getHead(HListP list); //возвращает указатель на head
HListP getTail(HListP list); //возвращает указатель на tail
bool isNull(HListP list); //проверка, пустой ли список
HListP addNode(HListP head, HListP tail); //присоединяет узел к списку
HListP makeAtom(const char sign);
void makeSimpleList(HListP list, Simple head);
void destroy (HListP s); //уничтожение списка

void push(Simple head, char data); //добавление элемента в линейный список
void listPrint(Simple list); //печать линейного списка
bool checkAtomInSimple(Simple head, char atom); //проверка вхождения атома в линейный список
void initHead(Simple head, char data); //инициализация головы списка

#endif //LAB3EXAMPLE_STRUCTURES_H
