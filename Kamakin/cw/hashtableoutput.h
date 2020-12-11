#ifndef COURSEWORK_HASHTABLEOUTPUT_H
#define COURSEWORK_HASHTABLEOUTPUT_H

#include "hashtable.h"

#define RED_COLOR "\033[31m"
#define BLUE_COLOR "\033[34m"
#define GREEN_COLOR "\033[32m"
#define RESET "\033[0m"

/*
 * This class provides methods to output
 * information about main operations in hashtable.
 */

template <typename T>
class HashTableOutput {
    HashTable<T> &table_;
    pOStream output_; // stream to output the information

public:
    HashTableOutput(HashTable<T> &table, pOStream output) : table_(table), output_(output) {}

    void remove(T value) {
        auto table = table_.getTable();
        table_.remove(value, output_);
        bool flag = true;

        for (auto i = 0; i < table.size(); i++) { // iterating through the map
            *output_ << "Table[" << i << "] = ";

            for (const auto &elem : table[i]) {
                if (flag && elem == value) {
                    *output_ << RED_COLOR << elem << RESET << "->";
                    flag = false;
                } else
                    *output_ << elem << "->";
            }

            *output_ << '\n';
        }
    }

    // add an array of the elements to the map
    void add(std::vector<T> &value) {
        std::map<int, std::vector<T>> hash = getHashMap(value); // get a map of the hashes
        auto table = table_.getTable();

        for (auto i = 0; i < table.size(); i++) { // iterating through the map
            *output_ << "Table[" << i << "] = ";
            for (const auto &elem : table[i]) // output old elements
                *output_ << elem << "->";
            for (const auto &elem : hash[i]) { // insert new elements and output them
                table_.add(elem);
                *output_ << GREEN_COLOR << elem << RESET << "->";
            }

            *output_ << '\n';
        }
    }

    std::map<T, int> count(std::vector<T> &value) {
        std::map<int, std::vector<T>> hash = getHashMap(value); // get a map of the hashes
        std::map<T, int> count;
        auto table = table_.getTable();

        for (auto i = 0; i < table.size(); i++) { // iterating through the map
            *output_ << "Table[" << i << "] = ";
            for (const auto &elem : table[i]) {
                if (isIn(value, elem)) { // if elem is in the map then count and output
                    *output_ << BLUE_COLOR << elem << RESET << "->";
                    count[elem]++;
                }
                else // just output the elem
                    *output_ << elem << "->";
            }

            *output_ << '\n';
        }

        return count;
    }

    void printTable(std::ostream &out) {
        auto table = table_.getTable();

        for (auto i = 0; i < table.size(); i++) {
            out << "Table[" << i << "] = ";

            for (const auto &elem : table[i])
                out << elem << "->";

            out << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream &out, HashTableOutput<T> &table) { // output operator
        table.printTable(out);
        return out;
    }

    bool isIn(std::vector<T> &vector, T value) {
        for (const auto &elem : vector)
            if (value == elem)
                return true;

        return false;
    }

    std::map<int, std::vector<T>> getHashMap(std::vector<T> &value) {
        std::map<int, std::vector<T>> hash;

        for (const auto &elem : value) {
            auto key = table_.hash(elem, output_);
            hash[key].push_back(elem);
            *output_ << "Hash for (" << elem << ") = " << key << '\n';
        }

        return hash;
    }
};

#endif //COURSEWORK_HASHTABLEOUTPUT_H

