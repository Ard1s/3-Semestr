#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gridwidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void speedSlider();

private slots:

    void on_btn_start_clicked();
    void on_btn_stop_clicked();

private:

    Ui::MainWindow *ui;
    GridWidget* grid;



};
#endif // MAINWINDOW_H
