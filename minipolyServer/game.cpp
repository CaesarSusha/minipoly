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
    QString result = "";
    switch(phase)
    {
    //warten auf Spieler zu würfeln
        case 0:
        {
            //Ermittlung der neuen Position
            int diceRoll = dices.rollDice();
            if(currentPlayer.getPosition() + diceRoll > 28)
            {
                currentPlayer.setPurse(currentPlayer.getPurse() + 200);
                result = "setPurse-" + QString::number(currentPlayer.getPurse()) + "-" + QString::number(currentPlayer.getId()) + "%";
            }
            int newPosition = (currentPlayer.getPosition() + diceRoll)%28;
            currentPlayer.setPosition(newPosition);
            result += "moveCurrentPlayerToGridcellId-" + QString::number(getCurrentPlayer().getPosition()) + "%" + "setDice-" + QString::number(diceRoll)+ "%";
            Player owner = gameBoard.squares[newPosition].getOwner();
            if(owner.getId() == -1)
            {
                if(currentPlayer.getPurse() >= gameBoard.squares[newPosition].getPrice())
                {
                    phase = 1;
                    return result;
                }
                phase = 2;
                return result;
            }

            if(owner.getId() == -2)
            {
                phase = 2;;
                return result + runGame(false);
            }

            if(currentPlayer.getId() == owner.getId())
            {
                phase = 2;
                return result + runGame(false);
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
            for(Player player : players)
            {
                if(player.getId() == owner.getId())
                {
                    player.setPurse(player.getPurse() + rent);
                }
            }
            result = "setPurse-" + QString::number(currentPlayer.getPurse()) + "-" + QString::number(currentPlayer.getId()) + "%" +
                     "setPurse-" + QString::number(owner.getPurse()) + "-" + QString::number(owner.getId()) + "%" +
                     "moveCurrentPlayerToGridcellId-" + QString::number(getCurrentPlayer().getPosition()) + "%" +
                     "setDice-" + QString::number(diceRoll)+ "%";
            if(currentPlayer.getPurse() < 0)
            {
                endGame();
                return "setGameOver";
            }
            phase = 2;
            return result + runGame(false);
        }
        //warten auf Spieler Feld zu kaufen
        case 1:
        {
            phase = 2;
            //Feld nicht kaufen
            if(!action)
            {
                squareBought = "No";
                return result + runGame(false);
            }
            //Feld kaufen
            int purse  = currentPlayer.getPurse() - gameBoard.squares[currentPlayer.getPosition()].getPrice();
            gameBoard.squares[currentPlayer.getPosition()].setOwner(currentPlayer);
            currentPlayer.setPurse(purse);
            squareBought = "Yes";
            result = "setPurse-" + QString::number(purse) + "-" + QString::number(currentPlayer.getId()) + "%" +
                     "setOwner-" + QString::number(getCurrentPlayer().getPosition()) + "-" + QString::number(getCurrentPlayer().getId()) + "%";
            return result + runGame(false);
        }
        //Zug beenden
        case 2:
        {
            QString content = "Turn: " + QString::number(turn) + "\t Player" + QString::number(currentPlayer.getId()) + "\t Purse: " + QString::number(currentPlayer.getPurse()) +
                              "\t Square: " + QString::number(currentPlayer.getPosition());
            if(squareBought != "")
            {
                content += "\t SquareBought: " + squareBought;
            }
            for(Player player : players)
            {
                content += "\t Player" + QString::number(player.getId()) + " " + QString::number(player.getPurse());
            }
            content += "\n";
            writeCSV("protocol", content);
            //Neuen Zug einleiten            
            phase = 0;
            currentPlayer = getNextPlayer();
            squareBought = "";
            return result + "setCurrentPlayer-" + QString::number(currentPlayer.getId());
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
    int i = 0;
    for(Player player : players)
    {
        if(player.getId() == currentPlayerId)
        {
            break;
        }
        i += 1;
    }
    if(i < playerAmount)
    {
        players.removeAt(i);
        players.push_back(currentPlayer);
    }
    if(phase == 0)
    {
        turn += 1;
    }
    return players.value(0);
    if(currentPlayerId == playerAmount || currentPlayerId == -1)
    {
        //Letzter Spieler in der Reihe war am Zug -> erster Spieler beginnt seinen Zug
        return players.at(0);
        turn += 1;
    }
    else
    {
        players.value(currentPlayerId - 1) = currentPlayer;
        //Nächster bzw. erster Spieler wird ausgegeben
        return players.value(currentPlayerId);
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

void Game::endGame()
{
    QString content = "Turn: " + QString::number(turn) + "\t Player" + QString::number(currentPlayer.getId()) + "\t Purse: " + QString::number(currentPlayer.getPurse()) +
                      "\t Square: " +  QString::number(currentPlayer.getPosition()) + "\n\n\n";
    writeCSV("protocol", content);
    for(Player player : players)
    {
        if(player.getPurse() > 0)
        {
            content = "Player" + QString::number(player.getId()) + "\t Purse: " + QString::number(player.getPurse()) + "\n";
            break;
        }
    }
    writeCSV("highscore", content);
    turn = -1;
}

void Game::writeCSV(QString filename, QString content)
{
    QFile file("./" + filename + ".csv");
    if (file.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream stream(&file);
        stream << content;
        file.close();
    }
}
