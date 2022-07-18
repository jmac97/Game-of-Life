#include "mainwindow.h"
#include "gol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    gol g;


//    w.setCentralWidget(&g);
    w.show();
    return a.exec();
}
