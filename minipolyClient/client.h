#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebsocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, QObject *parent = nullptr);
    ~Client();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnection();
    void onDisconnection();
    QString receiveData();
    void transmitData(QString data);

private:
    QWebSocket m_webSocket;

};

#endif // CLIENT_H
