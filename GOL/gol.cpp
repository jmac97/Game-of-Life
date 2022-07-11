#include "gol.h"
#include "./ui_gol.h"

gol::gol(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gol)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&gol::update));
    timer->start(1000);
    ui->setupUi(this);
}

gol::~gol()
{
    delete ui;
}


void gol::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int spacing = 10;

    for (int x = 0; x <= QWidget::width(); x += spacing)
    {
        painter.drawLine(x,0, x,QWidget::height());
    }

    for (int y = 0; y <= QWidget::height(); y += spacing)
    {
        painter.drawLine(0,y, QWidget::width(),y);
    }

    painter.setBrush(Qt::cyan);
    painter.setPen(Qt::cyan);
    painter.drawRect(cellX,cellY, cellSize,cellSize);

    cellX += 10;
}

