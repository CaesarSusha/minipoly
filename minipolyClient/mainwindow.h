#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>


// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
//     Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// public slots:
//     //Message-Handling von erhaltenen Nachrichten
//     void handleIncomingMessages(QString message);

//     //Sende den Funk zu dem Server
//     void sendFunk(QString message);
//     //Sende den Namen an den Server
//     void sendName(QString name);

// private:
//     //Das Fenster
//     Ui::MainWindow *ui;
//     //Der client socket für die Kommunikation mit dem Server
//     QWebSocket client;
//};

};
#endif // MAINWINDOW_H
