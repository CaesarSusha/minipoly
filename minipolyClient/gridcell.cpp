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

//Wenn ein Spieler ein Gebäude gekauft hat, bekommt es die Border in seiner Color
void GridCell::setBorder(QString color)
{
    this->setStyleSheet("border: 4px solid " + color + ";");
}

void GridCell::setBrushColor(QString newBrushColor)
{
    this->brushColor = newBrushColor;
}

void GridCell::setPenColor(QString newPenColor)
{
    this->penColor = newPenColor;
}


void GridCell::calculateIconPositions()
{
    //Gesamtzahl der Kreise in einer Zeile/Spalte
    int totalCirclesX;
    int totalCirclesY;
    if(this->width() > this->height())
    {
        totalCirclesX = 3;
        totalCirclesY = 2;
    }
    else
    {
        totalCirclesX = 2;
        totalCirclesY = 3;
    }

    //Abstand zwischen den Kreisen berechnen
    int spaceBetweenCirclesX = this->width() / (totalCirclesX + 1);
    int spaceBetweenCirclesY = this->height() / (totalCirclesY + 1);

    //Position für jeden Kreis berechnen
    for (int i = 1; i <= totalCirclesX; ++i)
    {
        for (int j = 1; j <= totalCirclesY; ++j)
        {

            //x- und y-Position des Kreismittelpunkts berechnen
            int xPos = i * spaceBetweenCirclesX;
            int yPos = j * spaceBetweenCirclesY;

            iconPositions.push_back(QPoint(xPos, yPos));
        }
    }
}

void GridCell::addCircle(const QString &brushColor, const QString &penColor, const int player)
{
    calculateIconPositions();

    CircleProperties circle;
    circle.brushColor = brushColor;
    circle.penColor = penColor;

    //Zuweisen von Kreispositionen aus den berechneten Positionen
    circle.circlePosition = iconPositions[player-1];
    circles.append(circle);

    this->drawCircleFlag = true;

    //Erneutes Zeichnen des Widget auslösen
    update();
}

void GridCell::removeCircle()

{
    circles.removeFirst();
}

void GridCell::paintEvent(QPaintEvent *event)
{
    //Zuerst die Implementierung der Basisklasse aufrufen
    QPushButton::paintEvent(event);
    QPainter painter(this);

    for (const auto &circle : circles)
    {
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen(QColor(circle.penColor), 3);
        painter.setPen(pen);
        painter.setBrush(QColor(circle.brushColor));

        int diameter = qMin(20, 20);
        QPoint circlePosition = circle.circlePosition;
        painter.drawEllipse(circlePosition.x() - diameter / 2, circlePosition.y() - diameter / 2, diameter, diameter);
    }
}
