#ifndef COURSEWORK_ADVANCEDSTATE_H
#define COURSEWORK_ADVANCEDSTATE_H

#include "hashtablestate.h"
#include "hashtable.h"

template <typename T>
class AdvancedState : public HashTableState<T> {
public:
    int hash(HashTable<T> &map, T value, pOStream output) override {
        return output ? map.getHashAdvanced(value, output) : map.getHashAdvanced(value);
    }
};

#endif //COURSEWORK_ADVANCEDSTATE_H

