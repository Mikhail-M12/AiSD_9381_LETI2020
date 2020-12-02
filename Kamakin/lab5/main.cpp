#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>

template <typename T>
class HashTable {
    std::vector < std::list<T> > table_;
    int size_;

public:
    explicit HashTable(int size) : size_(size) {
        table_.resize(size_);
    }

    void add(T value) {
        table_[hash(value)].push_back(value);
    }

    int count(T value) {
        auto key = hash(value), count = 0;

        for (const auto &elem : table_[key])
            if (value == elem)
                count++;

        return count;
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<T> &table) {
        for (auto i = 0; i < table.size_; i++) {
            out << "Table[" << i << "] = ";
            for (const auto &elem : table.table_[i])
                out << elem << "->";
            out << "\n";
        }

        return out;
    }

private:
    int hash(T value) {
        return value.size() % size_;
    }

};

void outputHelp(std::ostream &output) {
    output << "Choose one of the following actions: " << '\n';
    output << "1. Find the elements" << '\n';
    output << "2. Add the elements" << '\n';
    output << "3. Open a file" << '\n';
    output << "4. Close the file and read from std::cin" << '\n';
    output << "5. Exit" << '\n';
    output << "Your action: ";
}

int getAction(std::istream &input) {
    int action;
    outputHelp(std::cout);
    input >> action;
    input.ignore();
    return action;
}

std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> strings;
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }

    return strings;
}

void readString(std::istream &stream, std::string &string) {
    std::cout << "Input: ";
    getline(stream, string, '\n');
    std::cout << "Your string: " << string << '\n';
}

int main() {
    HashTable<std::string> table(10);
    int action;

    std::ifstream file;
    std::string filePath;
    std::string string;
    std::vector<std::string> elements;
    std::istream *input = &std::cin;

    while ((action = getAction(std::cin)) != 5) {

        switch (action) {
            case 1:
                readString(*input, string);
                elements = split(string, ' ');

                for (auto &i : elements)
                    std::cout << i << " contains " << table.count(i) << " times in the table" << '\n';

                break;
            case 2:
                readString(*input, string);
                elements = split(string, ' ');

                for (auto &i : elements)
                    table.add(i);

                break;
            case 3:
                std::cout << "Path to the file: ";
                std::cin >> filePath;
                file.open(filePath);

                if (!file.is_open()) {
                    std::cout << "Couldn't open the file, please try again" << '\n';
                    continue;
                }

                input = &file;
                break;
            case 4:
                if (file.is_open())
                    file.close();
                input = &std::cin;
                break;
            case 5:
            default:
                std::cout << "Exiting the program" << '\n';
                return 0;
        }

        std::cout << '\n' << "The table is: " << '\n';
        std::cout << table << '\n';
    }

    return 0;
}
