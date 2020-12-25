#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QValidator>
#include "drawTree.cpp"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->deleteInput->setValidator (new QIntValidator (this));
    tree = new BinTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Node* MainWindow::fillBdp(vector<int> arr){
for(int val : arr) {   //добавляем элементы из вектора в БДП
        string k = "";
        tree->head = tree->insert(tree->head, val, &k);
        k += "\t\tДОБАВЛЕН ЭЛЕМЕНТ " + std::to_string(val) + "\n";
        ui->result->append(QString::fromLocal8Bit(k.c_str()));
        int depth = tree->maxDepth(tree->head);
        scene = graphic(tree->head, scene, depth);
        QEventLoop loop;
        QTimer::singleShot(1700, &loop, SLOT(quit()));
        loop.exec();
    }
      return tree->head;
}

void MainWindow::on_printTree_clicked()
{
     vector<int> arr = checkStr();
     if (!arr.empty()){
         scene->clear();
         tree->head = fillBdp(arr);
     }
     ui->inputTree->clear();
}


vector<int> MainWindow::checkStr(){
     QString data = ui->inputTree->text();
     string str = data.toUtf8().constData();
     istringstream ss(str);
     vector<int>arr;   //вектор введенных чисел
     int x;
     while(ss >> x){
         arr.push_back(x);
         if(ss.peek() == ' ')  //игнорируем пробелы
             ss.ignore();
     }
     if (!ss.eof())   //если были введены символы кроме цифер
     {
         QMessageBox::warning(this,"Error", "Неправильный ввод!");
     }
     return arr;
}


void MainWindow::on_deleteElement_clicked()
{
     if (ui->deleteInput->text().isEmpty())
         return;
     QString data = ui->deleteInput->text();
     string str = data.toUtf8().constData();
     for (auto i: str)
     {
         if (!isdigit(i)){
              QMessageBox::warning(this,"Error", "Неправильный ввод!");
              return;
         }
     }
     int x = std::stoi(str);
     string k = "";
     tree->head = tree->remove(tree->head, x, &k);
     ui->deleteInput->clear();
     int depth = tree->maxDepth(tree->head);
     ui->result->append(QString::fromLocal8Bit(k.c_str()));
     scene = graphic(tree->head, scene, depth-1);
     if (!tree->head)
         scene->clear();
}


void MainWindow::on_newTree_clicked()
{
    scene->clear();
    delete tree;
    tree = new BinTree();
    ui->result->clear();
    ui->result->append(QString::fromLocal8Bit("\tCоздаем новое дерево."));
}


void MainWindow::on_openFile_clicked()
{
    QString str = QFileDialog::getOpenFileName(nullptr, "Выберите файл для открытия", "/home/user", "*.txt");
           if (str == nullptr)
               return;
              tree->head = fillBdpFile(tree, str.toLocal8Bit().constData());
 }


Node* MainWindow::fillMas(BinTree* tree, string name, int count){  // заполнение БДП с файла
    ifstream in(name);  //открываем файл
    if (!in.is_open()) {
        cout << "Файл не может быть открыт!\n";
        return tree->head;
   }
     int x[count];
     vector<int>arr;
    for (int i = 0; i < count - 1; i++){
        in >> x[i];
        arr.push_back(x[i]);
}

    tree->head = fillBdp(arr);
    in.close(); //под конец закроем файла
    return tree->head;
}

Node* MainWindow::fillBdpFile(BinTree* tree, string name){  //подсчет количества чисел в файле
    //Создаем файловый поток и связываем его с файлом
    ifstream in(name);
    if (!in.is_open()) {
        cout << "Файл не может быть открыт!\n";
        return tree->head;
    }
        int count = 0; // количество чисел в файле
        int temp;  //Временная переменная

        while (!in.eof()) // пробегаем пока не встретим конец файла eof
        {
            in >> temp;  //в пустоту считываем из файла числа
            count++; // увеличиваем счетчик количества чисел
        }

        in.close();
        return fillMas(tree, name, count);
}

