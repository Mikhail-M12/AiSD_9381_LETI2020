#ifndef INOUT_H
#define INOUT_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>

using namespace std;

class INOut
{
public:
    INOut();
    int makeArr(std::vector<int>& arr, string res);
    int makeArrFile(std::vector<int>& arr, string filename);
private:
    int getNum(string& input);
    void skip (string& str, int n = 1);
};

#endif // INOUT_H
