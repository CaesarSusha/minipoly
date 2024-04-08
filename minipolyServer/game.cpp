#include "game.h"

Game::Game()
{
    dices = Dice(12);
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
    //Warten auf Würfeln des Spielers
        case 0:
        {
            //Ermittlung der neuen Position
            int diceRoll = dices.rollDice();

            //Spieler läuft über das Startfeld
            if(currentPlayer.getPosition() + diceRoll > 28)
            {
                currentPlayer.setPurse(currentPlayer.getPurse() + 50);
                result = "setPurse_" + QString::number(currentPlayer.getPurse()) + "_" + QString::number(currentPlayer.getId()) + "%";
            }
            int newPosition = (currentPlayer.getPosition() + diceRoll)%28;
            currentPlayer.setPosition(newPosition);
            result += "moveCurrentPlayerToGridcellId_" + QString::number(newPosition) + "%" + "setDice_" + QString::number(diceRoll)+ "%";

            //Ermittlung des Besitzers des neuen Feldes
            Player owner = gameBoard.squares[newPosition].getOwner();

            //Das Feld hat keinen Besitzer und ist kaufbar
            if(owner.getId() == -1)
            {
                int price = gameBoard.squares[newPosition].getPrice();
                if(currentPlayer.getPurse() >= price)
                {
                    phase = 1;
                    result += "displayPurchasingUI_" + QString::number(price) + "%";
                    return result;
                }
                phase = 2;
                return result;
            }

            //Das Feld hat keinen Besitzer und ist nicht kaufbar
            if(owner.getId() == -2)
            {
                phase = 2;;
                return result + runGame(false);
            }

            //Der aktuelle Spieler ist der Besitzer
            if(currentPlayer.getId() == owner.getId())
            {
                phase = 2;
                return result + runGame(false);
            }

            //Ermittelung der Miete
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

            //Aktualisierung des Geldbeutels jedes Spielers
            currentPlayer.setPurse(currentPlayer.getPurse() - rent);
            int ownerId = 0;
            for(Player player : players)
            {
                if(player.getId() == owner.getId())
                {
                    break;
                }
                ownerId += 1;
            }
            players[ownerId].setPurse(players[ownerId].getPurse() + rent);
            result = "setPurse_" + QString::number(currentPlayer.getPurse()) + "_" + QString::number(currentPlayer.getId()) + "%" +
                     "setPurse_" + QString::number(players[ownerId].getPurse()) + "_" + QString::number(owner.getId()) + "%" +
                     "moveCurrentPlayerToGridcellId_" + QString::number(getCurrentPlayer().getPosition()) + "%" +
                     "setDice_" + QString::number(diceRoll)+ "%";

            //Ein Spieler hat Schulden => Ende des Spiels
            if(currentPlayer.getPurse() < 0)
            {
                endGame();
                return result + "setGameOver";
            }
            phase = 2;
            return result + runGame(false);
        }

        //Warten auf Entscheidung des Spielers
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
            result = "setPurse_" + QString::number(purse) + "_" + QString::number(currentPlayer.getId()) + "%" +
                     "setOwner_" + QString::number(getCurrentPlayer().getPosition()) + "_" + QString::number(getCurrentPlayer().getId()) + "%";
            return result + runGame(false);
        }
        //Zug beenden
        case 2:
        {
            //Zugereignisse protokollieren
            QString content = "Turn: " + QString::number(turn) +
                              ",\t Player" + QString::number(currentPlayer.getId()) +
                              ",\t Purse: " + QString::number(currentPlayer.getPurse()) +
                              ",\t Square: " + QString::number(currentPlayer.getPosition());
            if(squareBought != "")
            {
                content += ",\t SquareBought: " + squareBought;
            }

            content += "\n";
            writeCSV("protocol", content);

            //Neuen Zug einleiten            
            phase = 0;
            currentPlayer = getNextPlayer();
            squareBought = "";
            return result + "setCurrentPlayer_" + QString::number(currentPlayer.getId());
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
    //Keine Spieler vorhanden
    if(playerAmount == 0)
    {
        return Player();
    }
    int currentPlayerId = currentPlayer.getId();
    int i = 0;

    //Ermittlung der Position des aktuellen Spielers in der Liste
    for(Player player : players)
    {
        if(player.getId() == currentPlayerId)
        {
            break;
        }
        i += 1;
    }
    //Aktuellen Spieler vom Anfang der Liste nehmen und ans Ende setzen
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
    // Zugereignisse protokollieren
    QString content = "Turn: " + QString::number(turn) +
                      ",\t Player" + QString::number(currentPlayer.getId()) +
                      ",\t Purse: " + QString::number(currentPlayer.getPurse()) +
                      ",\t Square: " +  QString::number(currentPlayer.getPosition()) +
                      "\n\n\n";
    writeCSV("protocol", content);

    int winner = players[0].getId() - 1;

    //Gewinner (Spieler mit meistem Geld) ermitteln
    for(Player player : players)
    {
        if(player.getPurse() > players[winner].getPurse())
        {
            winner = player.getId() - 1;
        }
    }

    // Gewinner protokollieren
    content = "Gewinner: Player " + QString::number(players[winner].getId()) +
              "\t Erwirtschaftetes Geld: " + QString::number(players[winner].getPurse()) +
              " Coins \n";
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
