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

void gol::set_timer() {
    if (timer_started == false) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&gol::update));
        timer->start(1000);
        timer_started = true;
    }
}

void gol::set_window_parameters(int w, int h) {
    window_width = w;
    window_height = h;
    setFixedSize(window_width, window_height);
}

void gol::set_generation(int gen)
{
    generation = gen;
}

void gol::seed_grid()
{
    int spacing = 10;
    bool alive = true;

    // blinker
    cells_current.resize(100);  // resize top level vector
    cells_next_gen.resize(100);
    for (int i = 0; i < 100; i+=10)
    {
        cells_current[i].resize(100);  // resize each of the contained vectors
        cells_next_gen[i].resize(100);

        for (int j = 0; j < 100; j+=10)
        {
            cells_current[i][j] = 0;
            cells_next_gen[i][j] = 0;
        }
    }

    glider();
}

void gol::blinker() {
    bool alive = true;
    cells_current[20][30] = alive;
    cells_current[30][30] = alive;
    cells_current[40][30] = alive;
}

void gol::toad() {
    bool alive = true;
    cells_current[30][30] = alive;
    cells_current[50][20] = alive;
    cells_current[60][30] = alive;
    cells_current[30][40] = alive;
    cells_current[60][40] = alive;
    cells_current[40][50] = alive;
}

void gol::beacon() {
    bool alive = true;
    cells_current[30][30] = alive;
    cells_current[40][30] = alive;
    cells_current[30][40] = alive;
    cells_current[60][50] = alive;
    cells_current[50][60] = alive;
    cells_current[60][60] = alive;
}

void gol::glider() {
    bool alive = true;
    cells_current[30][30] = alive;
    cells_current[50][30] = alive;
    cells_current[40][40] = alive;
    cells_current[50][40] = alive;
    cells_current[40][50] = alive;
}


void gol::get_next_generation() {
    int neighbor = 0;
    int count = 0;

    for (int i = 10; i < 90; i+=10) {
        for (int j =10; j < 90; j+=10) {

            for (int k = i - 10; k <= i + 10; k+=10) {
                for (int l = j - 10; l <= j + 10; l+=10) {

                    if (cells_current[k][l] == true) {
                            neighbor++;
                    }
                }
            }

            if (cells_current[i][j] == true) {
                neighbor -= 1;
                if (neighbor == 2 || neighbor == 3) {
                    cells_next_gen[i][j] = true;
                } else {
                    cells_next_gen[i][j] = false;
                }
            } else {
                if (neighbor == 3) {
                    cells_next_gen[i][j] = true;
                } else {
                    cells_next_gen[i][j] = false;
                }
            }

            neighbor = 0;

        }
    }
}

void gol::cell_swap() {
    for (int i = 0; i < 100; i+=10) {
        for (int j = 0; j < 100; j+=10) {
            cells_current[i][j] = cells_next_gen[i][j];
            cells_next_gen[i][j] = 0;
        }
    }
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

    if (QEvent::Show) {
        set_timer();
        qDebug() << "Generation: " << generation;
         if (generation == 0) {
             for (int i = 0; i < cells_current.size(); i+=10) {
                 for (int j = 0; j < cells_current[i].size(); j+=10) {
                     if (cells_current[i][j] == alive) {
                         painter.drawRect(i, j, 10, 10);
                     }
                 }
             }
         } else {
             get_next_generation();
             for (int i = 0; i < cells_next_gen.size(); i+=10) {
                 for (int j = 0; j < cells_next_gen[i].size(); j+=10) {
                     if (cells_next_gen[i][j] == alive) {
                         painter.drawRect(i, j, 10, 10);
                     }
                 }
             }
             cell_swap();
         }
         generation++;
    }
}

