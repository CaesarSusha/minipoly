#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_passDataButton = new QPushButton("Pass Data", this);
    connect(m_passDataButton, &QPushButton::clicked, this, &MainWindow::onPassDataButtonClicked);
    setCentralWidget(m_passDataButton);
}

void MainWindow::onPassDataButtonClicked()
{
    // Here you can define the data you want to transmit
    QString data = "Hello, server!";

    // Emit the passDataButtonClicked signal with the data
    emit passDataButtonClicked(data);
}
