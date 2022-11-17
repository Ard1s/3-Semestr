#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QObject>

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(int **grid, const int &XAxis, const int &YAxis);

    int neighbourSum(int** grid, const int& XAxis, const int& YAxis, const int& XState, const int& YState);
    int** grid;
    int XAxis;
    int YAxis;
    void run();



};

#endif // MYTHREAD_H
