#ifndef COURSEWORK_HASHTABLE_H
#define COURSEWORK_HASHTABLE_H

#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "hashtablestate.h"
#include "advancedstate.h"
#include "simplestate.h"

/*
 * This is class template of a hash table. Hash function calculated
 * based on the table's size and the length of a value.
 * Table based on std::list.
 */

template <typename T>
class HashTable {
    std::vector < std::list<T> > table_;
    std::shared_ptr < HashTableState<T> > state_; // smart pointer for an abstract class
    int size_;

public:
    HashTable(int size, std::shared_ptr < HashTableState<T> > state) :
        size_(size), state_(state) {
        table_.resize(size_);
    }

    void setState(std::shared_ptr < HashTableState<T> > state) {
        state_ = state;
    }

    // resize the hashmap and recalculate all hashes
    void resize(int newSize, pOStream output = nullptr) {
        HashTable<T> newMap(newSize, state_);

        for (auto i = 0; i < size_; i++)
            for (auto elem : table_[i])
                newMap.add(elem, output);

        *this = newMap;
    }

    // add a single element to the map
    void add(T value, pOStream output = nullptr) {
        auto key = state_->hash(*this, value, output);
        table_[key].push_back(value);
    }


    int count(T value) {
        auto hash = state_->hash(*this, value), count = 0;

        for (const auto &elem : table_[hash])
            if (value == elem)
                count++;

        return count;
    }

    void remove(T value) {
        auto hash = state_->hash(*this, value);

        for (const auto &elem : table_[hash]) {
            if (elem == value) {
                table_[hash].remove(elem);
                break;
            }
        }
    }

    void remove(T value, pOStream output) {
        auto hash = state_->hash(*this, value, output);

        for (auto elem = begin(table_[hash]); elem != end(table_[hash]); elem++) {
            if (*elem == value) {
                table_[hash].erase(elem);
                break;
            }
        }
    }

    int hash(T value, pOStream output = nullptr) {
        return state_->hash(*this, value, output);
    }

    int getHashAdvanced(T value) { // hash function
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++)
            hash = 37 * hash + value[i]; // calculated based on the length

        hash %= size_; // correct the hash
        return hash;
    }

    int getHashAdvanced(T value, pOStream output) {
        *output << "Calculating hash for (" << value << ")\n";
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++) {
            *output << "Hash = 37 * " << hash << " + " << (int)value[i];
            hash = 37 * hash + value[i]; // calculated based on the length
            *output << " = " << hash << '\n';
        }

        *output << "Correcting hash = hash % size_ = " << hash << " % " << size_;
        hash %= size_; // correct the hash
        *output << " = " << hash << '\n';
        return hash;

    }

    int getHashSimple(T value) {
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++)
            hash += value[i]; // calculated based on the length

        hash %= size_; // correct the hash
        return hash;
    }

    int getHashSimple(T value, pOStream output) {
        *output << "Calculating hash for (" << value << ")\n";
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++) {
            *output << "Hash += " << (int)value[i];
            hash += value[i]; // calculated based on the length
            *output << " = " << hash << '\n';
        }

        *output << "Correcting hash = hash % size_ = " << hash << " % " << size_;
        hash %= size_; // correct the hash
        *output << " = " << hash << '\n';
        return hash;
    }

    std::vector < std::list<T> > getTable() {
        return table_;
    }

    int getSize() {
        return size_;
    }
};

#endif //COURSEWORK_HASHTABLE_H

