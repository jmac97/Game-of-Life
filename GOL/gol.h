#ifndef GOL_H
#define GOL_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class gol; }
QT_END_NAMESPACE

class gol : public QWidget
{
    Q_OBJECT

public:
    gol(QWidget *parent = nullptr);
    ~gol();

    // Not sure if this is needed
    void set_window_parameters(int w, int h);

    void set_generation(int gen);

    void set_timer();
    void seed_grid();
    void get_next_generation();
    void cell_swap();
    void update_grid();


protected:
    void paintEvent(QPaintEvent *event);

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

    int cell_size = 10;
    int generation = 0;
    bool timer_started = false;

    // Not sure if this is needed
    int window_width = 255;
    int window_height = 255;

    std::vector<std::vector<bool>> cells_current;
    std::vector<std::vector<bool>> cells_next_gen;

private:
    Ui::gol *ui;
};
#endif // GOL_H
