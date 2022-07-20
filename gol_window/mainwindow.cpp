#include "mainwindow.h"
#include "QtWidgets/qpushbutton.h"
#include "gol.h"
#include "./ui_mainwindow.h"

#include <QLayout>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gol_setup();
    slider_setup();
    main_setup();

    connect(ui->actionPlay, SIGNAL(toggled(bool)), ui->actionPause, SLOT(setVisible(bool)));
    connect(ui->actionPause, SIGNAL(toggled(bool)), ui->actionPlay, SLOT(setVisible(bool)));
    ui->actionPause->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::main_setup() {
    main_layout = new QHBoxLayout;

    main_layout->addWidget(g);
    main_layout->addWidget(slider_box);

    central = new QWidget();

    central->setLayout(main_layout);
    setCentralWidget(central);
}

void MainWindow::gol_setup() {
    QHBoxLayout *layout = new QHBoxLayout;

    g = new gol();
    g->setFixedWidth(280);
    g->setLayout(layout);
}

void MainWindow::slider_setup()
{
    slider_box = new QGroupBox();
    slider_layout = new QHBoxLayout;

    speed_range = new QSlider(Qt::Horizontal);

    slider_layout->addWidget(speed_range);

    slider_box->setLayout((slider_layout));
}

void MainWindow::on_actionPlay_triggered()
{
    g->play_GOL();
    ui->actionPlay->setVisible(false);
    ui->actionPause->setVisible(true);
}


void MainWindow::on_actionPause_triggered()
{
    g->pause_GOL();
    ui->actionPlay->setVisible(true);
    ui->actionPause->setVisible(false);
}

void MainWindow::on_actionReset_triggered()
{
    g->pause_GOL();
    ui->actionPlay->setVisible(true);
    ui->actionPause->setVisible(false);
    g->reset_GOL();
}



