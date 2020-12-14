#include "progwindow.h"

enum typeOfError{//Перечисление с типами ошибки
    WRONGINPUT,
    NOTREE,
    NOINPUT,
    BIGAMOUNT,
    WRONGDELETE,
    TREEISCREATED
};

void error(typeOfError type){//Обработка ошибок
    switch(type){
        case WRONGINPUT:
            QMessageBox::warning(nullptr, "Warning!","Wrong input!");
            break;
        case NOTREE:
            QMessageBox::warning(nullptr, "Warning!","No tree found!");
            break;
        case NOINPUT:
            QMessageBox::warning(nullptr, "Warning!","No input found!");
            break;
        case BIGAMOUNT:
            QMessageBox::warning(nullptr, "Warning!","You've inputted too huge amount!");
            break;
        case WRONGDELETE:
            QMessageBox::warning(nullptr, "Warning!","You've tried to delete an unexisting element or the head!");
            break;
        case TREEISCREATED:
            QMessageBox::warning(nullptr, "Warning!","Tree is already created, so use the Clear button!");
            break;
    }
}

ProgWindow::ProgWindow()
{
    //Выделение памяти под объекты
    numOfLE=new QLineEdit();
    loa=new LineOfAmounts;
    whichElemAdd=new QLineEdit;
    findElemAddButton=new QPushButton("Add");
    whichElemDel=new QLineEdit;
    findElemDelButton=new QPushButton("Delete");
    instructions=new QPushButton("Instructions");
    clear=new QPushButton("Clear");
    calc=new QPushButton("Generate");
    treeScene = new VisualizeTree(maxn);
    view=new QGraphicsView;
    view->setScene(treeScene);//Установка сцены с деревом в view
    //Компоновка графического отображения
    QHBoxLayout* layh = new QHBoxLayout;
    QLabel *NumberOf = new QLabel("Number of elements:");

    layh->addWidget(NumberOf);
    layh->addWidget(numOfLE);
    layh->addWidget(calc);

    QHBoxLayout* layh2=new QHBoxLayout;
    layh2->addWidget(whichElemAdd);
    layh2->addWidget(findElemAddButton);

    QHBoxLayout* layh3=new QHBoxLayout;
    layh3->addWidget(whichElemDel);
    layh3->addWidget(findElemDelButton);

    QVBoxLayout* layv=new QVBoxLayout;
    layv->addLayout(layh);
    layv->addWidget(loa);
    layv->addLayout(layh2);
    layv->addLayout(layh3);
    layv->addWidget(clear);
    layv->addWidget(instructions);

    QWidget* leftThing=new QWidget;
    leftThing->setLayout(layv);
    leftThing->setFixedWidth(275);

    QHBoxLayout* layh4=new QHBoxLayout;
    layh4->addWidget(leftThing);
    layh4->addWidget(view);

    //Добавление связи между сигналами и слотами

    connect(calc,SIGNAL(clicked()),this,SLOT(createTree()));
    connect(findElemAddButton,SIGNAL(clicked()),this,SLOT(addElem()));
    connect(findElemDelButton,SIGNAL(clicked()),this,SLOT(delElem()));
    connect(instructions,SIGNAL(clicked()),this,SLOT(inst()));
    connect(clear,SIGNAL(clicked()),this,SLOT(startNew()));
    connect(numOfLE,SIGNAL(textChanged(const QString &)),this,SLOT(addArray()));

    this->setLayout(layh4);
}

void ProgWindow::createTree()
{
    if(created){
        error(TREEISCREATED);
        return;
    }
    if(numOfLEi==0){//Проверка на ошибку отсутствия ввода
        error(NOINPUT);
        if(head!=nullptr)
            head->deleteTree();
        head=nullptr;
        treeScene->update(head,0);
        return;
    }
    for(int i=0;i<numOfLEi;i++){//Проверка но ошибку неверного ввода
        if(!(amounts[i]=loa->arr[i]->text().toInt())&&(loa->arr[i]->text()!="0")){
            error(WRONGINPUT);
            if(head!=nullptr)
                head->deleteTree();
            head=nullptr;
            treeScene->update(head,0);
            return;
        }
    }
    if(head!=nullptr)//Очистка предыдущего дерева
        head->deleteTree();
    head = new Node(amounts[0],0,0);//Добавление нового
    for(int i=1;i<numOfLEi;i++)
        head->addnew(amounts[i],i);
    treeScene->update(head,numOfLEi);
    created=true;
}

