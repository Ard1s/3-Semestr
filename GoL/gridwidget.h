#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <random>
#include "mythread.h"

class GridWidget : public QWidget
{
    Q_OBJECT

public:
   explicit GridWidget(QWidget *parent = nullptr);
    ~GridWidget();
    int getTimerInterval() const;
    mythread *mthread;
    void stopTimer();

public slots:
      void evolve();
      void setTimerInterval(const int& msec);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    int** grid;
    void createRandomGrid();
    int XAxis = 200;
    int YAxis = 200;
    QTimer* timer;
    void setTimer();


};

#endif // GRIDWIDGET_H
