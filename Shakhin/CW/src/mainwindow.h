#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "tree.h"
#include "inout.h"
#include "myview.h"
#include <vector>

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
    void on_open_clicked();

    void on_ok_clicked();

    void on_delete_2_clicked();

    void on_add_clicked();

    void on_find_clicked();

private:
    Ui::MainWindow *ui;
    MyView* view;
    INOut* scan;
    BinaryTree* tree;
};
#endif // MAINWINDOW_H
