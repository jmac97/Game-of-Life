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

    void seed_grid();
    void get_next_generation();
    void cell_swap();
    void update_grid();


protected:
    void paintEvent(QPaintEvent *event);

    int cell_size = 10;
    int generation = 0;

    // Not sure if this is needed
    int window_width = 255;
    int window_height = 255;

    std::vector<std::vector<bool>> cells_current;
    std::vector<std::vector<bool>> cells_next_gen;
    std::vector<std::vector<bool>> empty;

private:
    Ui::gol *ui;
};
#endif // GOL_H
