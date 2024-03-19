#ifndef GRIDCELL_H
#define GRIDCELL_H
#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QLabel>
#include <QPainter>
#include <QVector>

struct CircleProperties {
    QString brushColor;
    QPoint circlePosition;
};

// Die Klasse erweitert den Pushbutton um eine x und y coordinate und einen state
class GridCell : public QPushButton
{
    Q_OBJECT
public:
    GridCell(QWidget* parent = 0, int x = 0, int y = 0); //maybe use a "problem" picture
    ~GridCell();

    //Ownership
    void setBorder(QString color);
    void setBrushColor(QString newBrushColor);
    void addCircle(const QString &brushColor);
    void paintEvent(QPaintEvent *event) override;
    bool drawCircleFlag;

private:
    int x, y;

    QString brushColor;
    QVector<CircleProperties> circles;
    QVector<QPoint> iconPositions;

    void calculateIconPositions();
};

#endif // GRIDCELL_H
