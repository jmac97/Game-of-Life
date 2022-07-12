#include "gol.h"
#include "cells.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gol w;

    w.show();


    Subject sub;
    Cell guy1(&sub, 10, 10);
    Cell guy2(&sub, 30, 30);
    Cell guy3(&sub, 50, 50);

    sub.notify();
    return a.exec();
}
