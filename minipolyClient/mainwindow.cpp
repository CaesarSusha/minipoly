#include "mainwindow.h"
#include "gridcell.h"
//#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) //, ui(new Ui::MainWindow)
{
    this->lastXPos = 0;
    this->lastYPos = 0;

    //QPixmap pixmap(":/assets/buildings/train.png");
    this->width = 1920;
    this->height = 1080;
    this->boardSize = 900;
    this->setGeometry(0, 0, width, height);

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            this->grid[x][y] = new GridCell(this, x, y);
            this->drawBuilding(x,y,'d');
        //this->grid[x][y]->setGeometry(QRect((width-boardSize)/2+(x*180), (height-boardSize)/4+(y*180),180,180));

        //this->grid[x][y]->setEnabled(false);

        //connect(grid[x][y], SIGNAL(clicked()),this, SLOT(selectShips()));

        //Corners
            /*
        if (x == 0)
        {
            if(y == 0 || y == 7)
            {
                drawFreeParking(x, y);
            }
        }
        if (x == 7)
        {
            if(y == 0 || y == 7)
            {
                drawFreeParking(x, y);
            }
        }


        if(x > 0 && x < 7)
        {
            //Middle
            if(y > 0 && y < 7)
            {
                drawEmptyCell(x, y);
            }
            else
            {
                drawBuilding(x ,y, 'd');
            }

        }
        */


    }

}

}
void MainWindow::drawEmptyCell(int x, int y)
{
    grid[x][y]->setEnabled(false);
    grid[x][y]->setGeometry(QRect((width-boardSize)/2+(x*180), (height-boardSize)/4+(y*180),180,180));
}

void MainWindow::drawFreeParking(int x, int y)
{
    grid[x][y]->setEnabled(false);
    grid[x][y]->setGeometry(QRect((width-boardSize)/2+(x*180), (height-boardSize)/4+(y*180),180,180));
    grid[x][y]->setIcon(QIcon(QPixmap(":/assets/buildings/freeparking.png")));
    //grid[x][y]->setIconSize(QSize(180, 180));
}

void MainWindow::drawBuilding(int x, int y, char direction)
{
    int rectWidth = determineWidth(y);
    int rectHeight = determineHeight(x);
    int boardStartX = width-boardSize/2;
    int boardStartY = height-boardSize/4;
    grid[x][y]->setGeometry(QRect(0+(lastXPos), 0 +(lastYPos), rectWidth, rectHeight));
    //grid[x][y]->setText(QString(x) + '/' + QString(y));
    //grid[x][y]->setIconSize(QSize(500, 500));
    //following coud be outsourced to new function updateLastPos
    if(y >= 7)
    {
        lastXPos = 0;
        lastYPos += rectHeight;
    }
    else{
        lastXPos += rectWidth;
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

