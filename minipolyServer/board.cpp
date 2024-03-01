#include "board.h"


Board::Board()
{
    initializeBoard();
}

void Board::initializeBoard()
{
    //Die 4 Ecken des Spielbrettes
    squares[0] = Square(0,0,0);
    squares[7] = Square(0,0,0);
    squares[14] = Square(0,0,0);
    squares[21] = Square(0,0,0);
    //Collection 1 (alle 4 Seiten)
    squares[4] = Square(1,1000,100);
    squares[11] = Square(1,1000,100);
    squares[18] = Square(1,1000,100);
    squares[24] = Square(1,1000,100);
    //Collection 2 (Seite 1)
    squares[1] = Square(2,1000,100);
    squares[2] = Square(2,1000,100);
    squares[3] = Square(2,1000,100);
    //Collection 3 (Seite 1)
    squares[5] = Square(3,1000,100);
    squares[6] = Square(3,1000,100);
    //Collection 4 (Seite 2)
    squares[8] = Square(4,1000,100);
    squares[9] = Square(4,1000,100);
    squares[10] = Square(4,1000,100);
    //Collection 5 (Seite 2)
    squares[12] = Square(5,1000,100);
    squares[13] = Square(5,1000,100);
    //Collection 6 (Seite 3)
    squares[15] = Square(6,1000,100);
    squares[16] = Square(6,1000,100);
    squares[17] = Square(6,1000,100);
    //Collection 7 (Seite 3)
    squares[19] = Square(7,1000,100);
    squares[20] = Square(7,1000,100);
    //Collection 8 (Seite 4)
    squares[22] = Square(8,1000,100);
    squares[23] = Square(8,1000,100);
    //Collection 9 (Seite 4)
    squares[25] = Square(9,1000,100);
    squares[26] = Square(9,1000,100);
    squares[27] = Square(9,1000,100);
}
