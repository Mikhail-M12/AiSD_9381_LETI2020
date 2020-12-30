#include <iostream>
#include "Treap.h"

namespace treap {

    TreapPtr build(const std::vector<int>& keys) {
        Logger::instance().stream.setstate(std::ios_base::failbit);
        std::cout.setstate(std::ios_base::failbit);

        auto tr = std::make_shared<Treap>(keys[0]);
        for (int i = 1; i < keys.size(); i++) {
            insert(tr, keys[i]);
        }

        Logger::instance().stream.clear();
        std::cout.clear();
        return tr;
    }

    Treap::Treap(int key, int priority, TreapPtr left, TreapPtr right)
            : key(key), priority(priority), left(left), right(right) {};

    TreapPtr makeNode(int key) {
        return std::make_shared<Treap>(key);
    }

    TreapPtr merge(const TreapPtr& L, const TreapPtr& R) {
        if (L == nullptr) return R;
        if (R == nullptr) return L;

        TreapPtr merged = nullptr;
        if (L->priority > R->priority) {
            merged = merge(L->right, R);
            merged = std::make_shared<Treap>(L->key, L->priority, L->left, merged);
        } else {
            merged = merge(L, R->left);
            merged = std::make_shared<Treap>(R->key, R->priority, merged, R->right);
        }
        return merged;
    }

    TreapPair split(const TreapPtr& T, int key) {
        if (T == nullptr) return TreapPair(nullptr, nullptr);

        if (T->key <= key) {
            TreapPair R = split(T->right, key);
            TreapPtr L = std::make_shared<Treap>(T->key, T->priority, T->left, R.first);
            return TreapPair(L, R.second);
        } else {
            TreapPair L = split(T->left, key);
            TreapPtr R = std::make_shared<Treap>(T->key, T->priority, L.second, T->right);
            return TreapPair(L.first, R);
        }
    }

    TreapPtr insert(TreapPtr& T, int key) {
        Logger::instance().log("Добавление элемента M с ключом " + std::to_string(key) + ":\n");
        TreapPtr newNode = std::make_shared<Treap>(key);

        TreapPair pair = split(T, key);
        Logger::instance().log("Дерево T расщеплено по ключу " + std::to_string(key) + ":\n");
        Logger::instance().log("Левая половинка L: \n");
        printTree(pair.first, nullptr, false, key);
        Logger::instance().log("Правая половинка R: \n");
        printTree(pair.second, nullptr, false, key);

        TreapPtr left = merge(pair.first, newNode);
        Logger::instance().log("Левая половинка L сцеплена с элементом M с ключом " + std::to_string(key) + ":\n");
        printTree(left, nullptr, false, key);

        T = merge(left, pair.second);
        Logger::instance().log("Получившееся дерево L+M сцеплено с правой половинкой R:\n");
        printTree(T, nullptr, false, key);

        Logger::instance().log("Добавление элемента завершено.\n");
        return T;
    }

    TreapPtr remove(TreapPtr& T, int key) {
        if (T == nullptr) {
            Logger::instance().log("Дерево пусто. Удаление не проводится\n");
            return T;
        }
        Logger::instance().log("Удаление элемента с ключом " + std::to_string(key) + ":\n");

        TreapPair pair = split(T, key-1);
        Logger::instance().log("Дерево T расщеплено по ключу " + std::to_string(key-1) + ":\n");
        Logger::instance().log("Левая половинка L: \n");
        printTree(pair.first, nullptr, false, key);
        Logger::instance().log("Правая половинка R: \n");
        printTree(pair.second, nullptr, false, key);

        TreapPair pairR = split(pair.second, key);
        Logger::instance().log("Правая половинка расщеплена по ключу " + std::to_string(key-1) + ":\n");
        Logger::instance().log("Её левая половинка M: \n");
        printTree(pairR.first, nullptr, false, key);
        Logger::instance().log("Её правая половинка R': \n");
        printTree(pairR.second, nullptr, false, key);

        T = merge(pair.first, pairR.second);
        Logger::instance().log("Левая половинка L сцеплена с правой половинкой правого поддерева R' (исключили M):\n");
        printTree(T, nullptr, false, key);

        Logger::instance().log("Удаление элемента завершено.\n");
        return T;
    }





    void showTrunks(Trunk *p)
    {
        if (p == nullptr) return;
        showTrunks(p->prev);
        std::cout << p->str;
    }

    void printTree(TreapPtr root, Trunk *prev, bool isLeft, int greenkey)
    {
        if (root == nullptr) return;

        std::string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);
        printTree(root->left, trunk, true, greenkey);

        if (!prev)
            trunk->str = "---";
        else if (isLeft)
        {
            trunk->str = ".---";
            prev_str = "   |";
        }
        else
        {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        if (root->key == greenkey) {
            std::cout << "\033[1;32m" <<root->key<<"\033[0m\n";
        } else {
            std::cout << root->key << "\n";
        }

        if (prev)
            prev->str = prev_str;
        trunk->str = "   |";

        printTree(root->right, trunk, false, greenkey);

    }

}