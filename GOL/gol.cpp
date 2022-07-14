#include "gol.h"
#include "./ui_gol.h"
#include <QDebug>

gol::gol(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gol)
{
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, QOverload<>::of(&gol::update));
//    timer->start(1000);
    ui->setupUi(this);
}

gol::~gol()
{
    delete ui;
}

void gol::set_window_parameters(int w, int h) {
    window_width = w;
    window_height = h;
    setFixedSize(window_width, window_height);
}

void gol::seed_grid()
{
    int spacing = 10;
    bool alive = true;

    // blinker
    cells_current.resize(100);  // resize top level vector
    for (int i = 0; i < 100; i++)
    {
        cells_current[i].resize(100);  // resize each of the contained vectors
        for (int j = 0; j < 100; j++)
        {
            cells_current[i][j] = 0;
        }
    }


    cells_current[30][30] = alive;
    cells_current[30][20] = alive;
    cells_current[30][40] = alive;
}


void gol::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int spacing = 10;
    bool alive = true;

    for (int x = 0; x <= QWidget::width(); x += spacing)
    {
        painter.drawLine(x,0, x,QWidget::height());
    }

    for (int y = 0; y <= QWidget::height(); y += spacing)
    {
        painter.drawLine(0,y, QWidget::width(),y);
    }

    painter.setBrush(Qt::cyan);
//    painter.setPen(Qt::cyan);

    for (int i = 0; i < cells_current.size(); i+=10) {
        for (int j = 0; j < cells_current[i].size(); j+=10) {
            if (cells_current[i][j] == alive) {
                painter.drawRect(i, j, 10, 10);
            }
        }
    }
}

