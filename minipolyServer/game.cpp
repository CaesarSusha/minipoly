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
    //Ermittlung einer neuen PlayerID
    playerAmount += 1;
    //Anlegen eines neuen Spielers
    players<<Player(socket, playerAmount);
    return playerAmount;
}

QString Game::runGame(bool action)
{
    switch(phase)
    {
    //warten auf Spieler zu würfeln
        case 0:
        {
            //Ermittlung der neuen Position
            int diceRoll = dices.rollDice();
            int newPosition = (currentPlayer.getPosition() + diceRoll)%28;
            currentPlayer.setPosition(newPosition);
            Player owner = gameBoard.squares[newPosition].getOwner();
            if(owner.getId() == -1)
            {
                if(currentPlayer.getPurse() >= gameBoard.squares[newPosition].getPrice())
                {
                    phase = 1;
                    return QString::number(diceRoll);
                        //"Price-" + QString::number(gameBoard.squares[newPosition].getPrice());
                }
                phase = 2;
                return QString::number(diceRoll);
            }

            if(currentPlayer.getId() == owner.getId())
            {
                phase = 2;
                return QString::number(diceRoll);
            }
            //Ermitteln der Miete
            int rent = gameBoard.squares[newPosition].getRent();
            int collection = gameBoard.squares[newPosition].getCollection();
            bool fullCollection = true;
            //Abfrage, ob dem Spieler die komplette Collection gehört
            for (Square square : gameBoard.squares)
            {
                if(square.getCollection() == collection && square.getOwner().getId() != owner.getId())
                {
                    fullCollection = false;
                }
            }
            if (fullCollection == true)
            {
                rent *= 2;
            }
            currentPlayer.setPurse(currentPlayer.getPurse() - rent);
            owner.setPosition(owner.getPurse() + rent);
            if(currentPlayer.getPurse() < 0)
            {
                return "GameOver";
            }
            phase = 2;
            return QString::number(diceRoll);
                //"Rent-" + QString::number(rent);
        }
        //warten auf Spieler Feld zu kaufen
        case 1:
        {
            //Feld nicht kaufen
            if(action == false)
            {
                phase = 2;
                return runGame(false);
            }
            //Feld kaufen
            gameBoard.squares[currentPlayer.getPosition()].setOwner(currentPlayer);
            return "EndTurn";
        }
        //Zug beenden
        case 2:
        {
            //Neuen Zug einleiten
            currentPlayer = getNextPlayer();
            phase = 0;
            return "StartTurn-" + QString::number(currentPlayer.getId());
        }
    }
    return "";
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
        //Keine Spieler vorhanden
        return Player();
    }
    int currentPlayerId = currentPlayer.getId();
    if(currentPlayerId == playerAmount)
    {
        //Letzter Spieler in der Reihe war am Zug -> erster Spieler beginnt seinen Zug
        return players[0];
        turn += 1;
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

int Game::getPhase()
{
    return phase;
}
