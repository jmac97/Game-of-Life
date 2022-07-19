#include "mainwindow.h"
#include "gol.h"
#include "./ui_mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g = new gol();
    this->setCentralWidget(g);

    connect(ui->actionPlay, SIGNAL(toggled(bool)), ui->actionPause, SLOT(setVisible(bool)));
    connect(ui->actionPause, SIGNAL(toggled(bool)), ui->actionPlay, SLOT(setVisible(bool)));
    ui->actionPause->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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

