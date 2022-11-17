#include "gridwidget.h"
#include "mythread.h"



GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{

    setTimer();
    createRandomGrid();
    mthread = new mythread(grid, XAxis, YAxis);
    QThread *thread = new QThread();
    mthread->moveToThread(thread);

}
GridWidget::~GridWidget()
{

}

void GridWidget::stopTimer()
{
    timer->stop();
}
void GridWidget::paintEvent(QPaintEvent* event)
{
          QPainter painter(this);
          for(int i=0; i<YAxis; i++)
          {
          for(int j=0; j<XAxis; j++)
             {
              if(grid[i][j] == 1) painter.setBrush(Qt::black);
              else if(grid[i][j] == 0) painter.setBrush(Qt::white);
              QRect r(i*10,j*10,10,10);
              painter.drawRect(r);
              }
          }
}
void GridWidget::createRandomGrid()
{   grid = new int*[XAxis];
    for(int i =0; i<XAxis; i++)
    {   grid[i] = new int[YAxis];
        for(int j=0; j<YAxis; j++)
        {
            grid[i][j] =  rand() % 2;
        }
    }
}

void GridWidget::evolve()
{   timer->start();
    mthread->start();
    update();

}

void GridWidget::setTimer()
{
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(evolve()));
}
void GridWidget::setTimerInterval(const int &msec)
{

    timer->setInterval(msec);
}

int GridWidget::getTimerInterval() const
{
    return timer->interval();
}






