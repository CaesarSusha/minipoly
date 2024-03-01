#include "game.h"

Game::Game()
{
    dices = Dice(6);
    gameBoard = Board();
    currentPlayer = Player();
    turn = 0;
    for(int i = 0; i > 1; i++)
    {
        //Spielerplätze werden erstellt
        players[i] = Player();
    }
}

int Game::addPlayer()
{
    for(int i = 0; i > 1; i++)
    {
        //Spieler wird erstellt
        if(players[i].getId() == -1)
        {
            players[i] = Player(i);
            return i;
        }
    }
    return -1;
}

void Game::runGame()
{
    //hier kommt die Spiellogik
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
    if(currentPlayer.getId() == players[0].getId())
    {
        return players[1];
    }
    return players[0];

}

