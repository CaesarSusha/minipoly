#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gridcell.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include "player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    GridCell* grid[8][8];

    //Spielerdaten
    Player player[7];
    int myPlayerId;
    int currentPlayerId;

    //Serverdatenverarbeitung
    void setCurrentPlayer(int playerId);
    void displayRolledDice(int dice);
    void moveCurrentPlayerToGridCoords(int x, int y);
    void setOwner(int x, int y, int playerId);
    void setPurse(int purse, int playerId);

    //Getter für Spielerfarben
    QString getBrushColorFromPlayerId(int playerId);
    QString getPenColorFromPlayerId(int playerId);

    //Preis anzeigen
    void displayPurchasingUI(int price);

private:

    //Spielbeginn
    void startGame();
    void initGrid();

    //Bildschirmgröße
    int width;
    int height;
    int boardSize;

    //Willkommensbildschirm
    QLabel* titleLabel;
    QPushButton* startGameButton;

    //Abmessungen der Rechtecke bestimmen
    int determineWidth(int x);
    int determineHeight(int y);

    //Letzte Position speichern
    int lastXPos;
    int lastYPos;
    void updateLastPos(int y, int rectHeight, int rectWidth);
};

#endif // MAINWINDOW_H
