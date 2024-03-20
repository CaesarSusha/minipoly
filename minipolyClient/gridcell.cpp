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
    this->setStyleSheet("border: 4px solid " + color + ";");
}

void GridCell::setBrushColor(QString newBrushColor)
{
    this->brushColor = newBrushColor;
}

void GridCell::calculateIconPositions()
{
    // Total number of circles in a row/column
    int totalCircles = 3;

    // Calculate the space between circles
    int spaceBetweenCirclesX = this->width() / (totalCircles + 1);
    int spaceBetweenCirclesY = this->height() / (totalCircles + 1);

    // Calculate the positions for each circle
    for (int i = 1; i <= totalCircles; ++i) {
        for (int j = 1; j <= totalCircles; ++j) {
            // Calculate the x and y positions of the circle center
            int xPos = i * spaceBetweenCirclesX;
            int yPos = j * spaceBetweenCirclesY;

            iconPositions.push_back(QPoint(xPos, yPos));
        }
    }
}

void GridCell::addCircle(const QString &brushColor)
{
    calculateIconPositions();

    CircleProperties circle;
    circle.brushColor = brushColor;

    // Assign circle positions from the calculated positions
    for (const auto &pos : iconPositions)
    {
        circle.circlePosition = pos;
        circles.append(circle);
    }
    this->drawCircleFlag = true;
    update(); // Trigger repainting of the widget
}

void GridCell::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event); // Call the base class implementation first

    QPainter painter(this);

    for (const auto &circle : circles)
    {
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen(QColor(circle.brushColor), 3);
        painter.setPen(pen);
        painter.setBrush(QColor(circle.brushColor));

        int diameter = qMin(20, 20); // Circle diameter
        QPoint circlePosition = circle.circlePosition;
        painter.drawEllipse(circlePosition.x() - diameter / 2, circlePosition.y() - diameter / 2, diameter, diameter);
    }
}









// OLD CODE cus ima horder
// void GridCell::drawCircle(QString brushColor, int currentPlayerId)
// {
//     setBrushColor(brushColor);
//     setPlayerIconPosition(currentPlayerId);
//     qInfo() << "currentPlayerId: " << currentPlayerId;
//     drawCircleFlag = true;
//     update();
// }

// void GridCell::paintEvent(QPaintEvent *event)
// {
//     QPushButton::paintEvent(event); // Call the base class implementation first

//     if (drawCircleFlag) {
//         QPainter painter(this);

//         QPen pen(QColor(brushColor), 3);
//         painter.setRenderHint(QPainter::Antialiasing);
//         painter.setBrush(QColor(brushColor)); // Set brush color
//         painter.setPen(pen);
//         int diameter = qMin(20, 20); // Circle diameter

//         int xCenter = this->width() / iconPosition; // X-coordinate of circle center
//         int yCenter = this->height() / iconPosition; // Y-coordinate of circle center
//         painter.drawEllipse(xCenter - diameter / 2, yCenter - diameter / 2, diameter, diameter);
//     }
// }

