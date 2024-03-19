#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "dice.h"
#include <vector>

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
    int rollDice();
    void setNewPosition(int rollresult);
    void setCurrentPlayer(Player newPlayer);
    Player getCurrentPlayer();
    Player getNextPlayer();
    int getTurn();

private:
    Player currentPlayer;
    int turn;
    //Player Objekte für die Spieler
    std::vector<Player> players;
};

#endif // GAME_H
