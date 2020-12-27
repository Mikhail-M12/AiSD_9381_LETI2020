#include "HaffCoder.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

HaffCoder::HaffCoder(char *alphabet, InterData& interdata): alphabet(alphabet), interdata(interdata){
    getCodes();
    interdata << "Алфавит и сгенерированные специальные кода каждого символа:\n";
    for (int i = 0; i < strlen(alphabet); i++) interdata << alphabet[i] << " - " << codes[i] << "\n\n";
    root = new HaffNode(&nulc);
    emptyElem = root;
}

HaffCoder::~HaffCoder(){
    delete root;
    delete codes;
}

void HaffCoder::getCodes(){
	size_t count = strlen(alphabet);
    int k = count;
    int p = 0;
    int accum = 1;
    while (k != 1){
        k = k / 2;
        p++;
        accum *= 2;
    }
    int q = count - accum;
    
    codes = new string[count];
	char *bitstr = new char[p+2];
	for (int i = 1; i <= count; i++){
		if (i >= 1 && i <= 2*q){
            itoa(i - 1, bitstr, 2);
            codes[i - 1] = string(bitstr);
            while (codes[i - 1].length() != p + 1) codes[i - 1] = "0" + codes[i - 1];
        } else {
            itoa(i - q - 1, bitstr, 2);
            codes[i - 1] = string(bitstr);
            while (codes[i - 1].length() != p) codes[i - 1] = "0" + codes[i - 1];
        }
	}
    delete bitstr;
}

void HaffCoder::checkTree(){
    root->recount();
    interdata << "с пересчитанными весами:\n";
    interdata.drowTree(root);
    vector<HaffNode*> nodeSequence;
    queue<HaffNode*> nodeQueue;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
        nodeSequence.push_back(nodeQueue.front());
        nodeQueue.pop();
        if (nodeSequence.back()->getRight()) nodeQueue.push(nodeSequence.back()->getRight());
        if (nodeSequence.back()->getLeft()) nodeQueue.push(nodeSequence.back()->getLeft());
    }

    HaffNode* branch_1;
    HaffNode* branch_2;
    
    for (int i = nodeSequence.size() - 1; i > 0; i--){
        if (*(nodeSequence[i]) > *(nodeSequence[i - 1])){
            branch_1 = nodeSequence[i];
            int j = i - 1;
            while(*(nodeSequence[j]) < *branch_1) j--;
            branch_2 = nodeSequence[j + 1];

            interdata << "\nТребуется перевесить ветки:\n";
            interdata.drowTree(branch_1);
            interdata << "\nи\n\n";
            interdata.drowTree(branch_2);

            swapNode(branch_1, branch_2);
            nodeSequence.clear();

            interdata << "\nПовторный пересчет всех весов и перевешивание дерева в случае необходимости:\n";
            interdata << "Дерево с перевешанными ветками и ";
            checkTree();
            break;
        }
    }
}

string HaffCoder::encode(char character){
    interdata << "---------------------------------\n";
    interdata << "На вход кодировщику поступает символ '" << character << "'\n";
    char *charPtr = strchr(alphabet, character);
    if (!charPtr) throw invalid_argument(string("Ошибка кодировщика: Символ: '") + character + string("' не распознан кодировщиком (не принадлежит его алфавиту)\n"));
    
    interdata << "Текущее дерево кодировщика:\n";
    interdata.drowTree(root);
    string result;
    HaffNode *curElem = root->findChar(character);
    
    if (curElem){
        result = ((*curElem)++).getCode();
        interdata << "\nСимвол '" << character << "' уже встречался в кодируемом сообщении и присутствует в дереве => ";
        interdata << "вес узла с этим символом в дереве учеличивается на 1:\n";
        interdata.drowTree(root);
        interdata << "\nКод символа '" << character << "', собранный по пути к узлу дерева: " << result << "\n";
    } else {
        interdata << "\nСимвол '" << character << "' еще не встречался в кодируемом сообщении =>\n";
        interdata << "1) Берется код пустого символа: " << emptyElem->getCode() << "\n";
        interdata << "2) К нему добавляется спец-код символа '" << character << "' из алфавита: " << codes[charPtr - alphabet] << "\n";
        result = emptyElem->getCode() + codes[charPtr - alphabet];
        emptyElem = emptyElem->extend(charPtr);
        interdata << "3) К узлу с пустым символом добавляются два новых узла:\n";
        interdata << "Левый сын - новый пустой узел, а правый - узел с новым добавленным символом: '" << character << "':\n";
        interdata.drowTree(root);
    }
    interdata << "\nПроизводится пересчет всех весов и перевешивание дерева в случае необходимости:\n";
    interdata << "Дерево ";
    checkTree();

    interdata << "\nРезультат кодирования символа '" << character << "' - " << result << "\n";
    interdata << "---------------------------------\n";
    return result;
}

string HaffCoder::decode(string bitMessage){
    string result;

    HaffNode *specTree = new HaffNode;
    int len = strlen(alphabet);
    for (int i = 0; i < len; i++) paveWay(specTree, codes[i])->symbol = alphabet + i;
    
    len = bitMessage.length();
    HaffNode *curElem;
    int i = 0;
    while (i < len) {
        curElem = root;
        while (!curElem->symbol){
            if (i >= len) throw invalid_argument("Ошибка кодировщика: Закодированное сообщение имеет неверный формат: не хватает бит для полного декодирования\n");
            curElem = paveWay(curElem, bitMessage[i]);
            i++;
        }
        
        if (*curElem->symbol == '\0'){
            curElem = specTree;
            while (!curElem->symbol){
                if (i >= len) throw invalid_argument("Ошибка кодировщика: Закодированное сообщение имеет неверный формат: не хватает бит для полного декодирования\n");
                curElem = paveWay(curElem, bitMessage[i]);
                i++;
            }
            emptyElem = emptyElem->extend(curElem->symbol);
        } else (*curElem)++;
        
        result.push_back(*curElem->symbol);
        checkTree();
    }

    return result;
}