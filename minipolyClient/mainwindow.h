#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gridcell.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <vector>

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
    QString getColorFromPlayerId(int playerId);
    void setCurrentPlayer(int playerId);
    void displayRolledDice(int dice);

    int myPlayerId;
    int currentPlayerId;


};

#endif // MAINWINDOW_H
