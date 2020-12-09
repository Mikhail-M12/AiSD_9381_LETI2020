#ifndef COURSEWORK_HASHTABLESTATE_H
#define COURSEWORK_HASHTABLESTATE_H

#include <memory>
#include <vector>

template <typename T> class HashMap;

/*
 * This is an abstract class for pattern "state".
 * Hash table has different states for different hash functions;
 */

template <typename T>
class HashTableState {
public:
    virtual int hash(HashMap<T> &map, T value) = 0;
    ~HashTableState() = default;
};

#endif //COURSEWORK_HASHTABLESTATE_H
