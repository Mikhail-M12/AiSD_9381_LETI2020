#ifndef ALGO_H
#define ALGO_H

#include "structs.h"
#include "inputoutput.h"

#define TRUE_S "TRUE"
#define FALSE_S "FALSE"
#define NOT_S "NOT"
#define AND_S "AND"
#define OR_S "OR"
#define OPEN_BRACKET "("
#define CLOSE_BRACKET ")"
#define COMMA ","

bool statement (string& str, int& pos, int indent);

bool operands(string& str, int& pos, int indent);

bool operation (string& str, int& pos, int indent);

bool findWord (string& str, int& pos, int indent, const char* word);

bool checkLetter(string& str, int& pos, int indent);

bool checkString(string& str);

void skip (string& str, int& pos, int indent, int n = 1);
#endif

