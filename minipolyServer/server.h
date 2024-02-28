#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server: public QObject
{
    Q_OBJECT

public:
    static Server *getInstance();
    ~Server();


Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnection();
    void onDisconnection();
    void handleReceivedData(QString data);
    void transmitData(QString data);

private:
    //Singleton Server Instanz
    static Server *instance;
    //quint16 = short
    explicit Server(quint16 port);
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket*> m_clients;


};
#endif // SERVER_H
