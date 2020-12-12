#include "HList.h"

namespace hlist
{
    Node::Node(element elem) : cur(elem) {}

    bool Node::operator==(const Node& other) const {
        // если типы текущих узлов различны - узлы однозначно не идентичны
        if (cur.index() != other.cur.index()) {
            Logger::instance().logNodeOperatorEquals(toString(), other.toString(), false);
            return false;
        }
        if (std::holds_alternative<atom>(cur)) {
            // если текущие узлы - атомы, сравниваются атомы
            bool res = std::get<atom>(cur) == std::get<atom>(other.cur);
            Logger::instance().logNodeOperatorEquals(toString(), other.toString(), res);
            return res;
        } else {
            // если же текущие узлы - указатели на внутренний список,
            // сравниваются списки (вызывается оператор сравнения класса HList) - косвенная рекурсия
            bool res = *(std::get<HList *>(cur)) == *(std::get<HList *>(other.cur));
            Logger::instance().logNodeOperatorEquals(toString(), other.toString(), res);
            return res;
        }
    }

    bool Node::operator!=(const Node& other) const {
        return !(*this == other);
    }

    std::string Node::toString() const {
        if (std::holds_alternative<atom>(cur)) {
            return std::string(1, std::get<atom>(cur));
        } else {
            return std::get<HList *>(cur)->toString();
        }
    }


    HList::HList() : head(nullptr), tail(nullptr) {}

    HList::HList(const std::string &from) : HList() {
        if (!isStringCorrect(from)) {
            Logger::instance().log("Строка \"" + from + "\" некорректна. Создан пустой список.");
            return;
        }
        int pos = 0;
        readFromString(from, pos);
    }

    HList::~HList() {
        Node* tmp = head;
        while (tmp) {
            head = tmp->next;
            if (std::holds_alternative<HList *>(tmp->cur)) {
                // если текущий узел - внутренний список, память под него тоже очищается
                delete *std::get_if<HList *>(&(tmp->cur));
            }
            delete tmp;
            tmp = head;
        }
    }

    bool HList::operator==(const HList& other) const {
        Node* i = head; Node* j = other.head;
        // продвигается по спискам, пока не достигнут конец хотя бы одного из них,
        // либо пока соответствующие узлы равны (вызывается оператор сравнения класса Node) - косвенная рекурсия
        while (i && j && *i == *j) {
            i = i->next, j = j->next;
        }
        // последняя проверка на идентичность - концы обоих списков достигнуты
        return !i && !j;
    }

    bool HList::isStringCorrect(const std::string &str) {
        int pos = 0, bracketPairsCount = 0;
        while (str[pos] == ' ') pos++;
        if (str[pos] != '(') return false;

        bracketPairsCount++;
        while (++pos != str.length() && bracketPairsCount != 0) {
            if (str[pos] == ' ') continue;
            if (str[pos] == '(') bracketPairsCount++;
            else if (str[pos] == ')') bracketPairsCount--;
        }
        return pos == str.length() && bracketPairsCount == 0;
    }

    void HList::readFromString(const std::string &from, int &pos) {
        while (from[++pos] != ')' && pos < from.length()) {
            if (from[pos] == ' ') continue;
            if (from[pos] != '(') {
                pushBack(from[pos]);
            } else {
                HList* tmp = new HList;
                tmp->readFromString(from, pos);
                pushBack(tmp);
            }
        }
    }

    Node* HList::pushBack(element elem) {
        Node* node = new Node(elem);
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
        return node;
    }

    std::string HList::toString() const {
        std::string str;
        str += "(";
        if (head) {
            for (auto i = head; i != nullptr; i = i->next) {
                if (std::holds_alternative<atom>(i->cur)) {
                    str += std::get<atom>(i->cur);
                } else {
                    str += std::get<HList *>(i->cur)->toString();
                }
            }
        }
        str += ")";
        return str;
    }

}