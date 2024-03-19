#include "gridcell.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>

GridCell::GridCell(QWidget *parent, int x, int y) : QPushButton(parent)
{
    this->x = x;
    this->y = y;
    this->drawCircleFlag = false;
    this->brushColor = "#000000";
}

GridCell::~GridCell()
{

}

//wenn ein Spieler ein Gebäude gekauft hat, bekommt es die Border in seiner Color
void GridCell::setBorder(QString color)
{
    this->setStyleSheet("border: 3px dashed " + color + ";");
}

void GridCell::setBrushColor(QString newBrushColor)
{
    this->brushColor = newBrushColor;
}

void GridCell::drawCircle()
{
        drawCircleFlag = true;
        //this->repaint(); // Trigger repainting of the widget
        update();
}

void GridCell::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event); // Call the base class implementation first

    if (drawCircleFlag) {
        QPainter painter(this);

        QPen pen(QColor(brushColor), 3);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QColor(brushColor)); // Set brush color
        painter.setPen(pen);
        int diameter = qMin(30, 30); // Circle diameter
        int xCenter = this->width() / 2; // X-coordinate of circle center
        int yCenter = this->height() / 2; // Y-coordinate of circle center
        painter.drawEllipse(xCenter - diameter / 2, yCenter - diameter / 2, diameter, diameter);
    }
}

