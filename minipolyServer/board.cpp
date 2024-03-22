#include "board.h"


Board::Board()
{
    initializeBoard();
}

void Board::initializeBoard()
{
    //Die 4 Ecken des Spielbrettes
    squares[0] = Square(0,0,0, false);
    squares[7] = Square(0,0,0, false);
    squares[14] = Square(0,0,0, false);
    squares[21] = Square(0,0,0, false);
    //Collection 9: Transportmittel (alle 4 Seiten)
    squares[3] = Square(9,1500,350);
    squares[11] = Square(9,1500,350);
    squares[17] = Square(9,1500,350);
    squares[25] = Square(9,1500,350);
    //Collection 1 (Reihe 1)
    squares[1] = Square(1,1000,100);
    squares[2] = Square(1,1000,100);
    //Collection 2 (Reihe 1)
    squares[4] = Square(2,1000,150);
    squares[5] = Square(2,1000,150);
    squares[6] = Square(2,1000,150);
    //Collection 3 (Reihe 2)
    squares[8] = Square(3,1500,200);
    squares[9] = Square(3,1500,200);
    squares[10] = Square(3,1500,200);
    //Collection 4 (Reihe 2)
    squares[12] = Square(4,1700,250);
    squares[13] = Square(4,1700,250);
    //Collection 5 (Reihe 3)
    squares[15] = Square(5,2000,275);
    squares[16] = Square(5,2000,275);
    //Collection 6 (Reihe 3)
    squares[18] = Square(6,2000,300);
    squares[19] = Square(6,2000,300);
    squares[20] = Square(6,2000,300);
    //Collection 7 (Reihe 4)
    squares[22] = Square(7,2500,350);
    squares[23] = Square(7,2500,350);
    squares[24] = Square(7,2500,350);
    //Collection 8 (Reihe 4)
    squares[26] = Square(8,3500,500);
    squares[27] = Square(8,3500,500);
}
