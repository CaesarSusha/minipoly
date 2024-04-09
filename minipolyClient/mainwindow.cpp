#include "mainwindow.h"
#include "gridcell.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("background-color: #1B201D;");
    this->width = 900;
    this->height = 900;
    this->boardSize = 900;
    this->setGeometry(0, 0, width, height);
    this->lastXPos = 0;
    this->lastYPos = 0;
    this->setFixedSize(*new QSize(width,height));

    for(int i = 1; i <= 6; i++)
    {
        player[i] = Player();
        player[i].playerId = i;
    }

    initGrid();

    //minipoly Titel anzeigen
    titleLabel = new QLabel(this);
    QPixmap pmtitle(":/title");
    titleLabel->setPixmap(pmtitle);
    //Das Qlabel, welches das Logo erhält in die Mitte des Bildes setzen
    titleLabel->setGeometry(370, 300, pmtitle.width(), pmtitle.height());

    //Menschlicher Player Knopf anzeigen und verbinden
    humanPlayerButton = new QPushButton(this);
    humanPlayerButton->setText("Human");
    humanPlayerButton->setEnabled(true);
    humanPlayerButton->setVisible(true);
    humanPlayerButton->setGeometry(370, 400, pmtitle.width(), pmtitle.height());
    humanPlayerButton->setStyleSheet("background-color: #D484A2");
    connect(humanPlayerButton, &QPushButton::clicked, this, [=]() {startGame();});

    //KI-Spieler Knopf
    computerPlayerButton = new QPushButton(this);
    computerPlayerButton->setText("Computer");
    computerPlayerButton->setEnabled(true);
    computerPlayerButton->setVisible(true);
    computerPlayerButton->setGeometry(370, 500, pmtitle.width(), pmtitle.height());
    computerPlayerButton->setStyleSheet("background-color: #5C78AC");
    connect(computerPlayerButton, &QPushButton::clicked, this, [=]() {startGame();});

    //Würfel verstecken
    grid[2][3]->setVisible(false);
    grid[2][4]->setVisible(false);

    //Zugtext verstecken
    grid[1][3]->setVisible(false);
    grid[1][4]->setVisible(false);
}

void MainWindow::startGame()
{
    //Willkommens-UI ausblenden
    titleLabel->setVisible(false);
    humanPlayerButton->setVisible(false);
    computerPlayerButton->setVisible(false);

    //Würfel einblenden
    grid[2][3]->setVisible(true);
    grid[2][4]->setVisible(true);

    //Zugtext einblenden
    grid[1][3]->setVisible(true);
    grid[1][4]->setVisible(true);

    //Display starting UI
    grid[3][3]->setText("Your \nPurse:");
    grid[3][3]->setStyleSheet("color: #FFD954");
    grid[3][3]->setVisible(true);

    grid[3][4]->setText(QString::number(player[myPlayerId].purse));
    grid[3][4]->setStyleSheet("color: #FFD954");
    grid[3][4]->setVisible(true);
}

void MainWindow::initGrid()
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            //Zellen anlegen
            this->grid[x][y] = new GridCell(this, x, y);

            //Maße jeder Zelle ermitteln
            int rectWidth = determineWidth(y);
            int rectHeight = determineHeight(x);
            int boardStartX = 0;
            int boardStartY = 0;
            grid[x][y]->setGeometry(QRect(boardStartX +(lastXPos),
                                          boardStartY + (lastYPos),
                                          rectWidth, rectHeight));
            //Bilder einfügen
            QString iconPath = ":/" + QString::number(x) + QString::number(y);
            grid[x][y]->setIcon(QIcon(QPixmap(iconPath)));
            grid[x][y]->setIconSize(QSize(rectWidth, rectHeight));

            //Buttons in der Mitte ausschalten
            if (grid[x][y]->icon().isNull())
            {
                grid[x][y]->setFlat(true);
                grid[x][y]->setEnabled(false);
            }
            //Position aktualisieren und bei Bedarf zur nächsten Zeile des grids wechseln
            updateLastPos(y, rectHeight, rectWidth);
        }
    }
}

int MainWindow::determineWidth(int x)
{
    return (x == 0 || x == 7) ? 180 : 90;
}


int MainWindow::determineHeight(int y)
{
    return(y == 0 || y == 7) ? 180 : 90;
}

