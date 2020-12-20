#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H
#include "structs.h"
#define START 1
#define END 0

string cuinput(int argc, char** argv);

void proceedOutput(string output, int indent);

void proceedErr(const string& err, int& pos);

void info(int indent, int flag);



#endif