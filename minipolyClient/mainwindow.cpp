#include "mainwindow.h"
#include "gridcell.h"
//#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    //int playerIconWidth = 100;
    //int playerIconWidth = 100;

    this->width = 1920;
    this->height = 1080;
    this->boardSize = 900;
    this->setGeometry(0, 0, width, height);

    this->lastXPos = 0;
    this->lastYPos = 0;

    initGrid();
    grid[5][3]->setIcon(QIcon(QPixmap(":/dice")));
    //grid[5][3]->setStyleSheet("color: "+ getColorFromPlayerId(currentPlayerId) + ";");




}

void MainWindow::initGrid()
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            this->grid[x][y] = new GridCell(this, x, y);

            int rectWidth = determineWidth(y);
            int rectHeight = determineHeight(x);
            int boardStartX = (width-boardSize)/2;
            int boardStartY = (height-boardSize)/4;
            grid[x][y]->setGeometry(QRect(boardStartX +(lastXPos), boardStartY +(lastYPos), rectWidth, rectHeight));

            QString iconPath = ":/" + QString::number(x) + QString::number(y);
            grid[x][y]->setIcon(QIcon(QPixmap(iconPath)));
            grid[x][y]->setIconSize(QSize(rectWidth, rectHeight));




            //disable buttons in the middle
            if (grid[x][y]->icon().isNull())
            {
                grid[x][y]->setFlat(true);
                grid[x][y]->setEnabled(false);
            }
            else
            {
                //grid[x][y]->drawCircle();
                grid[x][y]->drawCircleFlag = false;
            }

            //qInfo() << "hallo " << grid[x][y]->icon();
            updateLastPos(y, rectHeight, rectWidth);

            //grid[x][y]->setEnabled(false);
            //grid[x][y]->setBorder("red");
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
    if(y >= 7)
    {
        lastXPos = 0;
        lastYPos += rectHeight;
    }
    else{
        lastXPos += rectWidth;
    }
}

void MainWindow::setOwner(int x, int y, int playerId)
{
    grid[x][y]->setBorder(this->getColorFromPlayerId(playerId));
}

void MainWindow::setCurrentPlayer(int playerId)
{
    currentPlayerId = playerId;
    if(currentPlayerId == this->myPlayerId)
    {
        grid[5][3]->setEnabled(true);
        grid[4][3]->setText("Your Turn!");
    }
    else
    {
        grid[5][3]->setEnabled(false);
        grid[4][3]->setText("Waiting...");
    }
}

void MainWindow::displayRolledDice(int dice)
{
    grid[5][4]->setText(QString::number(dice));
    grid[5][4]->setStyleSheet("color: "+ getColorFromPlayerId(currentPlayerId) + ";");
}

void MainWindow::moveCurrentPlayerToGridCoords(int x, int y)
{
    //draw a circle on gridcellId with the currentplayer color
    //grid[5][3]->setStyleSheet("color: "+ getColorFromPlayerId(currentPlayerId) + ";");
    //grid[x][y]->setBrushColor(getColorFromPlayerId(currentPlayerId));
    //grid[x][y]->setPlayerIconPosition(currentPlayerId);
    //grid[x][y]->drawCircleFlag = true;

    //TEST
    grid[0][2]->addCircle(getColorFromPlayerId(1), 1);
    grid[0][2]->addCircle(getColorFromPlayerId(2), 2);
    grid[0][2]->addCircle(getColorFromPlayerId(3), 3);
    grid[0][2]->addCircle(getColorFromPlayerId(4), 4);
    grid[0][2]->addCircle(getColorFromPlayerId(5), 5);
    grid[0][2]->addCircle(getColorFromPlayerId(6), 6);


    grid[3][0]->addCircle(getColorFromPlayerId(1), 1);
    grid[3][0]->addCircle(getColorFromPlayerId(2), 2);
    grid[3][0]->addCircle(getColorFromPlayerId(3), 3);
    grid[3][0]->addCircle(getColorFromPlayerId(4), 4);
    grid[3][0]->addCircle(getColorFromPlayerId(5), 5);
    grid[3][0]->addCircle(getColorFromPlayerId(6), 6);



}

QString MainWindow::getColorFromPlayerId(int id)
{
    switch(id)
    {
    case 1:
        return "#ff0000";
    case 2:
        return "#0000ff";
    case 3:
        return "#00ff00";
    case 4:
        return "#ffff00";
    case 5:
        return "#00ffff";
    case 6:
        return "#ff00ff";
    default:
        return "#ffffff";
    }
}

