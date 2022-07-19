#ifndef GOL_H
#define GOL_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QMouseEvent>

class gol : public QWidget
{
    Q_OBJECT
public:
    explicit gol(QWidget *parent = nullptr);

    void play_GOL();
    void pause_GOL();
    void reset_GOL();

private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void set_timer();
    void get_next_generation();
    void cell_swap();

    //still lifes
    void block();
    void beehive();
    void tub();
    void boat();
    void loaf();

    //oscillators
    void blinker();
    void toad();
    void beacon();
    void pulsar();
    void pentadecathlon();

    //spaceships
    void glider();
    void light_weight_spaceship();
    void middle_weight_spaceship();
    void heavy_weight_spaceship();

    int generation = 0;
    bool timer_started = false;

    int spacing = 10;

    std::vector<std::vector<bool>> cells_current;
    std::vector<std::vector<bool>> cells_next_gen;

    int grid_offset = 200;
    int scale = grid_offset/2;

    bool alive = true;
    bool play = false;

    int userX = 0;
    int userY = 0;

};

#endif // GOL_H
