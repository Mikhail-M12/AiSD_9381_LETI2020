#include "IntermediaData.h"

#include "HaffCoder.h"

#include <string>
#include <Windows.h>

InterData::InterData(ofstream *fout): fout(fout){}

void InterData::drowTree(HaffNode *root){
    vector<HaffNode*> nodeSequence;
    int height = LKRdetour(root, nodeSequence);

    for (int i = 1; i <= height; i++) {
        for (int j = 0; j < nodeSequence.size(); j++){
            bool isWrite = (i == nodeSequence[j]->getCode().length() - root->getCode().length() + 1); //SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 0));
            specPrint(*this, '(', isWrite);
            specPrint(*this, to_string(nodeSequence[j]->getWeight()), isWrite);
            if (nodeSequence[j]->symbol) {
                specPrint(*this, '[', isWrite);
                if (*nodeSequence[j]->symbol == '\0') specPrint(*this, "\\0", isWrite);
                else specPrint(*this, *nodeSequence[j]->symbol, isWrite);
                specPrint(*this, ']', isWrite);
            }
            specPrint(*this, ')', isWrite);
        }
        *this << "\n";
    }
}

unsigned int LKRdetour(HaffNode *curElem, vector<HaffNode*>& nodeSequence){
    if (!curElem) return 0;
    int H1 = LKRdetour(curElem->getLeft(), nodeSequence);
    nodeSequence.push_back(curElem);
    int H2 = LKRdetour(curElem->getRight(), nodeSequence);
    return (H1 > H2 ? H1 : H2) + 1;
}

void specPrint(InterData& interdata, string str, bool isWrite){
    if (isWrite) interdata << str;
    else {
        int len = str.length();
        for (int i = 0; i < len; i++) interdata << ' ';
    }
}

void specPrint(InterData& interdata, char c, bool isWrite){
    if (isWrite) interdata << c;
    else interdata << ' ';
}