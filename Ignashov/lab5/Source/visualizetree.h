#ifndef VISUALIZETREE_H
#define VISUALIZETREE_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "node.h"

class VisualizeTree: public QGraphicsScene
{
private:
    int maxn;//Максимальное количество элементов
    QGraphicsSimpleTextItem** items;//Массив элементов
    QGraphicsLineItem** lineItems;//Массив линий между ними
public:
    VisualizeTree(int maxn);
    void update(Node* head, int numOfLeaves);//Обновление картины дерева
    ~VisualizeTree();
};

#endif // VISUALIZETREE_H
