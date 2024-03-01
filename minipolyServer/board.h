#ifndef BOARD_H
#define BOARD_H

#include "square.h"

class Board
{
public:
    Board();
    //Felder des Spielfeldes
    Square Squares[28];
private:
    void initializeBoard(Square Squares[]);
};

#endif // BOARD_H
