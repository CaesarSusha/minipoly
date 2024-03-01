#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gridcell.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();
    GridCell* grid[5][5];

    //screen size
    int width;
    int height;
    int boardSize;
};

#endif // MAINWINDOW_H
