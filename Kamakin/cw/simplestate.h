#ifndef COURSEWORK_SIMPLESTATE_H
#define COURSEWORK_SIMPLESTATE_H

#include "hashtablestate.h"
#include "hashtable.h"

template <typename T>
class SimpleState : public HashTableState<T> {
public:
    int hash(HashTable<T> &map, T value, pOStream output) override {
        return output ? map.getHashSimple(value, output) : map.getHashSimple(value);
    }
};

#endif //COURSEWORK_SIMPLESTATE_H

