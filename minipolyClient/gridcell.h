#ifndef GRIDCELL_H
#define GRIDCELL_H
#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QLabel>
#include <QPainter>

// Die Klasse erweitert den Pushbutton um eine x und y coordinate und einen state
class GridCell : public QPushButton
{
    Q_OBJECT
public:
    GridCell(QWidget* parent = 0, int x = 0, int y = 0); //maybe use a "problem" picture
    virtual ~GridCell();
    //Ownership
    void setBorder(QString color);
    int x;
    int y;
    void drawCircle();
    void paintEvent(QPaintEvent *event);
    void setBrushColor(QString newBrushColor);
    bool drawCircleFlag;
    QString brushColor;
};

#endif // GRIDCELL_H
