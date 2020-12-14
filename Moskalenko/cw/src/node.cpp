#include "node.h"

BinTree::BinTree(){
    head = nullptr;
}

int BinTree::find(Node* p, int k) // поиск ключа k в дереве p
{
    if(!p)
        return false; // в пустом дереве можно не искать
    if( k == p->key ) {
        cout << "\n\033[31m  Найден узел с совпадающим значением!\033[0m\n";
        return p->amount;      //если нашли, возвращаем поле amount - количество вхождений
    }
    if( k < p->key ) { //если меньше, ищем в левом поддереве
        cout << "\nЗначение искомого узла меньше " << p->key << ", переходим к левому поддереву\n";
        return find(p->left, k);
    }
    else {  //если больше, ищем в правом поддерев
        cout << "\nЗначение искомого узла больше " << p->key << ", переходим к правому поддереву\n";
        return find(p->right, k);
    }
}

int BinTree::getSize(Node* p) // возвращает размер дерева
{
    return (p)? p->size : 0;
}

void BinTree::fixSize(Node* p) // установление корректного размера дерева
{
    p->size = getSize(p->left) + getSize(p->right) + 1;  //размер = размер левого поддерева + правого + 1
}

Node* BinTree::rotateLeft(Node* p) // левый поворот вокруг узла p
{
    if (!p || !p->right)  //если узла нет, или правого поддерева, то поворот не происходит
        return p;

    Node* q = p->right;
    p->right = q->left;
    q->left = p;
    q->size = p->size;
    fixSize(p);
    fixSize(q);
    return q;
}

Node* BinTree::rotateRight(Node* p) // правый поворот вокруг узла p
{
    if (!p || !p->left)   //если узла нет, или левого поддерева, то поворот не происходит
        return p;

    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixSize(p);
    fixSize(q);
    return q;
}

Node* BinTree::insertRoot(Node* p, int k, string* str) // вставка нового узла с ключом k в корень дерева p
{
    if(!p) {
        return new Node(k);
    }

    if( k < p->key )       // если значение k < значения узла, то переходим в левое поддерево
    {
        *str += "\n" + std::to_string(k) + " < "
                + "значения узла " + std::to_string(p->key) + ", поэтому переходим к левому поддереву\n";
        p->left = insertRoot(p->left, k, str);
        *str += "\nОсуществляем правый поворот\n";
        p = rotateRight(p);   //осуществляем правый поворот
        print2DUtil(p, 0, str);
    }

    else if (k > p->key)        // если значение k > значения узла, то переходим в правое поддерево
    {
        *str += "\n" + std::to_string(k) + " > "
                + "значения узла " + std::to_string(p->key) + ", поэтому переходим к правому поддереву\n";
        p->right = insertRoot(p->right,k, str);
        *str += "\nОсуществляем левый поворот\n";
        p = rotateLeft(p);      //осуществляем левый поворот
        print2DUtil(p, 0, str);
    }
    return p;
}

Node* BinTree::insert(Node* p, int k, string* str) // рандомизированная вставка нового узла с ключом k в дерево p
{
    if(!p){
        return new Node(k);  //если корня дерева не существует, то создаем его в конструкторе со значением k
    }

    if(k == p->key){//если узел с таким значением уже есть в дереве, увеличиваем значение поля amount
        *str += "\nЕще одна попытка вставить узел со значением " + std::to_string(k) + "\n";
        p->amount++;
        return p;
    }

   // *str += "\nВероятность элемента " + std::to_string(k) + " оказаться в корне: " + std::to_string(r) + "/" + std::to_string(p->size+1) + "\n";
    if(rand() % (p->size+1) == 0) {  // вставка в корень происходит с вероятностью 1/(n+1),
        // где n - размер дерева до вставки
        *str += "\n Вероятность " + std::to_string(1) + "\\" + std::to_string(p->size+1) +
                ", вставляем узел со значением " + std::to_string(k) + " в корень дерева!\n";
        return
               insertRoot(p, k, str);
    }

    if(p->key > k) {   // иначе происходит обычная вставка в правое или левое поддерево в зависимости от значения k
        *str += "\n" + std::to_string(k) + " < " + "значения узла"
                + std::to_string(p->key) + ", поэтому переходим к левому поддереву\n";
        p->left = insert(p->left, k, str);
    }
    else {
        *str += "\n" + std::to_string(k) + " > " + "значения узла "
                + std::to_string(p->key) + ", поэтому переходим к правому поддереву\n";
         p->right = insert(p->right, k, str);
    }
    fixSize(p); //регулируется размер дерева
    return p;
}

void BinTree::print2DUtil(Node *root, int space, string* str)  //печать лежачего 2D дерева
{
    if (!root)
        return;

    space += COUNT; //счетчик дистанции между уровнями
    print2DUtil(root->right, space, str); //обработка правого поддерева
    *str += "\n";
    for (int i = COUNT; i < space; i++)
        *str += " ";
    *str += std::to_string(root->key) + "\n"; //печать значения узла
    print2DUtil(root->left, space, str); //обработка левого поддерева
}


int BinTree::maxDepth(Node *p){
    if (!p)
        return 0;
    else{
        int lDepth = maxDepth(p->left);
        int rDepth = maxDepth(p->right);
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

Node* BinTree::join(Node* p, Node* q) // объединение двух деревьев
{
    if (!p) return q;
    if (!q) return p;
    if( rand()%(p->size+q->size) < p->size )
    {
        p->right = join(p->right,q);
        fixSize(p);
        return p;
    }
    else
    {
        q->left = join(p,q->left);
        fixSize(q);
        return q;
    }
}

Node* BinTree::remove(Node* p, int k, string* str) // удаление из дерева p первого найденного узла с ключом k
{
    if(!p)
        return p;
    if( p->key == k )
    {
        *str += "Элемент " + std::to_string(k) + " удален\n";
        Node* q = join(p->left, p->right);
        delete p;
        return q;
    }
    else if( k < p->key ){
        *str += std::to_string(k) + " < " + "значения узла "
                + std::to_string(p->key) + ", поэтому переходим к левому поддереву\n";
        p->left = remove(p->left,k, str);
    }
    else{
        *str += "\n" + std::to_string(k) + " > " + "значения узла "
                + std::to_string(p->key) + ", поэтому переходим к правому поддереву\n";
        p->right = remove(p->right, k, str);
    }
    return p;
}

BinTree::~BinTree(){
    destroy(head);
}

void BinTree::destroy(Node* p)   //удаление дерева
{
    if(!p)
        return;
    destroy(p->left);
    destroy(p->right);
    delete p;
}
