#ifndef DICE_H
#define DICE_H


class Dice
{
public:
    Dice();
    Dice(int);

    //Ergebnis eines Würfelwurfs
    int rollDice();

private:
    //Anzahl der Augen, die der Würfel haben soll
    int Eyes;
};

#endif // DICE_H
