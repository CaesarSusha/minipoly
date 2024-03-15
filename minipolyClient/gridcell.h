#ifndef GRIDCELL_H
#define GRIDCELL_H
#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QLabel>

// Die Klasse erweitert den Pushbutton um eine x und y coordinate und einen state
class GridCell : public QPushButton
{
    Q_OBJECT
public:
    GridCell(QWidget* parent = 0, int x = 0, int y = 0); //maybe use a "problem" picture
    virtual ~GridCell();
    int x;
    int y;

};

#endif // GRIDCELL_H
