#ifndef BOARD_H
#define BOARD_H


#include "Call_states.h"
#include <QString>

class Board
{
private:

    Call_states allBoard[15][10];
    unsigned short int numberOfMin (unsigned short int, unsigned short int);

public:
    Board       ();
    void clear  ();

    void generateNew();
    void clickAllMines();
    bool isWin();
    bool checkFlag();

    Call_states get         (unsigned short int, unsigned short int);
    void setClick           (unsigned short int, unsigned short int);

    void setFlag            (unsigned short int y, unsigned short int x);
    void setMineBoom        (unsigned short int y, unsigned short int x);
    void unSetFlag          (unsigned short int y, unsigned short int x);
    void clickNeigbors      (unsigned short int y, unsigned short int x);

    bool isMine             (unsigned short int, unsigned short int);
    QString getColorNumber  (unsigned short int, unsigned short int);

};
#endif // BOARD_H

