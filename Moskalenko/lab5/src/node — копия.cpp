#include "node.h"

Node* Node::getLeft(){  //возвращает левое поддерево
    return left;
}

Node* Node::getRight(){  //возвращает правое поддерево
    return left;
}

Node::Node(int key, Node* left, Node* right):key(key),  //конструктор
                                             left(left), right(right){
    this->size = (left ? left->size : 0) + (right ? right->size : 0) + 1;  //размер = размер левого поддерева + правого + 1
    this->amount = 1;    //узел новый. количество = 1
}

int Node::find(Node* p, int k) // поиск ключа k в дереве p
{
    if(!p)
        return false; // в пустом дереве можно не искать
    if( k == p->key )
        return p->amount;  //если нашли, возвращаем поле amount - количество вхождений
    if( k < p->key )   //если меньше, ищем в левом поддереве
        return find(p->left,k);
    else                //если больше, ищем в правом поддереве
        return find(p->right,k);
}

int Node::getSize(Node* p) // возвращает размер дерева
{
    return (p)? p->size : 0;
}

void Node::fixSize(Node* p) // установление корректного размера дерева
{
    p->size = getSize(p->left) + getSize(p->right) + 1;  //размер = размер левого поддерева + правого + 1
}

Node* Node::rotateLeft(Node* p) // левый поворот вокруг узла p
{
    if (!p || !p->right)  //если узла нет, или правого поддерева, то поворот не происходит
        return p;

    Node* q = p->right;
    p->right = q->left;
    q->left = p;
    q->size = p->size;
    fixSize(p);
    return q;
}

Node* Node::rotateRight(Node* p) // правый поворот вокруг узла p
{
    if (!p || !p->left)   //если узла нет, или левого поддерева, то поворот не происходит
        return p;

    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixSize(p);
    return q;
}

Node* Node::insertRoot(Node* p, int k) // вставка нового узла с ключом k в корень дерева p
{
    if(!p) {
        return new Node(k);
    }

    if( k < p->key )       // если значение k < значения узла, то переходим в левое поддерево
    {
        p->left = insertRoot(p->left,k);
        p = rotateRight(p);   //осуществляем правый поворот
    }

    else if (k > p->key)        // если значение k > значения узла, то переходим в правое поддерево
    {
        p->right = insertRoot(p->right,k);
        p = rotateLeft(p);      //осуществляем левый поворот
    }
    return p;
}

Node* Node::insert(Node* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
    if(!p){
        return new Node(k);  //если корня дерева не существует, то создаем его в конструкторе со значением k
    }

    if(k == p->key){       //если узел с таким значением уже есть в дереве, увеличиваем значение поля amount
        p->amount++;
        return p;
    }

    if(rand() % (p->size+1) == 0) {  // вставка в корень происходит с вероятностью 1/(n+1),
        // где n - размер дерева до вставки
        return insertRoot(p, k);
    }

    if(p->key > k)   // иначе происходит обычная вставка в правое или левое поддерево в зависимости от значения k
        p->left  =  insert(p->left, k);
    else
        p->right  = insert(p->right,k);
    fixSize(p); //регулируется размер дерева
    return p;
}

void Node::recTreePrint(Node* p) {   //печать дерева в обходе КЛП
    if (!p) {
        cout << "/ ";
        return;
    }
    cout << p->key << ' ';
    recTreePrint(p->left); //печать левого
    recTreePrint(p->right);     //печать правого
}