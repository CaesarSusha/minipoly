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

    void drawEmptyCell(int x, int y);
    void drawFreeParking(int x, int y );
    void drawBuilding(int x, int y, char direction);

    // determine card dimensions
    int determineWidth(int x);
    int determineHeight(int y);

    //save last position
    int lastXPos;
    int lastYPos;

    //screen size
    int width;
    int height;
    int boardSize;
};

#endif // MAINWINDOW_H