void MainWindow::updateLastPos(int y, int rectHeight, int rectWidth)
{
    //Zur nächsten Zeile wechseln wenn Ende der Zeile erreicht ist
    if(y >= 7)
    {
        lastXPos = 0;
        lastYPos += rectHeight;
    }
    //Die nächste Zelle neben der gerade gezeichneten zeichnen
    else{
        lastXPos += rectWidth;
    }
}

void MainWindow::setOwner(int x, int y, int playerId)
{
    grid[x][y]->setBorder(this->getBrushColorFromPlayerId(playerId));
}

void MainWindow::setCurrentPlayer(int playerId)
{
    currentPlayerId = playerId;
    if(currentPlayerId == this->myPlayerId)
    {
        //Enable dice rolling button
        grid[2][3]->setIcon(QIcon(QPixmap(":/diceOn")));
        grid[2][3]->setEnabled(true);
        grid[1][3]->setText("  Your");
        grid[1][4]->setText("Turn!  ");
        grid[1][3]->setStyleSheet("color: white;");
        grid[1][4]->setStyleSheet("color: white;");
    }
    else
    {
        //Disable Buy buttons
        grid[5][2]->setVisible(false);
        grid[5][5]->setVisible(false);

        //Disable dice rolling button
        grid[2][3]->setIcon(QIcon(QPixmap(":/diceOff")));
        grid[2][3]->setEnabled(false);
        grid[1][3]->setText("Waiting");
        grid[1][3]->setStyleSheet("color: white;");
        grid[1][4]->setText("...    ");
        grid[1][4]->setStyleSheet("color: white;");

        //Disable Price Display
        grid[4][5]->setVisible(false);
    }
}

void MainWindow::displayRolledDice(int dice)
{
    //gewürfelte Augenzahl anzeigen
    grid[2][4]->setText(QString::number(dice));
    grid[2][4]->setStyleSheet("color: "+ getBrushColorFromPlayerId(currentPlayerId) + ";");
}

void MainWindow::moveCurrentPlayerToGridCoords(int x, int y)
{
    //Alten Kreis entfernen
    grid[player[currentPlayerId].positionX][player[currentPlayerId].positionY]->removeCircle();
    //Neuen Kreis hinzufügen
    grid[x][y]->addCircle(getBrushColorFromPlayerId(currentPlayerId), getPenColorFromPlayerId(currentPlayerId), currentPlayerId);
    //Player aktualisieren
    player[currentPlayerId].positionX = x;
    player[currentPlayerId].positionY = y;
}

void MainWindow::displayPurchasingUI(int price)
{
    if(currentPlayerId == this->myPlayerId)
    {
        //Preis der Immobilie anzeigen
        grid[4][5]->setText("Price:\n" + QString::number(price));
        grid[4][5]->setStyleSheet("color: #FFD954;");
        grid[4][5]->setVisible(true);

        //Kauf Knopf anzeigen
        grid[5][5]->setEnabled(true);
        grid[5][5]->setVisible(true);
        grid[5][5]->setText("Buy");
        grid[5][5]->setStyleSheet("background-color: #1AA530;");
        grid[5][5]->setAutoFillBackground(true);

        //Ablehnungsknopf anzeigen
        grid[5][2]->setEnabled(true);
        grid[5][2]->setVisible(true);
        grid[5][2]->setText("Decline");
        grid[5][2]->setStyleSheet("background-color: #B80900;");
        grid[5][2]->setAutoFillBackground(true);
    }
}

void MainWindow::setPurse(int purse, int playerId)
{
    for(int i = 1; i <= 6; i++)
    {
        if(player[i].playerId == playerId)
        {
            player[i].purse = purse;
        }
    }
    grid[3][4]->setText(QString::number(player[myPlayerId].purse));

    qInfo()<<"Player " << this->myPlayerId << " Purse: " << player[this->myPlayerId].purse;
}

QString MainWindow::getBrushColorFromPlayerId(int playerId)
{
    switch(playerId)
    {
    case 1:
        return "#9F150E";
    case 2:
        return "#019092";
    case 3:
        return "#FEE083";
    case 4:
        return "#C5E493";
    case 5:
        return "#D484A2";
    case 6:
        return "#164260";
    default:
        return "#ffffff";
    }
}

QString MainWindow::getPenColorFromPlayerId(int playerId)
{
    switch(playerId)
    {
    case 1:
        return "#4E0A07";
    case 2:
        return "#102432";
    case 3:
        return "#716950";
    case 4:
        return "#687B48";
    case 5:
        return "#77516C";
    case 6:
        return "#102432";
    default:
        return "#000000";
    }
}
