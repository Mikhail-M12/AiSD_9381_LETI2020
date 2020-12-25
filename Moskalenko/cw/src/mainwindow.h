#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "node.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_printTree_clicked();

    void on_deleteElement_clicked();

    void on_newTree_clicked();

    void on_openFile_clicked();

private:
    BinTree* tree;
    vector<int> checkStr();
    int check();
    Node* fillBdp(vector<int> arr);
    Node* fillMas(BinTree* tree, string name, int count);
    Node* fillBdpFile(BinTree* tree, string name);
    QGraphicsScene* scene;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
