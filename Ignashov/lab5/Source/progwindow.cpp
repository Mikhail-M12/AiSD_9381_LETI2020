#include "progwindow.h"

enum typeOfError{//Перечисление с типами ошибки
    WRONGINPUT,
    NOTREE,
    NOINPUT,
    BIGAMOUNT
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
    }
}

ProgWindow::ProgWindow()
{
    //Выделение памяти под объекты
    numOfLE=new QLineEdit();
    loa=new LineOfAmounts;
    whichElem=new QLineEdit;
    findElemButton=new QPushButton("Find and Add");
    howManyElems=new QLabel("Amount:  ");
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
    layh2->addWidget(whichElem);
    layh2->addWidget(findElemButton);
    layh2->addWidget(howManyElems);

    QVBoxLayout* layv=new QVBoxLayout;
    layv->addLayout(layh);
    layv->addWidget(loa);
    layv->addLayout(layh2);

    QWidget* leftThing=new QWidget;
    leftThing->setLayout(layv);
    leftThing->setFixedWidth(275);

    QHBoxLayout* layh3=new QHBoxLayout;
    layh3->addWidget(leftThing);
    layh3->addWidget(view);

    //Добавление связи между сигналами и слотами

    connect(calc,SIGNAL(clicked()),this,SLOT(createTree()));
    connect(findElemButton,SIGNAL(clicked()),this,SLOT(findElem()));
    connect(numOfLE,SIGNAL(textChanged(const QString &)),this,SLOT(addArray()));

    this->setLayout(layh3);
}

void ProgWindow::createTree()
{
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
}

void ProgWindow::findElem()
{
    int e;
    int count=0;
    if(whichElem->text()=="")
        return;
    if(head==nullptr){//Проврека на ошибку отсутствия дерева
        error(NOTREE);
        return;
    }
    if(whichElem->text()=="0"){
        e=0;
    }else
        if(!(e=whichElem->text().toInt())){//Проверка на ошибку неверного ввода
            error(WRONGINPUT);
            return;
        }
    head->findElem(e,&count);//Поиск элемента
    howManyElems->setText("Amount: "+QString::number(count));
    head->addnew(e,numOfLEi);
    amounts[numOfLEi]=e;
    loa->arr[numOfLEi]->setVisible(true);
    loa->arr[numOfLEi]->setText(whichElem->text());
    numOfLEi+=1;
    createTree();
}

void ProgWindow::addArray()
{
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
        if(numOfLEi>=100){//Проверка на ошибку большого количества элементов
            error(BIGAMOUNT);
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
    if(k<n){
        for(int i=k;i<n;i++){
            arr[i]->setVisible(false);
        }
    }else{
        for(int i=n;i<k;i++){
            arr[i]->setVisible(true);

        }
    }
    this->n=k;
}

LineOfAmounts::~LineOfAmounts()
{
    for(int i=0;i<maxn;i++){
        delete arr[i];
    }
}
