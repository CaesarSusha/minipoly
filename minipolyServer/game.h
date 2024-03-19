#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "dice.h"
#include <QtCore/QList>
#include "QtWebSockets/qwebsocket.h"

class Game
{
public:
    Game();
    //Objekt für den Würfel
    Dice dices;
    //Objekt für das Spielfeld
    Board gameBoard;

    int addPlayer(QWebSocket* socket);
    QString runGame(bool action);
    int rollDice();
    int MoveToNewPosition(int rollresult);
    void setCurrentPlayer(Player newPlayer);
    Player getCurrentPlayer();
    Player getNextPlayer();
    int getTurn();
    int getPhase();

private:
    Player currentPlayer;
    int turn;
    int phase;
    int playerAmount;
    //Player Objekte für die Spieler
    QList<Player> players;
};

#endif // GAME_H
