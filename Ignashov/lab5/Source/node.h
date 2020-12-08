#ifndef NODE_H
#define NODE_H


class Node
{
private:
    int a;//Содержание
    int elemNum;//Номер элемента
    Node* left;//Ссылка на левый элемент
    Node* right;//Ссылка на правый элемент
    int depth;//Глубина вхождения в дерево
public:
    Node(int am, int depth, int elemNum);//Конструктор
    void addnew(int x, int num);//Добавление элемента
    int maxdepth();//Поиск максимаьлной глубины
    void findElem(int elem, int* count);//Поиск элемента в массиве
    void deleteTree();//Удалить дерево

    Node* getLeft(){return left;}
    Node* getRight(){return right;}
    int getA(){return a;}
    int getElemNum(){return elemNum;}
    int getDepth(){return depth;}
};

#endif // NODE_H
