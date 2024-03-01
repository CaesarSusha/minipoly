#include "game.h"

Game::Game()
{
    dices = Dice(6);
    gameBoard = Board();
    currentPlayer = Player();
    turn = 0;
}

int Game::addPlayer()
{
    int playerAmount = players.size();
    players.push_back(Player(playerAmount));
    return playerAmount;
}

void Game::runGame()
{
    //hierhin kommt die Spiellogik
    return;
}

int Game::rollDice(Dice dices)
{
    return dices.rollDice();
}

void Game::setCurentPlayer(Player newPlayer)
{
    currentPlayer = newPlayer;
}

Player Game::getCurrentPlayer()
{
    return currentPlayer;
}

Player Game::getNextPlayer()
{
    int playerAmount = players.size();
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

int Game::getTurn()
{
    return turn;
}
