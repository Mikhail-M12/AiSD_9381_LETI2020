#include "node.h"
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
void Node::findElem(int elem, int* count){
    //Последовательный обход и +1 к count если совпадают
     if(elem==this->a)
        *count+=1;

     if(this->left!=nullptr)
        left->findElem(elem,count);
     if(this->right!=nullptr)
        right->findElem(elem,count);
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
    if(left!=nullptr)
        left->deleteTree();
    if(right!=nullptr)
        right->deleteTree();
    delete this;
}
