#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gridwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grid(new GridWidget(this))
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(grid);
    speedSlider();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{

    grid->evolve();

}


void MainWindow::speedSlider()
{    ui->speedSlider->setMinimum(1);
     ui->speedSlider->setMaximum(1000);
     ui->speedSlider->setValue(1);
    connect(ui->speedSlider, SIGNAL(valueChanged(int)), grid, SLOT(setTimerInterval(int)));
}


void MainWindow::on_btn_stop_clicked()
{
    grid->stopTimer();
}

