#ifndef TREAP_TREAP_H
#define TREAP_TREAP_H

#include <utility>
#include <memory>
#include <ctime>
#include <vector>
#include "Logger.h"

namespace treap {

    using TreapPtr = std::shared_ptr<class Treap>;
    using TreapPair = std::pair<TreapPtr, TreapPtr>;

    // Рандомизированная дерамида поиска (РДП)
    struct Treap {
        int key; // ключ
        int priority; // приоритет
        TreapPtr left;
        TreapPtr right;

        // конструктор, принимает ключ key, приоритет priority, указатели на левое и правое поддеревья left и right
        Treap(int key, int priority = rand(), TreapPtr left = nullptr, TreapPtr right = nullptr);

    };

    // принимает два дерева L и R, сливает их в одно и возвращает его
    TreapPtr merge(const TreapPtr& L, const TreapPtr& R);

    // принимает дерево T и по ключу key расщепляет его, возвращает пару из левой и правой половинки
    TreapPair split(const TreapPtr& T, int key);

    // принимает дерево T и вставяет элемент с ключом key в него, возвращает это же дерево
    TreapPtr insert(TreapPtr& T, int key);

    // принимает дерево T и удаляет элемент с ключом key из него, возвращает это же дерево
    TreapPtr remove(TreapPtr& T, int key);

    // принимает вектор ключей keys и строит на их основе РДП
    TreapPtr build(const std::vector<int>& keys);


    // вспомогательная структура и набор функций для печати дерева
    struct Trunk
    {
        Trunk *prev;
        std::string str;

        Trunk(Trunk *prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };
    void showTrunks(Trunk *p);
    void printTree(TreapPtr root, Trunk *prev, bool isLeft, int greenkey);
}

#endif //TREAP_TREAP_H
