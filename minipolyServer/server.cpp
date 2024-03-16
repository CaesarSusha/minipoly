#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QDateTime>

QT_USE_NAMESPACE

Server* Server::instance = nullptr;

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
    broadcastData("Player" + QString::number(m_clients.length()) + " joined.");

    //Debugging purpose
    //User 1 has bought a house
    // broadcastData("setOwner-2-3");
    // broadcastData("setOwner-16-3");
    // broadcastData("setOwner-23-3");
    // broadcastData("setOwner-9-3");
    //It is now Player 1s turn
    broadcastData("setCurrentPlayer-1");
    transmitData("setPlayerId-" + QString::number(m_clients.length()) , m_clients.at(m_clients.length()-1));
}


void Server::onDisconnection()
{
    qInfo()<<"Client disconnected";
}

void Server::handleReceivedData(QString data)
{
    qInfo()<<"Received data from client: " << data;
    if (data == "3")
    {
        int rollResult = this->game->rollDice(6);
        broadcastData("setDice-" + QString::number(rollResult));
        // walk
    }
}

void Server::broadcastData(QString data)
{
    qInfo()<<"Broadcasting data: " << data;
    for (QWebSocket *client : qAsConst(m_clients))
    {
        client->sendTextMessage(data);
    }
}

void Server::transmitData(QString data, QWebSocket *client)
{
    if (!client) {
        qWarning() << "Invalid client specified.";
        return;
    }

    qInfo() << "Passing data to client:" << data;
    client->sendTextMessage(data);
}

