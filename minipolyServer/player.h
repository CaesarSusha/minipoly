#ifndef PLAYER_H
#define PLAYER_H
#include "QtWebSockets/qwebsocket.h"

class Player
{
public:
    Player();
    Player(QWebSocket* socket, int id);

    int getId();
    QWebSocket* getSocket();

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
    QWebSocket* socket;
};

#endif // PLAYER_H
