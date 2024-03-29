#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gridcell.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include "player.h"

// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();
    GridCell* grid[8][8];

    void initGrid();

    //screen size
    int width;
    int height;
    int boardSize;

    // determine rectangle dimensions
    int determineWidth(int x);
    int determineHeight(int y);

    //save last position
    int lastXPos;
    int lastYPos;
    void updateLastPos(int y, int rectHeight, int rectWidth);

    // server data handling
    void setOwner(int x, int y, int playerId);
    QString getBrushColorFromPlayerId(int playerId);
    QString getPenColorFromPlayerId(int playerId);
    void setCurrentPlayer(int playerId);
    void displayRolledDice(int dice);
    void moveCurrentPlayerToGridCoords(int x, int y);
    void setPurse(int purse, int playerId);

    int myPlayerId;
    int currentPlayerId;
    Player player[7];

    //virtual void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
