#include "gol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gol w;

    w.set_window_parameters(100,100);
    w.seed_grid();

    w.show();
    return a.exec();
}
