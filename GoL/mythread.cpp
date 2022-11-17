#include "mythread.h"

#include <QDebug>

mythread::mythread(int **grid, const int &XAxis, const int &YAxis)
    : grid(grid) , XAxis(XAxis) , YAxis(YAxis)
{

}

int mythread::neighbourSum(int** grid, const int& XAxis, const int& YAxis, const int& XState, const int& YState)
{
    int sum = 0;
       for (int y = std::max(XState-1, 0); y < std::min(XState+2, XAxis); ++y)
       {
           for (int x = std::max(YState-1, 0); x < std::min(YState+2, YAxis); ++x)
           {
               sum += grid[y][x] & 1;
           }
       }
       return sum -= grid[XState][YState] & 1;
}


void mythread::run()
{
   for (int x=0; x<XAxis; ++x)
   {
       for (int y=0; y<YAxis; ++y)
       {
           int sum = neighbourSum(grid, XAxis, YAxis, x, y);
           if ((sum | grid[x][y]) == 3)
           {
               grid[x][y]|=2;
           }
       }
   }
   for (int x = 0; x< XAxis; ++x)
       for (int y = 0; y<YAxis; ++y)
       {
           grid[x][y] >>=1;
       }

}
//
