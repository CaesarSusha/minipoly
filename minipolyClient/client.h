#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets>
#include "mainwindow.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, QObject *parent = nullptr);
    ~Client();

Q_SIGNALS:
    void closed();

signals:
    void passDataButtonClicked(const QString &data);

private Q_SLOTS:
    void onConnection();
    void onDisconnection();
    void handleReceivedData(QString data);
    void transmitData(QString data);

private:
    QWebSocket m_webSocket;
    MainWindow m_mainWindow;
};

#endif // CLIENT_H
