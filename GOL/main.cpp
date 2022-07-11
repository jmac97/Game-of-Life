#include "gol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gol w;

    w.show();
    return a.exec();
}
