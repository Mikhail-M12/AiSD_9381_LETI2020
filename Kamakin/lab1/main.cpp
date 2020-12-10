#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static int recursionLevel = 0;

/*
 * Построить синтаксический анализатор для понятия простое выражение.
 *    Простое_выражение:: = простой_идентификатор | (простое_выражение знак_операции простое_выражение)
 *    Простой_идентификатор:: = буква (alpha)
 *    Знак_операции:: = - | + | * (symbol)
 */

void printRecursion(int level) { // Outputs '*' for recursion depth
    for (int i = 0; i < level; i++)
        cout << '*';
}

bool stringAnalyze(string input, int bracketsOpen, int alphaBefore, int symbolBefore) {
    if (input.empty() && bracketsOpen != 0)  { // The string is over but bracket(s) wasn't closed
        printRecursion(recursionLevel);
        cout << "Invalid brackets" << '\n';
        recursionLevel--;
        return false;
    }

    if (input.empty()) { // The string was parsed and brackets closed
        printRecursion(recursionLevel);
        cout << "Done. The string is correct" << '\n';
        recursionLevel--;
        return true;
    }

    if (isalpha(input[0])) { // Case for an alpha
        if ((!bracketsOpen && input.size() > 1) || alphaBefore > 1) {  // No brackets but more than 1 alpha
            printRecursion(recursionLevel);
            cout << "You have more than 1 simple id (an alpha) in a row" << '\n';
            recursionLevel--;
            return false;
        } else if (input.size() == 1 && !bracketsOpen) { // Only one symbol
            printRecursion(recursionLevel);
            cout << "Found only one alpha so it's correct." << '\n';
            recursionLevel--;
            return true;
        }

        alphaBefore++;
        printRecursion(recursionLevel);
        cout << "Found an alpha '" << input[0]  << "' alphaBefore = " << alphaBefore << '\n';
    } else if (input[0] == '(') {
        bracketsOpen++;
        printRecursion(recursionLevel);
        cout << "Found '(' and bracketsOpen = " << bracketsOpen << '\n';
    } else if (input[0] == ')') {
        if (alphaBefore != 1 || symbolBefore < 1) { // (alpha symbol alpha) -> check for alpha and symbol
            printRecursion(recursionLevel);
            cout << "Found ')' but there were no alpha. Wrong brackets, not correct." << '\n';
            recursionLevel--;
            return false;
        }

        bracketsOpen--;
        symbolBefore--;
        printRecursion(recursionLevel);
        cout << "Found ')' , bracketsOpen = " << bracketsOpen << " and alphaBefore = " << alphaBefore << '\n';
    } else if (input[0] == '+' || input[0] == '-' || input[0] == '*')  { // Case for the operations
        symbolBefore++;

        if (bracketsOpen < 1 || alphaBefore < 1 || (symbolBefore >= 2 && bracketsOpen < 2)) { // An operation not in brackets
            printRecursion(recursionLevel);
            cout << "Found a symbol but it's not in brackets, symbolBefore = "  << symbolBefore << '\n';
            recursionLevel--;
            return false;
        }

        alphaBefore--;
        printRecursion(recursionLevel);
        cout << "Found a symbol '" << input[0] << "' bracketsOpen = " << bracketsOpen <<
                    " and symbolBefore = " << symbolBefore << '\n';
    } else {
        printRecursion(recursionLevel);
        cout << "Invalid symbol starting here: " << input << '\n';
        recursionLevel--;
        return false;
    }

    input = input.substr(1, input.size() - 1);
    recursionLevel++;
    return stringAnalyze(input, bracketsOpen, alphaBefore, symbolBefore);
}

int main() {
    string input, fileName;

    bool isFile;

    cout << "Would you like to read from the file? (1/0)?" << '\n';

    cin >> isFile;
    cin.get();

    if (isFile) {
        cout << "Input the full path to the isFile: " << '\n';
        getline(cin, fileName);

        ifstream myFile(fileName);
        if (myFile.fail()) {
            cout << "Couldn't open the file. Try again" << '\n';
            return 0;
        }

        getline(myFile, input);
        cout << "The line from the file: " << input << '\n';
    } else {
        cout << "Input the string: " << '\n';
        getline(cin, input);
    }

    if (!input.empty())
        cout << (stringAnalyze(input, 0, 0, 0) ? "Correct" : "Not correct") << '\n';
    else
        cout << "Something went wrong" << '\n';
    return 0;
}