void ProgWindow::delElem()
{
    int e;
    if(whichElemDel->text()=="")
        return;
    if(head==nullptr){//Проврека на ошибку отсутствия дерева
        error(NOTREE);
        whichElemDel->setText("");
        return;
    }
    if(whichElemDel->text()=="0"){
        e=0;
    }else{
        if(!(e=whichElemDel->text().toInt())){//Проверка на ошибку неверного ввода
            error(WRONGINPUT);
            whichElemDel->setText("");
            return;
        }
    }
    if(head->delElem(e)==0){//Удаление
        error(WRONGDELETE);//Ошибка несуществующего элемента или удаление главного элемента
        whichElemDel->setText("");
        return;
    }
    int tmpn=0;
    head->reNumAll(&tmpn);//Перерасчет номеров элементов
    head->reDepthAll(0);//Перерасчет глубины
    numOfLEi--;
    treeScene->update(head,numOfLEi);
    whichElemDel->setText("");
}

void ProgWindow::inst()
{
    QMessageBox* instBox=new QMessageBox;
    instBox->setWindowTitle("Instructions");
    instBox->setText("1) В левой верхней строке указывается количество элементов в дереве, после чего ниже появится такое же количество полей для заполнения - сами элементы.\n"
                     "2) Нажатие кнопки генерации приведет к созданию дерева в правой части окна программы.\n"
                     "3) Внизу слева программы присутствует поле ввода добавляемого элемента и кнопка, добавляющая его. Ниже них поле ввода удаляемого элемента и кнопка, удаляющая его.\n"
                     "4) Для полной очистки нажмите на кнопку Clear.");
    instBox->exec();
}

void ProgWindow::startNew()
{
    if(created==false){
        return;
    }
    created=false;
    numOfLEi=0;
    numOfLE->setText("");
    if(head!=nullptr)
        head->deleteTree();
    head=nullptr;
    treeScene->update(head,0);
}

void ProgWindow::addElem()
{
    int e;
    if(whichElemAdd->text()=="")
        return;
    if(head==nullptr){//Проврека на ошибку отсутствия дерева
        error(NOTREE);
        whichElemAdd->setText("");
        return;
    }
    if(whichElemAdd->text()=="0"){
        e=0;
    }else
        if(!(e=whichElemAdd->text().toInt())){//Проверка на ошибку неверного ввода
            error(WRONGINPUT);
            whichElemAdd->setText("");
            return;
        }
    head->addnew(e,numOfLEi);
    numOfLEi+=1;
    treeScene->update(head,numOfLEi);
    whichElemAdd->setText("");
}

void ProgWindow::addArray()
{
    if(head!=nullptr)
        head->deleteTree();
    head=nullptr;
    treeScene->update(head,0);
    for(int i=0;i<maxn;i++){//Делаем невидимыми для пользователя все строки
        loa->arr[i]->setVisible(false);
    }
    if(numOfLE->text()==""){//Если нет количества строк - все пустые
        loa->resize(0);
        for(int i=0;i<maxn;i++)
            loa->arr[i]->setText("");
        numOfLEi=0;
        return;
    }
    if(numOfLEi=numOfLE->text().toInt()){//Проверка на верный ввод
        if(numOfLEi>=maxn){//Проверка на ошибку большого количества элементов
            error(BIGAMOUNT);
            loa->setN(maxn);
            return;
        }
        loa->resize(numOfLEi);
    }else{
        error(WRONGINPUT);
        numOfLE->setText("");
    }
}

LineOfAmounts::LineOfAmounts()
{
    //Выделение памяти и создание графического отображения строк ввода элементов
    fr=new QFrame;
    l = new QVBoxLayout;
    for(int i=0;i<maxn;i++){
        arr[i]=new QLineEdit;
        arr[i]->setVisible(false);
        arr[i]->setFixedHeight(20);
        l->addWidget(arr[i]);
    }
    setWidgetResizable(true);
    l->setAlignment(Qt::AlignTop);
    fr->setLayout(l);

    setWidget(fr);
}

void LineOfAmounts::resize(int k)
{
    //Перерасчет количества отображаемых строк
    for(int i=0;i<maxn;i++){//Делаем невидимыми для пользователя все строки
        arr[i]->setVisible(false);
    }
    for(int i=0;i<k;i++){
        arr[i]->setVisible(true);
    }

    this->n=k;
}

LineOfAmounts::~LineOfAmounts()
{
    for(int i=0;i<maxn;i++){
        delete arr[i];
    }
}
