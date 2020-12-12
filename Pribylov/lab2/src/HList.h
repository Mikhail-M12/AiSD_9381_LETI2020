#ifndef ALG_LAB2_HLIST_H
#define ALG_LAB2_HLIST_H

#include <variant>
#include <string>
#include "Logger.h"

namespace hlist
{
    struct HList;
    using atom = char;
    using element = std::variant<atom, HList*>; // элемент узла - либо атом, либо указатель на внутренний список

    struct Node
    {
        element cur;
        Node* next = nullptr;

        // создаёт узел с элементом
        explicit Node(element elem);

        // проверяет идентичность узлов
        bool operator==(const Node& other) const;
        bool operator!=(const Node& other) const;

        // возвращает узел в виде строки (для логгирования)
        std::string toString() const;
    };

    class HList
    {
    public:
        // создаёт пустой список
        HList();

        // создаёт список на основе строки с сокращённой скобочной записью;
        // если строка содержит некорректный список, создаётся пустой список
        explicit HList(const std::string &from);

        // очищает память
        ~HList();

        // проверяет идентичность списков
        bool operator==(const HList& other) const;

        // вставляет новый элемент в конец списка
        Node* pushBack(element elem);

        // возвращает сокращённое скобочное представление списка
        std::string toString() const;

    private:
        Node* head;
        Node* tail;

        // проверяет строку на корректность
        bool isStringCorrect(const std::string& str);

        // анализирует строку с сокращённой скобочной записью и добавляет в список элементы
        void readFromString(const std::string& from, int &pos);
    };

}
#endif //ALG_LAB2_HLIST_H
