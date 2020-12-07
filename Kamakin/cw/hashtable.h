#ifndef COURSEWORK_HASHTABLE_H
#define COURSEWORK_HASHTABLE_H

#include <list>
#include <vector>
#include <iostream>

/*
 * This is class template of a hash table. Hash function calculated
 * based on the table's size and the length of a value.
 * Table based on std::list.
 */

template <typename T>
class HashMap {
    std::vector < std::list<T> > table_;
    int size_;

public:
    explicit HashMap(int size) : size_(size) {
        table_.resize(size_);
    }

    void add(T value) {
        auto hash = getHash(value); // get the hash of a value
        std::cout << "Calculated hash = " << hash << '\n';
        std::cout << "Pushing to [" << hash << "]" << '\n';
        table_[hash].push_back(value); // add the element
    }

    int count(T value) {
        auto key = getHash(value), count = 0; // get the hash
        std::cout << "Hash = " << key << '\n';
        std::cout << "Counting the element: " << '\n';

        for (const auto &elem : table_[key]) {
            if (value == elem) {
                std::cout << "Found the element, counting.." << '\n';
                count++;
            }
            else
                std::cout << "Got (" << elem << ")\n";
        }

        return count;
    }

    int remove(T value) {
        auto key = getHash(value); // get the hash
        std::cout << "Hash = " << key << '\n';

        for (const auto &elem : table_[key]) { // remove all repeated elements in foreach
            if (value == elem) {
                std::cout << "Found the element, deleting.." << '\n';
                table_[key].remove(value);
                return 1;
            } else
                std::cout << "Got (" << elem << ")\n";
        }

        std::cout << "The element is not in the map" << '\n';
        return 0;

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

    int getHash(T value) { // hash function
        auto hash = 0;

        for (auto i = 0; i < value.size(); i++)
            hash = 37 * hash + value[i]; // calculated based on the length

        hash %= size_; // correct the hash

        return hash >= 0 ? hash : hash + size_;
    }
};

#endif //COURSEWORK_HASHTABLE_H
