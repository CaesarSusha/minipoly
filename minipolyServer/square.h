#ifndef SQUARE_H
#define SQUARE_H
#include "player.h"

class Square
{
public:
    Square();
    Square(int collection, int price, int rent);
    void setOwner(Player newOwner);
    Player getOwner();
    int getCollection();
    int getPrice();
    int getRent();

private:
    Player owner;
    //Collection zu der das Feld gehört. Doppelte Miete, wenn ein Spieler die komplette Collection hat
    int collection;
    //Kaufpreis des Feldes
    int price;
    //Miete für das Feld, wenn ein Spieler darauf landet
    int rent;

};

#endif // SQUARE_H
