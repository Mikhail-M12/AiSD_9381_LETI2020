#ifndef AISD_LB2_INOUT_H
#define AISD_LB2_INOUT_H

#include "structs.h"
extern bool errorFlag;
extern int errorPos;

string cuinput(int argc, char** argv);

void proceedOutput(string output, int indent);

void proceedErr(const string& err, int& pos);

void info(int indent, int flag);

#endif //AISD_LB2_INOUT_H
