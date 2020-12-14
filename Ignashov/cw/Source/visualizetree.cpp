#include "visualizetree.h"

struct pt{
    int x;//Настоящий х
    int y;//Настоящий у
    int xlast;//Предыдущий х
    int ylast;//Предыдущий y
    int contains;//Содержит
    bool made=false;//Структура собрана/не собрана
};

pt findPlace(Node* tmphead, int elemNum, int leftMove, int rightMove, int widthch, bool toLeft){
    pt retpt;
    if(tmphead->getElemNum()==elemNum){//Если совпадает - инициализируем и возвращаем
        retpt.x=-leftMove+rightMove;
        retpt.y=tmphead->getDepth();
        retpt.ylast=retpt.y-1;
        if(toLeft){
            retpt.xlast=retpt.x+widthch*2;
        }else{
            retpt.xlast=retpt.x-widthch*2;
        }
        retpt.contains=tmphead->getA();
        retpt.made=true;
        return retpt;
    }
    //Ищем пока не совпадет
    if(tmphead->getLeft()!=nullptr){
        retpt=findPlace(tmphead->getLeft(),elemNum,leftMove+widthch,rightMove,widthch/2,true);
        if(retpt.made){//Чтобы в очередной раз не инициализировать после входа в right
            return retpt;
        }
    }
    if(tmphead->getRight()!=nullptr){
        retpt=findPlace(tmphead->getRight(),elemNum,leftMove,rightMove+widthch,widthch/2,false);
        if(retpt.made){
            return retpt;
        }
    }
    return retpt;
}


VisualizeTree::VisualizeTree(int maxn)
{
    //Выделение памяти всех элементов и выключение их для пользователя
    this->maxn=maxn;
    items=new QGraphicsSimpleTextItem*[maxn];
    lineItems=new QGraphicsLineItem*[maxn];
    for(int i=0;i<maxn;i++){
        items[i]=new QGraphicsSimpleTextItem;
        lineItems[i]=new QGraphicsLineItem;
        addItem(items[i]);
        addItem(lineItems[i]);
        items[i]->setVisible(false);
        lineItems[i]->setVisible(false);
    }
}

void VisualizeTree::update(Node* head, int numOfLeaves)
{
    for(int i=0;i<maxn;i++){//очистим сцену
        items[i]->setVisible(false);
        lineItems[i]->setVisible(false);
    }

    for(int i=0;i<numOfLeaves;i++){//Для каждого элемента будем искать его место и значение
        pt pl = findPlace(head,i,0,0,pow(2,(head->maxdepth())),true);
        items[i]->setText(QString::number(pl.contains));
        items[i]->setPos(pl.x*10,pl.y*30);
        if(i!=0){//Если 0 - рисовать линии наверх не надо
            lineItems[i]->setLine(pl.x*10,pl.y*30,pl.xlast*10,pl.ylast*30);
            lineItems[i]->setPen(Qt::DashLine);
            lineItems[i]->setVisible(true);
        }
        items[i]->setVisible(true);//Отображаем необходимые
    }
}

VisualizeTree::~VisualizeTree()
{
    //Очищаем выделенную под массивы память
    for(int i=0;i<maxn;i++){
        delete items[i];
        delete lineItems[i];
    }
    delete[] items;
    delete[] lineItems;
}
