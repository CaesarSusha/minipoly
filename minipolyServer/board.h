#ifndef BOARD_H
#define BOARD_H

#include "square.h"

class Board
{
public:
    Board();
    //Felder des Spielfeldes
    Square squares[28];
private:
    void initializeBoard();
};

#endif // BOARD_H
