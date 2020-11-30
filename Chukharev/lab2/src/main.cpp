#include <iostream>
#include <fstream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

struct List;

typedef List* ListP;

struct Pair {
    ListP head;
    ListP tail;
};

struct List {
    bool atom;

    union {
        char atom;
        Pair pair;
    } Node;
};

bool readExp(char prev, ListP& list, std::istream& stream); // Recursion reading (builds atoms)
void output(ListP list); // Recursion output

bool isAtom(ListP list) { // Check if an element is an atom
    if (!list)
        return false;

    return list->atom;
}

ListP getHead(ListP list) { // Returns the head of the element
    if (!list || isAtom(list))
        return nullptr;

    return list->Node.pair.head;
}

bool isNull(ListP list) { // Check if an element is null
    return list == nullptr;
}

ListP getTail(ListP list) { // Returns the tail of the element
    if (!list || isAtom(list))
        return nullptr;

    return list->Node.pair.tail;
}

ListP addNode(ListP head, ListP tail) { // Builds a node to the list from a head and a tail
    if (isAtom(tail))
        return nullptr;

    auto list = new List; // allocate new node
    list->atom = false;
    list->Node.pair.head = head;
    list->Node.pair.tail = tail;
    return list;
}

ListP makeAtom(char symbol) { // Builds an atom from the character
    auto list = new List;
    list->atom = true;
    list->Node.atom = symbol;
    return list;
}

void readRecursion(ListP& list, std::istream& stream) { // Recursion reading (builds the list)
    char symbol;
    ListP p1, p2; // head and tail

    stream >> symbol;

    if (symbol == ')')
        list = nullptr;
    else {
        readExp(symbol, p1, stream);
        readRecursion(p2, stream);
        list = addNode(p1, p2);
    }
}

bool readExp(char prev, ListP& list, std::istream& stream) { // Recursion reading (builds atoms)
    if (prev == ')')
        return false;
    else if (prev != '(')
        list = makeAtom(prev);
    else
        readRecursion(list, stream);
    return true;
}

bool readList(ListP &list, std::istream& stream) { // Start of the recursion
    char symbol;

    do {
        stream >> symbol;
    } while (symbol == ' ');

    return readExp(symbol, list, stream);
}

void outputRecursion(ListP list) { // Recursion output
    if (isNull(list))
        return;

    output(getHead(list));
    outputRecursion(getTail(list));
}

void output(ListP list) { // Recursion output
    if (isNull(list)) // Empty list is ()
        std::cout << "()";

    else if (isAtom(list))
        std::cout << list->Node.atom;
    else {
        std::cout << '(';
        outputRecursion(list);
        std::cout << ')';
    }
}

void freeMemory(ListP list) {
    if (!list)
        return;

    if (!isAtom(list)) {
        freeMemory(getHead(list));
        freeMemory(getTail(list));
    }

    delete list;
}

void printSymbol(int amount, char symbol) {
    for (auto i = 0; i < amount; i++)
        std::cout << symbol;
}

bool isMatch(ListP left, ListP right) {
    static auto space = 0;

    if ((isNull(left) && !isNull(right)) ||
        (!isNull(left) && isNull(right))) {// if one of them is null and the second not then they don't have the same structure
        printSymbol(space, ' ');
        space--;
        std::cout << "One node is null and the other not" << '\n';
        return false;
    }

    if (isAtom(left) != isAtom(right)) { // check for the atom in nodes
        printSymbol(space, ' ');
        space--;
        std::cout << "One is atom and the other is not. Return" << '\n';
        return false;
    }

    if (isNull(left) && isNull(right)) { // if both are checked and no errors occurred then they have the same structure
        printSymbol(space, ' ');
        std::cout << "Probably correct, continue checking nodes" << '\n';
        space--;
        return true;
    }

    printSymbol(space, ' ');
    std::cout << "Keep comparing in recursion" << '\n';
    space++;
    return isMatch(getTail(left), getTail(right)) && isMatch(getHead(left), getHead(right));
}

int getAction() {
    int action = 0;

    std::cout << "Choose one of the following options: " << '\n' <<
              "1. Read from the keyboard" << '\n' <<
              "2. Read from the file" << '\n' <<
              "3. Exit" << '\n' <<
              "Your choice: ";
    std::cin >> action;

    return action;
}

void execProgram() {
    int action;
    ListP listA = nullptr;
    ListP listB = nullptr;
    std::ifstream file;
    std::string fileName;

    while ((action = getAction()) != 3) {
        switch (action) {
            case 1:
                std::cout << "Input the first list: ";
                if (!readList(listA, std::cin)) {
                    std::cout << "Error during reading, please try again" << '\n';
                    return;
                }

                std::cout << "Input the second list: ";
                if (!readList(listB, std::cin)) {
                    std::cout << "Error during reading, please try again" << '\n';
                    return;
                }
                break;
            case 2:
                std::cout << "Input the path to your file: ";
                std::cin >> fileName;
                file.open(fileName);

                if (!file.is_open()) {
                    std::cout << "Wrong file" << '\n';
                    continue;
                }

                readList(listA, file);
                readList(listB, file);
                file.close();
                break;
            default:
                std::cout << "Exiting the program" << '\n';
                freeMemory(listA);
                freeMemory(listB);
                return;
        }

        std::cout << "The first list: ";
        output(listA);
        std::cout << '\n';

        std::cout << "The second list: ";
        output(listB);
        std::cout << '\n' << '\n';

        std::cout << "Start comparing" << '\n';
        std::cout << (isMatch(listA, listB) ? GREEN "The lists match" :
                      RED "The lists don't match") <<
                  RESET << '\n' << '\n';

        freeMemory(listA);
        freeMemory(listB);
    }

    std::cout << "Exiting the program" << '\n';
}

int main() {
    execProgram();
    return 0;
}

