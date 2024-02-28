#include "server.h"
#include <QDateTime>
#include <QtWebSockets>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"


QT_USE_NAMESPACE

Server* Server::instance =nullptr;

Server *Server::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Server(3000);
    }
    return instance;
}

Server::Server(quint16 port) :
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Server"), QWebSocketServer::NonSecureMode,this))
{
    qInfo() << "forced server into existence";
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &Server::onConnection);
    }
}

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::onConnection()
{
    qInfo()<<"nouvelle connecthione:";

}


void Server::onDisconnection()
{

}

QString Server::receiveData()
{
    return nullptr;
}


void Server::transmitData(QString data)
{

}

