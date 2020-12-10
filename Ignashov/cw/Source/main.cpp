#include <QApplication>

#include "progwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProgWindow* pg = new ProgWindow;
    pg->setWindowTitle("Случайные БДП");
    pg->showMaximized();//Отображение главного окна
    return a.exec();
}
