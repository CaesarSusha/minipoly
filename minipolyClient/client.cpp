#include "client.h"

QT_USE_NAMESPACE

Client::Client(const QUrl &url, QObject *parent) : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnection);
    //connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);
    m_webSocket.open(url);
}

Client::~Client()
{
    //m_webSocket.close();

    //Client::closed();
}

void Client::onConnection()
{
    qInfo()<<"Connected to server";
}

void Client::onDisconnection()
{
    qInfo()<<"Disconnected from server";
}

QString Client::receiveData()
{
    qInfo()<<"Received data from serverito";
}

void Client::transmitData(QString data)
{
    qInfo()<<"Gave data to serveritto";
}
