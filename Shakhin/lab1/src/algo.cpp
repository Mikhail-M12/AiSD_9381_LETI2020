#include "algo.h"

void skip(string& str, int& pos, int indent, int n){
    if (str.length() >= n) {
        // Вывод удаляемых символов
        proceedOutput(str.substr(0, n), indent);
        str = str.substr(n);
        pos++;
    }
}

bool findWord(string& str, int& pos, int indent, const char* word){
    int len = strlen(word);
    // Сравнение начала строки с word
    if (!str.compare(0, len, word) && (len == str.length() || (len < str.length() && (!isalnum(str[len]) || !isalnum(word[0]))))){
        skip(str, pos, indent, len);
        return true;
    }
    return false;
}

bool checkLetter(string& str, int& pos, int indent){
    // Проверка, является ли первый символ строки буквой
    if ((str.length() == 1 && isalpha(str[0])) || (str.length() > 1 && isalpha(str[0]) && !isalnum(str[1]))) {
        skip(str, pos, indent);
        return true;
    }
    return false;
}

// AND | OR
bool operation (string& str, int& pos, int indent){
    if (findWord(str, pos, indent, AND_S)) {
        return true;
    }
    else if (findWord(str, pos, indent, OR_S )) {
        return true;
    }
    return false;
}

// OPERAND | OPERAND,OPERANDS
bool operands(std::string& str, int& pos, int indent) {
    if (statement(str, pos, indent + 1)) {
        if (findWord(str, pos, indent, COMMA )) {
            return operands(str, pos, indent);
        }
        return true;
    }
    return false;
}

bool statement (string& str, int& pos, int indent){
    info(indent, START);
    //поиск TRUE
    if (findWord(str, pos, indent, TRUE_S )) {
        info(indent, END);
        return true;
    }
    // поиск FALSE
    else if (findWord(str, pos, indent, FALSE_S )) {
        info(indent, END);
        return true;
    }
    //происк буквы
    else if (checkLetter(str, pos, indent)) {
        info(indent, END);
        return true;
    }
    else if (findWord(str, pos, indent, NOT_S )) {
        if (findWord(str, pos, indent, OPEN_BRACKET )) {
            if (statement(str, pos, indent + 1) && findWord(str, pos, indent, CLOSE_BRACKET )) {
                info(indent, END);
                return true;
            }
            else proceedErr("')' expected", pos);
        }
        else proceedErr("'(' expected", pos);
    }
    else if (operation(str, pos, indent + 1)) {
        if (findWord(str, pos, indent, OPEN_BRACKET )) {
            if (operands(str, pos, indent + 1) && findWord(str, pos, indent, CLOSE_BRACKET )) {
                info(indent, END);
                return true;
            }
            else proceedErr("')' expected", pos);
        }
        else proceedErr("'(' expected", pos);
    }
    proceedErr("Statement expected", pos);
    info(indent, END);
    return false;
}

bool checkString(string& str){
    std::string copy = string(str);
    int position = 0;
    if (statement(copy, position, 1)) {
        if (copy.empty()) {
            return true;
        }
        else proceedErr("End of string expected. \"" + copy, position);
    }
    // Вывод ошибки
    cout << "> " << str << endl << "> ";
    for (int i = 0; i < str.length() - copy.length(); ++i) {
        cout << " ";
    }
    cout << "^" << endl;
    return false;
}