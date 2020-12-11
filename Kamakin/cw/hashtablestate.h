#ifndef COURSEWORK_HASHTABLESTATE_H
#define COURSEWORK_HASHTABLESTATE_H

#include <memory>
#include <vector>

using pOStream = std::ostream*;

template <typename T> class HashTable;

/*
 * This is an abstract class for pattern "state".
 * Hash table has different states for different hash functions;
 */

template <typename T>
class HashTableState {
public:
    virtual int hash(HashTable<T> &map, T value, pOStream output) = 0;
    ~HashTableState() = default;
};

#endif //COURSEWORK_HASHTABLESTATE_H

