#ifndef AISD_LB2_LISP_H
#define AISD_LB2_LISP_H

#include "InOut.h"

enum Type {
    PLUS,
    MINUS,
    MULTIPLY,
    SQRT,
    LOG
};

struct Expression;

struct Node{
    bool isNumber;
    union {
        int number;
        Expression* expression;
    } data;
};

struct two_ptr{
    Node* hd;
    two_ptr* tl;
};

struct Expression{
    Type expressionType;
    two_ptr* pair;
};


Expression* scanExpression(string& input, int& pos, int indent);
Node* scanNode(string& input, int& pos, int indent);
two_ptr* scanTail(string& input, int& pos, bool isFunc, int indent);
void skip (string& str, int& pos, int n = 1, int indent = 0);
int getNum(string& input, int& pos, int indent);
int length(two_ptr* list);

void logCheck(two_ptr* list, int& pos);
void sqrtCheck(two_ptr* list, int& pos);

void destroy(Expression*& lisp);
void destroy(Node*& lisp);
void destroy(two_ptr*& lisp);

#endif //AISD_LB2_LISP_H
