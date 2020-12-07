#include <string>
#include <fstream>
#include "hashtable.h"

// help for the user
void outputHelp(std::ostream &output) {
    output << "Choose one of the following actions: " << '\n';
    output << "1. Count the elements" << '\n';
    output << "2. Add the elements" << '\n';
    output << "3. Open a file" << '\n';
    output << "4. Close the file and read from std::cin" << '\n';
    output << "5. Delete an element" << '\n';
    output << "6. Exit" << '\n';
    output << "Your action: ";
}

// get an action from the user
int getAction(std::istream &input) {
    int action;
    outputHelp(std::cout);
    input >> action;
    input.ignore();
    return action;
}

// splits str on delimiter delim
std::vector<std::string> split(const std::string &str, char delim) {
    std::vector<std::string> strings; // result
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) { // while can find delimiters
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start)); // get a substr and add to the result
    }

    return strings;
}

// get a string from the stream
void readString(std::istream &stream, std::string &string) {
    std::cout << "Input: ";
    getline(stream, string, '\n');
    std::cout << "Your string: " << string << '\n';
}

int main() {
    HashMap<std::string> table(10);
    int action;

    std::ifstream file; // file to read from
    std::string filePath; // path to the file
    std::string string; // input string
    std::vector<std::string> elements; // split input
    std::istream *input = &std::cin; // input stream

    while ((action = getAction(std::cin)) != 6) {

        switch (action) {
            case 1:
                readString(*input, string); // read input
                elements = split(string, ' '); // split input

                for (auto &i : elements) { // count the element
                    std::cout << "Counting element (" << i << ")\n";
                    auto count = table.count(i);
                    std::cout << "Element (" << i << ") contains " << count << " times in the map" << '\n';
                }

                break;
            case 2:
                readString(*input, string); // read string
                elements = split(string, ' '); // split input

                for (auto &i : elements)  { // add elements
                    std::cout << "Working with element (" << i << ")" << '\n';
                    table.add(i);
                    std::cout << "Element (" << i << ") successfully added to the hashmap" << '\n';
                }

                break;
            case 3:
                std::cout << "Path to the file: ";
                std::cin >> filePath; // read the file path
                file.open(filePath); // open file

                if (!file.is_open()) { // check if it opens
                    std::cout << "Couldn't open the file, please try again" << '\n';
                    continue;
                }

                input = &file; // change stream
                break;
            case 4:
                if (file.is_open()) // close file if it was open
                    file.close();

                input = &std::cin; // change stream
                break;
            case 5:
                readString(*input, string); // read input
                elements = split(string, ' '); // split string

                for (auto &i : elements) { // delete the element
                    std::cout << "Working with element (" << i << ")" << '\n';
                    table.remove(i);
                }
                break;
            case 6:
            default:
                std::cout << "Exiting the program" << '\n';
                return 0;
        }

        std::cout << '\n' << "The table is: " << '\n';
        std::cout << table << '\n'; // output table with operator
    }

    return 0;
}