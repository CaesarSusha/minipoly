#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "dice.h"

class Game
{
public:
    Game();
    //Objekt für den Würfel
    Dice dices;
    //Objekt für das Spielfeld
    Board gameBoard;

    int addPlayer();
    void runGame();
    int rollDice(Dice dices);
    void setCurentPlayer(Player newPlayer);
    int getCurrentPlayer();
    int getNextPlayer();
    int getTurn();

private:
    Player currentPlayer;
    int turn;
    //Player Objekte für die Spieler
    Player players[2];



};

#endif // GAME_H
