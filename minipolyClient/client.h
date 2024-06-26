#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets>
#include "mainwindow.h"

class Client : public QObject
{
    public:
        struct coordinates {
            int x;
            int y;
        };

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
    coordinates convertIdToCoordinates(int gridcellId);

private:
    QWebSocket m_webSocket;
    MainWindow m_mainWindow;    
    bool debug;
};

#endif // CLIENT_H
