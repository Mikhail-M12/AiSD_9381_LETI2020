#include <iostream>
#include <fstream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

using namespace std;

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

#define SPACE ' '

ListP getHead(ListP list); // Get a head of the list
ListP getTail(ListP list); // Get a tail of the list
bool isAtom(ListP list); // Check if an element is an atom
char getAtom(ListP list); // Get an atom of the element
bool isNull(ListP list); // Check if an element is null

ListP addNode(ListP head, ListP tail); // Add a node to the list
ListP makeAtom(char symbol); // Make an atom

void readList(ListP &list, std::istream &stream); // Read list
void readExp(char prev, ListP &list, std::istream& stream); // Recursion (builds atoms)
void readRecursion(ListP &list, std::istream& stream); // Recursion reading

void output(ListP list); // Output recursion
void outputRecursion(ListP list); // Output recursion

void printSpace(int amount); // Print spaces (or any character) for recursion
void freeMemory(ListP list); // Free memory of the list

int getAction(); // Output the information and returns input
void execProgram(); // Main while
bool findAtom(ListP list, char atom, bool isIn); // Recursion searching for the atom

bool findAtom(ListP list, char atom, bool isIn) {
    if (isNull(list) || isIn)
        return isIn;

    static int space = 0; // Static counter for the depth of the recursion

    if (isAtom(list)) {
        printSpace(space);
        cout << "The last symbol is: " << getAtom(list) << '\n' <<
                "Check if it's the atom " << atom << '\n';

        if (getAtom(list) == atom) {
            cout << "That's the atom. Ending functions." << '\n';
            return true;
        }

        cout << "That's not the atom. Continue searching" << '\n';
    } else {
        cout << "CHECK_HEAD_TO_ATOM_X function is starting" << '\n';
        space++;
        printSpace(space);
        isIn = findAtom(getHead(list), atom, isIn);
        space--;
        printSpace(space);
        cout << "CHECK_HEAD_TO_ATOM_X function is ending" << '\n';

        cout << "CHECK_TAIL_TO_ATOM_X function is starting" << '\n';
        space++;
        printSpace(space);
        isIn = findAtom(getTail(list), atom, isIn);
        space--;
        printSpace(space);
        cout << "CHECK_TAIL_TO_ATOM_X function is ending" << '\n';
    }

    return isIn;
}

int getAction() {
    int action = 0;

    cout << "Choose one of the following options: " << '\n' <<
         "1. Read from the keyboard" << '\n' <<
         "2. Read from the file" << '\n' <<
         "3. Exit" << '\n' <<
         "Your choice: ";
    cin >> action;

    return action;
}

void execProgram() {
    int action;
    char atom;
    ifstream file;
    ListP list = nullptr;
    string fileName;

    while ((action = getAction()) != 3) {
        switch (action) {
            case 1:
                cout << "Input your list: ";
                readList(list, std::cin);
                break;
            case 2:
                cout << "Input the path to your file: ";
                cin >> fileName;
                file.open(fileName);

                if (!file.is_open()) {
                    cout << "Wrong file" << '\n';
                    continue;
                }

                readList(list, file);
                file.close();
                break;
            default:
                cout << "Exiting the program" << '\n';
                freeMemory(list);
                return;
        }

        cout << "Your list: ";
        output(list);
        cout << '\n' << "Input the Atom: ";
        cin >> atom;

        cout << (findAtom(list, atom, false) ? GREEN "The Atom is in the list" :
                 RED "The Atom is not in the list") <<
             RESET << '\n' << '\n';
        freeMemory(list);
    }

    cout << "Exiting the program" << '\n';
}

int main() {
    execProgram();
    return 0;
}

ListP getHead(ListP list) { // Returns the head of the element
    if (!list || isAtom(list))
        return nullptr;
    return list->Node.pair.head;
}

bool isAtom(ListP list) { // Check if an element is an atom
    if (!list)
        return false;
    return (list->atom);
}

char getAtom(ListP list) { // Returns atom
    if (isAtom(list))
        return list->Node.atom;
    else return '\0';
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

    auto list = new List;
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

void readList(ListP &list, std::istream& stream) { // Start of the recursion
    char symbol;

    do {
        stream >> symbol;
    } while (symbol == ' ');

    readExp(symbol, list, stream);
}

void readExp(char prev, ListP& list, std::istream& stream) { // Recursion reading (builds atoms)
    if (prev != '(')
        list = makeAtom(prev);
    else
        readRecursion(list, stream);
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

void outputRecursion(ListP list) { // Recursion output
    if (isNull(list))
        return;
    output(getHead(list));
    outputRecursion(getTail(list));
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

void printSpace(int amount) {
    for (int i = 0; i < amount; i++)
        std::cout << SPACE;
}
