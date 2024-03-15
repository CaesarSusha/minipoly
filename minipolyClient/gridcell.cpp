#include "gridcell.h"
#include <QHBoxLayout>
#include <QPushButton>

GridCell::GridCell(QWidget *parent, int x, int y) : QPushButton(parent)
{
    this->x = x;
    this->y = y;
}

GridCell::~GridCell()
{

}

//wenn ein Spieler ein Gebäude gekauft hat, bekommt es die Border in seiner Color
void GridCell::setBorder(QString color)
{
    this->setStyleSheet("border: 3px dashed " + color + ";");
}
