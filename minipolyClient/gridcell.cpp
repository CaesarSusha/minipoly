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
