#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QDateTime>

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

    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::handleReceivedData);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::onDisconnection);

    m_clients << pSocket;
    qInfo() << m_clients.length();
    qInfo()<<"socketConnected:"<< pSocket;

    //Show new User
    transmitData("A user joined.");
}


void Server::onDisconnection()
{
    qInfo()<<"Client disconnected";
}

void Server::handleReceivedData(QString data)
{
    qInfo()<<"Received data from client: " << data;
    transmitData("i am the server. I got your data, client.");
}

void Server::transmitData(QString data)
{
    qInfo()<<"Passing data to client: " << data;
    for (QWebSocket *client : qAsConst(m_clients))
    {
        client->sendTextMessage(data);
    }
}

