#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player();
    Player(int id);

    int getId();

    //Methoden zur Positionsanpassung im Verlauf des Spieles
    void setPosition(int position);
    int getPosition();

    //Methoden zur Anpassung des Geldes des Spielers
    void setPurse(int amount);
    int getPurse();

private:
    int id;
    int position;
    int purse;

};

#endif // PLAYER_H
