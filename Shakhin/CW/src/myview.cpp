#include "myview.h"

MyView::MyView(QWidget* parent):QGraphicsView (parent)
{
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene = new QGraphicsScene();
    QColor color = QColor(203, 119, 47);
    pen.setColor(color);
    brush.setColor(color);
    font.setFamily("Roboto");
    pen.setWidth(3);

}

void MyView::updateGraphics(Node *tree, int maxdepth){
    scene->clear();
    if(!tree) return;
    drawNode(tree, maxdepth);
    this->setScene(scene);
}
/*Рекурсивная функция для отрисовки дерева*/
void MyView::drawNode(Node* node, int maxdepth, int depth, int x, int y){
    if (node == nullptr) return;
        int offset = pow(2, maxdepth + 3) / pow(2, depth);
        if (node->getLeft()) scene->addLine(x + 32, y + 32, x - offset + 32, y + 64 + 32, pen);
        if (node->getRight()) scene->addLine(x + 32, y + 32, x + offset + 32, y + 64 + 32, pen);
        color.setRgb(203, 119, 47);
        QBrush brush(color);
        QPen pen(color, 3);
        scene->addEllipse(x+8, y+8, 48, 48, pen, brush);
        QGraphicsTextItem *numb = new QGraphicsTextItem();
        numb->setPlainText(QString::number(node->getData()));
        numb->setDefaultTextColor(Qt::black);
        numb->setScale(1.5);
        numb->setPos(x + 14, y + 8);
        scene->addItem(numb);
        drawNode(node->getLeft(), maxdepth, depth + 1, x - offset, y + 64);
        drawNode(node->getRight(), maxdepth, depth + 1, x + offset, y + 64);
}
