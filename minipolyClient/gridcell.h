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
    QString penColor;
    QPoint circlePosition;
};

//Die Klasse erweitert den Pushbutton um eine x und y Koordinate und einen Zustand
class GridCell : public QPushButton
{
    Q_OBJECT

public:
    GridCell(QWidget* parent = 0, int x = 0, int y = 0);
    ~GridCell();

    //Besitz darstellen
    void setBorder(QString color);

    //Spielfiguren darstellen
    void setBrushColor(QString newBrushColor);
    void setPenColor(QString newPenColor);
    void addCircle(const QString &brushColor, const QString &penColor, const int player);
    void removeCircle();
    void paintEvent(QPaintEvent *event) override;
    bool drawCircleFlag;

private:
    int x, y;
    QString brushColor;
    QString penColor;
    QVector<CircleProperties> circles;
    QVector<QPoint> iconPositions;
    void calculateIconPositions();
};

#endif // GRIDCELL_H
