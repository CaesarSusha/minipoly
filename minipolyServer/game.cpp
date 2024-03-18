#include "game.h"

Game::Game()
{
    dices = Dice(6);
    gameBoard = Board();
    currentPlayer = Player();
    turn = 0;
    phase = 0;
    playerAmount = 0;
}

int Game::addPlayer(QWebSocket* socket)
{
    playerAmount += 1;
    players<<Player(socket, playerAmount);
    return playerAmount;
}

string Game::runGame(int action)
{
    switch(phase)
    //warten auf Spieler zu würfeln
    case 0:
        return "";
        break;
    //warten auf Spieler Feld zu kaufen
    case 1:
        return "";
        break;
    // warten auf Spieler Zug zu beenden
    case 2:
        return "";
        break;
    //hierhin kommt die Spiellogik
    return;
}

int Game::rollDice()
{
    return dices.rollDice();
}

int Game::MoveToNewPosition(int rollresult)
{
    currentPlayer.setPosition(currentPlayer.getPosition() + rollresult);
    return currentPlayer.getPosition();
}

void Game::setCurrentPlayer(Player newPlayer)
{
    currentPlayer = newPlayer;
}


Player Game::getCurrentPlayer()
{
    return currentPlayer;
}

Player Game::getNextPlayer()
{
    if(playerAmount == 0)
    {
        return Player();
    }
    int currentPlayerId = currentPlayer.getId();
    if(currentPlayerId == playerAmount)
    {
        //Letzter Spieler in der Reihe war am Zug -> erster Spieler beginnt seinen Zug
        return players[0];
    }
    else
    {
        //Nächster bzw. erster Spieler wird ausgegeben
        return players[currentPlayerId + 1];
    }
}

Player Game::getPlayer(QWebSocket* socket)
{
    for(Player player : players)
    {
        if(player.getSocket() == socket)
        {
            return player;
        }
    }
}

int Game::getTurn()
{
    return turn;
}
