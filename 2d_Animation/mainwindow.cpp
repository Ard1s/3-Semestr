#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Beautiful Fox!");
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    fox = new Fox;
    scene -> addItem(fox);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scale(1.5, 1.5);
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_pushButton_pressed()
{
    QMessageBox::about(this, "Tap this message", "Thanks for watching");
}
