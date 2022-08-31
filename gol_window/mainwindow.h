#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLayout>
#include "gol.h"
#include "slider.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionReset_triggered();

    void slider_setup();
    void gol_setup();
    void main_setup();

private:
    Ui::MainWindow *ui;
    gol *g;
    Slider *speed_range;
    Slider *size_range;
    QWidget *central;
    QGroupBox *slider_box;
    QVBoxLayout *slider_layout;
    QHBoxLayout *main_layout;
};
#endif // MAINWINDOW_H
