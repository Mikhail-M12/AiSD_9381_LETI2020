#ifndef PROGWINDOW_H
#define PROGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include "visualizetree.h"

const int maxn=50;

class LineOfAmounts: public QScrollArea{
private:
    int n=0;
public:
    LineOfAmounts();
    QFrame* fr;

    QVBoxLayout* l;
    QLineEdit* arr[maxn];
    void resize(int k);
    ~LineOfAmounts();

    void setN(int x){n=x;}
};

class ProgWindow: public QWidget
{
    Q_OBJECT
private:
    Node* head=nullptr;//Главный элемент дерева
    bool created=false;
    int numOfLEi=0;//Количество строк элементов
    int amounts[maxn];//массив элементов
public:
    ProgWindow();
    //Для графического отображения
    QLineEdit* numOfLE;
    LineOfAmounts* loa = nullptr;
    QPushButton* calc;

    QLineEdit* whichElemAdd;
    QPushButton* findElemAddButton;

    QLineEdit* whichElemDel;
    QPushButton* findElemDelButton;

    QPushButton* instructions;
    QPushButton* clear;

    VisualizeTree* treeScene=nullptr;
    QGraphicsView* view;

public slots:
    void addElem();//Слот поиска элемента
    void addArray();//Слот добавления массива элементов
    void createTree();//Слот создания дерева
    void delElem();//Слот удаления элемента
    void inst();//Слот инструкций
    void startNew();//Слот инструкций
};

#endif // PROGWINDOW_H
