#include "lisp.h"

void skip(string& str, int& pos, int n, int indent){
    if (str.length() >= n) {

        proceedOutput(str.substr(0, n), indent);

        str = str.substr(n);
        pos++;
    }
}

Expression* scanExpression(string& input, int& pos, int indent){

    info(indent, 1);

    if(input.empty()) return nullptr;
    bool isFunc = input[0] != '(';
    Expression* expression = new Expression;
    if(isFunc){
        if(input.find("log") == 0){
            expression->expressionType = LOG;
            skip(input, pos, 3, indent);
        }
        else if(input.find("sqrt") == 0){
            expression->expressionType = SQRT;
            skip(input, pos, 4, indent);
        }
        else {
            proceedErr("Unknown operator", pos);
        }
        if(input.empty() || input[0] != '('){
            proceedErr("Expected (", pos);
        }
        skip(input, pos, 1, indent);
        expression->pair = scanTail(input, pos, true, indent+1); // составляем список из оставшеяся строки
        if(expression->pair == nullptr){
            proceedErr("Function arguments mot found", pos);
        }
        if(expression->expressionType == LOG){
            logCheck(expression->pair, pos); // проверяем корректонсть аогументов логорифма
        }
        if(expression->expressionType == SQRT){
            sqrtCheck(expression->pair, pos); // проверяем коректность аогументов sqrt
        }
        if(input.empty() || input[0] != ')'){ // проверяем закртую скобку после аргументов логорифма
            proceedErr("Expected )", pos);
        }
        skip(input, pos, 1, indent);// убираем пробел
    }
    else{
        skip(input, pos, 1, indent); // удаляем (
        if(input.find('+') == 0){
            expression->expressionType = PLUS;
            skip(input, pos, 1, indent); // удаляем +
        } else if(input.find('-') == 0){
            expression->expressionType = MINUS;
            skip(input, pos, 1, indent); // удаляем -
        } else if(input.find('*') == 0){
            expression->expressionType = MULTIPLY;
            skip(input, pos, 1, indent); // удаляем *
        } else{
            proceedErr("Unknown operator", pos);
        }
        if (input.empty() || input[0] != ' '){
            proceedErr("Arguments not found", pos);
        }
        skip(input, pos, 1, indent); // удаляем пробел
        expression->pair = scanTail(input, pos, false, indent + 1);
        if(expression->pair == nullptr){
            proceedErr("Arguments not found", pos);
        }
        if (input.empty() || input[0] != ')')
            proceedErr("Expression close bracket not found", pos);
        skip(input, pos, 1, indent);// удаляем )
    }

    info(indent, 2);

    return expression;
}

two_ptr* scanTail(string& input, int& pos, bool isFunc, int indent){

    info(indent, 5);

    two_ptr* list = new two_ptr;
    list->hd = scanNode(input, pos, indent+1);
    if(list->hd == nullptr){ // если не записалась голова списка, то отчищаем память и позвращаем nullprt
        delete list;

        info(indent, 6);

        return nullptr;
    }
    char sep = isFunc ? ',' : ' ';
    if(!input.empty() && input[0] == sep){
        skip(input, pos, 1, indent);
        list->tl = scanTail(input, pos, isFunc, indent+1);
    } else{
        list->tl = nullptr;
    }

    info(indent, 6);

    return list;
}

Node* scanNode(string& input, int& pos, int indent){

    info(indent, 3);

    if (input.empty() || input[0] == ')') {

        info(indent, 4);

        return nullptr;
    }
    Node* node  = new Node;
    node->isNumber = isdigit(input[0]) || (input.length() > 1 && input[0] == '-' && isdigit(input[1]));
    if(node->isNumber){
        node->data.number = getNum(input, pos, indent);
    } else{
        node->data.expression = scanExpression(input, pos, indent+1);
    }

    info(indent, 4);

    return  node;
}

// преобразование строки в число
int getNum(string& str, int& pos, int indent){
    string strNum;
    while (isdigit(str[0]) || (strNum.length() == 0 && str[0] == '-')) {
        strNum += str[0];
        skip(str, pos, 1, indent);
    }
    return stoi(strNum);
}

// подсчёт количества атомов в списке
int length(two_ptr* list){
    two_ptr* l2 = list;
    if(l2 != nullptr && l2->hd != nullptr){
        int len = 0;
        while (l2 != nullptr){
            len++;
            l2 = l2->tl;
        }
        return len;
    } else return 0;
}

//Проверка аргументов логорифма
void logCheck(two_ptr* list, int& pos){
    if(length(list) == 2){ // если список состоит из двух атомов
        if(list->tl->hd->isNumber && (list->tl->hd->data.number == 1 || list->tl->hd->data.number < 0)){
            proceedErr("Log base can't be negative or equals 1", pos);
        }
        if(list->hd->isNumber && (list->hd->data.number < 0)){
            proceedErr("Log argument can't be negative", pos);
        }
    }else{
        proceedErr("Log must have 2 arguments", pos);
    }
}

// проверка аргумента корня
void sqrtCheck(two_ptr* list, int& pos){
    if(length(list) == 1){ // Если в списке один атом
        if (list->hd->isNumber && list->hd->data.number < 0) {
            proceedErr("Sqrt from negative number", pos);
        }
    }
    else {
        proceedErr("Sqrt must have 1 argument", pos);
    }
}

void destroy(Expression*& lisp){
    if(lisp != nullptr){
        destroy(lisp->pair);
        delete lisp;
    }
}

void destroy(Node*& lisp){
    if(lisp != nullptr){
        if(!lisp->isNumber){
            destroy(lisp->data.expression->pair);
            delete lisp;
        }
    }
}

void destroy(two_ptr*& lisp){
    if(lisp != nullptr){
        destroy(lisp->hd);
        destroy(lisp->tl);
        delete lisp;
    }
}