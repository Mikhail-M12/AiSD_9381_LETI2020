#ifndef MYVIEW_H
#define MYVIEW_H
#include "QGraphicsScene"
#include "QGraphicsView"
#include "tree.h"
#include <cmath>
#include <QGraphicsTextItem>

class MyView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget* parent = nullptr);
    void updateGraphics(Node* tree, int maxdepth);
    QGraphicsScene* scene;
private:
    void drawNode(Node* node, int maxdepth, int depth = 0, int x = 0, int y = 0);

    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;
};

#endif // MYVIEW_H
