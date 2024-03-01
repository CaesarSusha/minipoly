#include "mainwindow.h"
#include "gridcell.h"
//#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) //, ui(new Ui::MainWindow)
{
    //QPixmap pixmap(":/assets/buildings/train.png");
    this->width = 1920;
    this->height = 1080;
    this->boardSize = 900;
    this->setGeometry(0, 0, width, height);

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y ++)
        {
        this->grid[x][y] = new GridCell(this, x, y);
        this->grid[x][y]->setGeometry(QRect((width-boardSize)/2+(x*180), (height-boardSize)/4+(y*180),180,180));
        this->grid[x][y]->setIcon(QIcon(QPixmap(":/assets/buildings/freeparking.png")));
        this->grid[x][y]->setIconSize(QSize(50, 50));
        //this->grid[x][y]->setEnabled(false);
        //Das linke Spielfeld wird bei klicken die selectShips Funktion aufrufen
        //connect(grid[x][y], SIGNAL(clicked()),this, SLOT(selectShips()));
        }
    }



}


//     // Create a QWidget to contain the grid layout
//     QWidget *centralWidget = new QWidget(this);
//     setCentralWidget(centralWidget);

//     //Das User Interface wird vorbereitet
//     //ui->setupUi(this);

//     // QWidget *centralWidget = new QWidget(this);
//     // setCentralWidget(centralWidget);

//     // Create the grid layout for the PNG images
//     QGridLayout *m_grid = new QGridLayout(centralWidget);
//     m_grid->setSpacing(10); // Add spacing between cells

//     const int gridSize = 5;
//     const int cellSize = 180;

//     // Load the PNG image
//     QPixmap pixmap(":/b_f_freeparking");

//     for (int row = 0; row < gridSize; ++row) {
//         for (int col = 0; col < gridSize; ++col) {
//             QLabel *label = new QLabel(this);
//             label->setPixmap(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
//             label->setFixedSize(cellSize, cellSize); // Set fixed size for the label
//             label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//             m_grid->addWidget(label, row, col); // Add the label to the grid layout
//         }
//     }

//     // Add some spacing around the grid layout
//     m_grid->setContentsMargins(20, 20, 20, 20); // Set margins (left, top, right, bottom)








    // // Create the central widget
    // QWidget *centralWidget = new QWidget(this);
    // setCentralWidget(centralWidget);

    // // Create the grid layout
    // grid = new QGridLayout(centralWidget);

    // // Set the minimum width of column 0
    // grid->setColumnMinimumWidth(0, 500);
    // // Set the minimum height of row 0
    // grid->setRowMinimumHeight(0, 500);


    // // Create the pass data button
    // QPushButton *button1 = new QPushButton("Pass Data Button 1", centralWidget);
    // QPushButton *button2 = new QPushButton("Pass Data Button 1", centralWidget);

    // // Connect the button's clicked signal to the slot
    // connect(m_passDataButton, &QPushButton::clicked, this, &MainWindow::onPassDataButtonClicked);
    // //setCentralWidget(m_passDataButton);


    // // Add the button to the grid layout
    // grid->addWidget(button1, 0, 0);
    // grid->addWidget(button2, 0, 1);

// void MainWindow::onPassDataButtonClicked()
// {
//     // Here you can define the data you want to transmit
//     QString data = "Hello, server!";

//     // Emit the passDataButtonClicked signal with the data
//     emit passDataButtonClicked(data);
// }
