#include "board.h"


Board::Board()
{
    initializeBoard(this->Squares);
}

void Board::initializeBoard(Square Squares[])
{
    //Die 4 Ecken des Spielbrettes
    Squares[0] = Square(0,0,0);
    Squares[7] = Square(0,0,0);
    Squares[14] = Square(0,0,0);
    Squares[21] = Square(0,0,0);
    //Collection 1 (alle 4 Seiten)
    Squares[4] = Square(1,1000,100);
    Squares[11] = Square(1,1000,100);
    Squares[18] = Square(1,1000,100);
    Squares[24] = Square(1,1000,100);
    //Collection 2 (Seite 1)
    Squares[1] = Square(2,1000,100);
    Squares[2] = Square(2,1000,100);
    Squares[3] = Square(2,1000,100);
    //Collection 3 (Seite 1)
    Squares[5] = Square(3,1000,100);
    Squares[6] = Square(3,1000,100);
    //Collection 4 (Seite 2)
    Squares[8] = Square(4,1000,100);
    Squares[9] = Square(4,1000,100);
    Squares[10] = Square(4,1000,100);
    //Collection 5 (Seite 2)
    Squares[12] = Square(5,1000,100);
    Squares[13] = Square(5,1000,100);
    //Collection 6 (Seite 3)
    Squares[15] = Square(6,1000,100);
    Squares[16] = Square(6,1000,100);
    Squares[17] = Square(6,1000,100);
    //Collection 7 (Seite 3)
    Squares[19] = Square(7,1000,100);
    Squares[20] = Square(7,1000,100);
    //Collection 8 (Seite 4)
    Squares[22] = Square(8,1000,100);
    Squares[23] = Square(8,1000,100);
    //Collection 9 (Seite 4)
    Squares[25] = Square(9,1000,100);
    Squares[26] = Square(9,1000,100);
    Squares[27] = Square(9,1000,100);
}
