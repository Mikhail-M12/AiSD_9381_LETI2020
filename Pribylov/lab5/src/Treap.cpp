#include <iostream>
#include "Treap.h"

namespace treap {

    int generateRandom() {
        return std::rand();
    }

    TreapPtr buildTreap(const std::vector<int>& keys) {
        auto tr = std::make_shared<Treap>(keys[0], generateRandom());
        for (int i = 1; i < keys.size()-1; i++) {
            auto node = tr->search(keys[i]);
            if (node)
                node->count++;
            else
                tr = tr->add(keys[i]);
        }
        return tr;
    }

    Treap::Treap(int key, int priority, TreapPtr left, TreapPtr right)
            : key(key), priority(priority), left(left), right(right) {}

    TreapPtr Treap::merge(TreapPtr L, TreapPtr R) {
        if (L == nullptr) return R;
        if (R == nullptr) return L;

        if (L->priority > R->priority) {
            return std::make_shared<Treap>(L->key, L->priority, L->left, merge(L->right, R));
        } else {
            return std::make_shared<Treap>(R->key, R->priority, merge(L, R->left), R->right);
        }
    }

    void Treap::split(int key, TreapPtr& L, TreapPtr& R) const {
        TreapPtr newTreap = nullptr;
        if (this->key <= key) {
            if (right == nullptr)
                R = nullptr;
            else
                right->split(key, newTreap, R);
            L = std::make_shared<Treap>(this->key, priority, left, newTreap);
        } else {
            if (left == nullptr)
                L = nullptr;
            else
                left->split(key, L, newTreap);
            R = std::make_shared<Treap>(this->key, priority, newTreap, right);
        }
    }

    TreapPtr Treap::add(int key) {
        TreapPtr l = nullptr, r = nullptr;
        split(key, l, r);
        TreapPtr tmp = std::make_shared<Treap>(key, generateRandom());
        return merge(merge(l, tmp), r);
    }

    Treap* Treap::search(int key) {
        if (key == this->key) return this;
        if (key < this->key) {
            if (left) return left->search(key);
        } else {
            if (right) return right->search(key);
        }
        return nullptr;
    }

    void Treap::print() {
        std::cout << "x=" << key << "; y=" << priority << "\n";
        if (left) left->print();
        if (right) right->print();
    }

}