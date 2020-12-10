#include "node.h"
#include <iostream>
Node::Node(int am, int depth, int elNum)
{
    elemNum=elNum;
    a=am;
    this->depth=depth;
    left=nullptr;
    right=nullptr;
}


void Node::addnew(int x, int num)
{
    //Последовательный обход в соотвествии с поиском по бдп и добавление в место, где элемент ддолжен быть
    Node* tmp = this;
    while(true){
        if(tmp->a>x){
            if(tmp->left==nullptr){
                tmp->left=new Node(x,tmp->depth+1,num);
                break;
            }
            tmp=tmp->left;
        }
        else{
            if(tmp->right==nullptr){
                tmp->right=new Node(x,tmp->depth+1,num);
                break;
            }
            tmp=tmp->right;
        }
    }
}

int Node::delElem(int x){
    bool onLeft;
    std::cout<<this->a;
    if((left!=nullptr&&left->a==x)||(right!=nullptr&&right->a==x)){//С какой стороны элемент
        if(left!=nullptr&&left->a==x)
            onLeft=true;
        else
            onLeft=false;
    }else{//Если не найден здесь - ищем дальше, или возвращаемся если во всем дереве нет этого элемента(не считая головы)
        if(left!=nullptr&&left->delElem(x)==1)
            return 1;
        if(right!=nullptr&&right->delElem(x)==1)
            return 1;
        return 0;
    }
    if(onLeft==true){//Если слева
        if(left->left==nullptr&&left->right==nullptr){//Если это лист
            delete left;
            left=nullptr;
            return 1;
        }
        if(left->left==nullptr){//Если только справа
            left=left->right;
            return 1;
        }
        if(left->right==nullptr){//Если только справа
            left=left->left;
            return 1;
        }
        Node* tmp=left->right;//Если два элемента есть - ищем минимальный справа
        if(tmp->left==nullptr&&tmp->right==nullptr){//Если сам такой элемент
            left->a=tmp->a;
            left->right->deleteTree();
            left->right=nullptr;
            return 1;
        }
        if(tmp->left==nullptr&&tmp->right!=nullptr){//Если сам такой элемент и справа висит что-то
            left->a=left->right->a;
            left->right=left->right->right;
            return 1;
        }
        while(tmp->left->left!=nullptr){//Переходим к минимальному
            tmp=tmp->left;
        }
        left->a=tmp->left->a;
        if(tmp->left->right!=nullptr){//Если у минимального ничего не висит
            tmp->left=tmp->left->right;
        }else{
            tmp->left->deleteTree();//Если у минимального висит справа
            tmp->left=nullptr;
        }
        return 1;

    }else{//Все аналогично вышеописанному, но если искомый элемент справа
        if(right->left==nullptr&&right->right==nullptr){
            delete right;
            right=nullptr;
            return 1;
        }
        if(right->left==nullptr){
            right=right->right;
            return 1;
        }
        if(right->right==nullptr){
            right=right->left;
            return 1;
        }
        Node* tmp=right->right;
        if(tmp->left==nullptr&&tmp->right==nullptr){
            right->a=tmp->a;
            right->right->deleteTree();
            right->right=nullptr;
            return 1;
        }
        if(tmp->left==nullptr&&tmp->right!=nullptr){
            right->a=right->right->a;
            right->right=right->right->right;
            return 1;
        }
        while(tmp->left->left!=nullptr){
            tmp=tmp->left;
        }
        right->a=tmp->left->a;
        if(tmp->left->right!=nullptr){
            tmp->left=tmp->left->right;
        }else{
            tmp->left->deleteTree();
            tmp->left=nullptr;
        }
        return 1;
    }
    return 0;//Если ничего не подходит - удалять точно нечего
}

void Node::reNumAll(int* n)
{
    this->elemNum=*n;
    *n+=1;
    if(left!=nullptr){
        left->reNumAll(n);
    }
    if(right!=nullptr){
        right->reNumAll(n);
    }
}

void Node::reDepthAll(int n)
{
    this->depth=n;
    if(left!=nullptr){
        left->reDepthAll(n+1);
    }
    if(right!=nullptr){
        right->reDepthAll(n+1);
    }
}

int Node::maxdepth()
{
    //Последовательный обход и сравнение максимальной глубины слева и справа
    int maxdepth_left=0;
    int maxdepth_right=0;
    if(left!=nullptr)
        maxdepth_left=left->maxdepth();
    if(right!=nullptr)
        maxdepth_right=right->maxdepth();
    if(left==nullptr&&right==nullptr)
        return depth;
    else
        return maxdepth_left>maxdepth_right ? maxdepth_left : maxdepth_right;
}

void Node::deleteTree()
{
    //Последовательный обход и удаление
    if(left!=nullptr){
        left->deleteTree();
        left=nullptr;
    }
    if(right!=nullptr){
        right->deleteTree();
        right=nullptr;
    }
    delete this;
}
