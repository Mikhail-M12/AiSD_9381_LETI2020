#ifndef COURSEWORK_HASHTABLE_H
#define COURSEWORK_HASHTABLE_H

#include <list>
#include <vector>
#include <map>
#include <iostream>
#include "hashtablestate.h"
#include "advancedstate.h"
#include "simplestate.h"

#define RED_COLOR "\033[31m"
#define BLUE_COLOR "\033[34m"
#define GREEN_COLOR "\033[32m"
#define RESET "\033[0m"

/*
 * This is class template of a hash table. Hash function calculated
 * based on the table's size and the length of a value.
 * Table based on std::list.
 */

template <typename T>
class HashMap {
    std::vector < std::list<T> > table_;
    std::shared_ptr< HashTableState<T> > state_; // smart pointer for an abstract class
    int size_;

public:
    explicit HashMap(int size, std::shared_ptr<HashTableState<T>> state) : size_(size), state_(state) {
        table_.resize(size_);
    }

    void setState(std::shared_ptr<HashTableState<T>> state) {
        state_ = state;
    }

    // resize the hashmap and recalculate all hashes
    void resize(int newSize) {
        HashMap<T> newMap(newSize, state_);

        for (auto i = 0; i < size_; i++)
            for (auto elem : table_[i])
                newMap.add(elem);

        *this = newMap;
    }

    // add a single element to the map
    void add(T value) {
        auto key = state_->hash(*this, value);
        table_[key].push_back(value);
    }

    // add an array of the elements to the map
    void add(std::vector<T> &value) {
        std::map<int, std::vector<T>> hash = getHashMap(value); // get a map of the hashes

        for (auto i = 0; i < hash.size(); i++) { // iterating through the map
            std::cout << "Table[" << i << "] = ";
            for (const auto &elem : table_[i]) // output old elements
                std::cout << elem << "->";
            for (const auto &elem : hash[i]) { // insert new elements and output them
                table_[i].push_back(elem);
                std::cout << GREEN_COLOR << elem << RESET << "->";
            }

            std::cout << '\n';
        }
    }

    int count(T value) {
        auto hash = getHashAdvanced(value), count = 0;

        for (const auto &elem : table_[hash])
            if (value == elem)
                count++;

        return count;
    }

    std::map<T, int> count(std::vector<T> &value) {
        std::map<T, int> count;

        for (auto i = 0; i < table_.size(); i++) { // iterating through the map
            std::cout << "Table[" << i << "] = ";
            for (const auto &elem : table_[i]) {
                if (isIn(value, elem)) { // if elem is in the map then count and output
                    std::cout << BLUE_COLOR << elem << RESET << "->";
                    count[elem]++;
                }
                else // just output the elem
                    std::cout << elem << "->";
            }

            std::cout << '\n';
        }

        return count;
    }

    void remove(T value) {
        for (auto i = 0; i < table_.size(); i++) { // iterating through the map
            std::cout << "Table[" << i << "] = ";

            for (auto elem = begin(table_[i]); elem != end(table_[i]); elem++) {
                if (*elem == value){ // if elem is for deleting then erase and return
                    std::cout << RED_COLOR << *elem << RESET << "->";
                    table_[i].erase(elem);
                    std::cout << '\n';
                    return;
                } else // just output
                    std::cout << *elem << "->";
            }

            std::cout << '\n';
        }
    }

    friend std::ostream& operator<<(std::ostream &out, const HashMap<T> &table) { // output operator
        for (auto i = 0; i < table.size_; i++) {
            out << "Table[" << i << "] = ";

            for (const auto &elem : table.table_[i])
                out << elem << "->";

            out << "\n";
        }

        return out;
    }

    int getHashAdvanced(T value) { // hash function
        std::cout << "Calculating hash for (" << value << ")\n";
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++) {
            std::cout << "Hash = 37 * " << hash << " + " << (int)value[i];
            hash = 37 * hash + value[i]; // calculated based on the length
            std::cout << " = " << hash << '\n';
        }

        std::cout << "Correcting hash = hash % size_ = " << hash << " % " << size_;
        hash %= size_; // correct the hash
        std::cout << " = " << hash << '\n';
        return hash;
    }

    int getHashSimple(T value) {
        std::cout << "Calculating hash for (" << value << ")\n";
        size_t hash = 0;

        for (auto i = 0; i < value.size(); i++) {
            std::cout << "Hash += " << (int)value[i];
            hash += value[i]; // calculated based on the length
            std::cout << " = " << hash << '\n';
        }

        std::cout << "Correcting hash = hash % size_ = " << hash << " % " << size_;
        hash %= size_; // correct the hash
        std::cout << " = " << hash << '\n';
        return hash;
    }

private:
    bool isIn(std::vector<T> &vector, T value) {
        for (const auto &elem : vector)
            if (value == elem)
                return true;

        return false;
    }

    std::map<int, std::vector<T>> getHashMap(std::vector<T> &value) {
        std::map<int, std::vector<T>> hash;

        for (const auto &elem : value) {
            auto key = state_->hash(*this, elem);
            hash[key].push_back(elem);
            std::cout << "Hash for (" << elem << ") = " << key << '\n';
        }

        return hash;
    }
};

#endif //COURSEWORK_HASHTABLE_H
