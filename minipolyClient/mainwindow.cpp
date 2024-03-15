#include "mainwindow.h"
#include "gridcell.h"
//#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->width = 1920;
    this->height = 1080;
    this->boardSize = 900;
    this->setGeometry(0, 0, width, height);

    this->lastXPos = 0;
    this->lastYPos = 0;

    initGrid();
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

            if (grid[x][y]->icon().isNull())
            {
                grid[x][y]->setEnabled(false);
            }
            qInfo() << "hallo " << grid[x][y]->icon();
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

