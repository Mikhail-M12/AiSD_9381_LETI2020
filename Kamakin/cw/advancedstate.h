#ifndef COURSEWORK_ADVANCEDSTATE_H
#define COURSEWORK_ADVANCEDSTATE_H

#include "hashtablestate.h"
#include "hashtable.h"

template <typename T>
class AdvancedState : public HashTableState<T> {
public:
    int hash(HashMap<T> &map, T value) override {
        return map.getHashAdvanced(value);
    }
};

#endif //COURSEWORK_ADVANCEDSTATE_H
