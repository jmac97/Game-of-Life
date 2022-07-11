#ifndef GOL_H
#define GOL_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class gol; }
QT_END_NAMESPACE

class gol : public QWidget
{
    Q_OBJECT

public:
    gol(QWidget *parent = nullptr);
    ~gol();

protected:
    void paintEvent(QPaintEvent *event);
    int cellSize = 10;
    int cellX = 10;
    int cellY = 10;



private:
    Ui::gol *ui;
};
#endif // GOL_H
