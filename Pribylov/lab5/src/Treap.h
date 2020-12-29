#ifndef TREAP_TREAP_H
#define TREAP_TREAP_H

#include <utility>
#include <memory>
#include <ctime>
#include <vector>

namespace treap {

    using TreapPtr = std::shared_ptr<class Treap>;

    struct Treap {
        int key;
        int priority;
        TreapPtr left;
        TreapPtr right;
        int count = 1;

        Treap(int key, int priority, TreapPtr left = nullptr, TreapPtr right = nullptr);
        static TreapPtr merge(TreapPtr L, TreapPtr R);
        void split(int key, TreapPtr& L, TreapPtr& R) const;
        TreapPtr add(int key);
        Treap* search(int key);
        void print();
    };

    int generateRandom();
    TreapPtr buildTreap(const std::vector<int>& keys);
}

#endif //TREAP_TREAP_H
