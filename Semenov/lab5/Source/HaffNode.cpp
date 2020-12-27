#include "HaffNode.h"

#include <iostream>

HaffNode::HaffNode(char* symbol, string wayCode): left(nullptr), right(nullptr), symbol(symbol), wayCode(wayCode){
    if (symbol){
        if (*symbol == '\0') weight = 0;
        else weight = 1;
    } else weight = 0;
}

HaffNode::~HaffNode(){
    if (this->left) delete this->left;
    if (this->right) delete this->right;
}

HaffNode* HaffNode::extend(char *newSymbol){
    if (!this->symbol || *this->symbol != '\0') return nullptr;
    this->left = new HaffNode(this->symbol, this->wayCode + "0");
    this->right = new HaffNode(newSymbol, this->wayCode + "1");
    this->symbol = nullptr;
    return this->left;
}

void HaffNode::recount(string wayCode){
    this->wayCode = wayCode;
    if (this->symbol) return;
    this->weight = 0;

    if (this->left){
        this->left->recount(this->wayCode + "0");
        this->weight += this->left->weight;
    }

    if (this->right){
        this->right->recount(this->wayCode + "1");
        this->weight += this->right->weight;
    }
}

HaffNode* HaffNode::findChar(char character){
    if (symbol && character == *symbol) return this;
    
    if (this->left){
        HaffNode *resLeft = this->left->findChar(character);
        if (resLeft) return resLeft;
    }

    if (this->right) return this->right->findChar(character);
    return nullptr;
}

HaffNode& HaffNode::operator ++ (int){
    this->weight += 1;
    return *this;
}

bool operator > (const HaffNode& obj1, const HaffNode& obj2){
    return obj1.getWeight() > obj2.getWeight();
}

bool operator < (const HaffNode& obj1, const HaffNode& obj2){
    return obj1.getWeight() < obj2.getWeight();
}

unsigned int HaffNode::getWeight() const{
    return this->weight;
}

HaffNode* HaffNode::getLeft(){
    return this->left;
}

HaffNode* HaffNode::getRight(){
    return this->right;
}

string HaffNode::getCode(){
    return this->wayCode;
}

void swapNode(HaffNode *node_1, HaffNode *node_2){
    std::swap(node_1->weight, node_2->weight);
    std::swap(node_1->left, node_2->left);
    std::swap(node_1->right, node_2->right);
    std::swap(node_1->symbol, node_2->symbol);
    std::swap(node_1->wayCode, node_2->wayCode);
}

HaffNode *paveWay(HaffNode *curElem, string code){
    if (!curElem) curElem = new HaffNode;
    int len = code.length();
    for (int i = 0; i < len; i++){
        switch (code[i]) {
            case '0':
                if (!curElem->left) curElem->left = new HaffNode(nullptr, curElem->wayCode + "0");
                curElem = curElem->left;
                break;

            case '1':
                if (!curElem->right) curElem->right = new HaffNode(nullptr, curElem->wayCode + "1");
                curElem = curElem->right;
                break;
            default:
                throw invalid_argument(string("Закодированное сообщение имеет неверный формат: встретилось: '") + code[i] + string("'\n"));
        }
    }
    return curElem;
}

HaffNode *paveWay(HaffNode *curElem, char code){
    if (!curElem) curElem = new HaffNode;
    
    switch (code) {
        case '0':
            if (!curElem->left) curElem->left = new HaffNode(nullptr, curElem->wayCode + "0");
            curElem = curElem->left;
            break;

        case '1':
            if (!curElem->right) curElem->right = new HaffNode(nullptr, curElem->wayCode + "1");
            curElem = curElem->right;
            break;
        default:
            throw invalid_argument(string("Ошибка кодировщика: Закодированное сообщение имеет неверный формат: встретилось: '") + code + string("'\n"));
    }

    return curElem;
}