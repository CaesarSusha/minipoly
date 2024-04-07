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

    void initGrid();

    //Bildschirmgröße
    int width;
    int height;
    int boardSize;

    //Abmessungen der Rechtecke bestimmen
    int determineWidth(int x);
    int determineHeight(int y);

    //Letzte Position speichern
    int lastXPos;
    int lastYPos;
    void updateLastPos(int y, int rectHeight, int rectWidth);

    //Serverdatenverarbeitung
    void setCurrentPlayer(int playerId);
    void displayRolledDice(int dice);
    void moveCurrentPlayerToGridCoords(int x, int y);
    void setPurse(int purse, int playerId);
    void setOwner(int x, int y, int playerId);
    QString getBrushColorFromPlayerId(int playerId);
    QString getPenColorFromPlayerId(int playerId);

    //Spielerdaten
    Player player[7];
    int myPlayerId;
    int currentPlayerId;

    //Preis anzeigen
    void setDisplayedPrice(int price);
};

#endif // MAINWINDOW_H
