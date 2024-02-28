#include "mainwindow.h"
#include "ui_mainwindow.h"

//MainWindow implementiert QMainWindow und Ui
MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
{
    //Der Socket öffnet localhost:8888
    //client.open(QUrl("ws://127.0.0.1:8888"));
    //Der Socket wird die handleIncomingMessages Funktion aufrufen wenn er eine Nachricht bekommt
    //connect(&client, &QWebSocket::textMessageReceived,this, &MainWindow::handleIncomingMessages);
    //Das User Interface wird vorbereitet
    //ui->setupUi(this);
    //Connect the editField to send content to server on Edit finished
    //connect(ui->freundFunk, &QLineEdit::textChanged, this, &MainWindow::sendFunk);
    //Connect the editField to send content to server on Edit finished
    //connect(ui->nameInput, &QLineEdit::textChanged, this, &MainWindow::sendName);
}



//Destruktor
// MainWindow::~MainWindow()
// {
//     delete ui;
//     client.close();
// }
