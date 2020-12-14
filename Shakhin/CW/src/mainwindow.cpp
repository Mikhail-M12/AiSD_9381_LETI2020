#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scan = new INOut();
    view = new MyView();
    tree = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберете файл", "/home/user", "*.txt");
    if(path == nullptr)
        return;
    std::vector<int> arr;
    if(scan->makeArrFile(arr, path.toLocal8Bit().constData())){
        QMessageBox::critical(this, "Error", "incorect input");
    }else{
        if(tree) delete tree;
        std::string str;
        tree = new BinaryTree(arr, str);
        ui->textBrowser->setText(QString::fromStdString(str));
        view->updateGraphics(tree->getTree(), tree->getMaxDepth());
        ui->gridLayout->addWidget(view);
    }
}

void MainWindow::on_ok_clicked()
{
    if(ui->lineEdit->isModified()){
        QString path = ui->lineEdit->text();
        if(!path.isEmpty()){
            std::vector<int> arr;
            if(scan->makeArr(arr, path.toLocal8Bit().constData())){
                QMessageBox::critical(this, "Error", "incorect input");
            }else{
                if(tree) delete tree;
                std::string str;
                tree = new BinaryTree(arr, str);
                ui->textBrowser->setText(QString::fromStdString(str));
                view->updateGraphics(tree->getTree(), tree->getMaxDepth());
                ui->gridLayout->addWidget(view);
            }
        }
    }

}

void MainWindow::on_delete_2_clicked()
{
    int el = ui->elem->value();
    std::string str;
    tree->deleteElem(el, str);
    ui->textBrowser->setText(QString::fromStdString(str));
    view->updateGraphics(tree->getTree(), tree->getMaxDepth());
}

void MainWindow::on_add_clicked()
{
    int el = ui->elem->value();
    std::string str;
    tree->addElem(el, str);
    ui->textBrowser->setText(QString::fromStdString(str));
    view->updateGraphics(tree->getTree(), tree->getMaxDepth());
}

void MainWindow::on_find_clicked()
{
    int el = ui->elem->value();
    std::string str;
    tree->findElem(el, str);
    ui->textBrowser->setText(QString::fromStdString(str));
    view->updateGraphics(tree->getTree(), tree->getMaxDepth());
}

