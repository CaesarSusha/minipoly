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
    game = Game();
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

    //create new User
    int playerId = game.addPlayer(pSocket);

    //Show new User
    broadcastData("Player" + QString::number(playerId) + " joined.");


    //Debugging purpose
    //User 1 has bought a house
    // broadcastData("setOwner-2-3");
    // broadcastData("setOwner-16-3");
    // broadcastData("setOwner-23-3");
    // broadcastData("setOwner-9-3");
    //It is now Player 1s turn
    if(playerId == 2)
    {
        game.setCurrentPlayer(game.getNextPlayer());
        broadcastData("setCurrentPlayer-" + QString::number(game.getCurrentPlayer().getId()));
    }
    else
    {
    transmitData("setCurrentPlayer-" + QString::number(game.getCurrentPlayer().getId()) , pSocket);
    }
    transmitData("setPlayerId-" + QString::number(playerId) , pSocket);
    //game->addPlayer();
    //qInfo() << game->getCurrentPlayer().getId();
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
        //verstehe ich bei Gott nicht
        int rollResult = game.rollDice();
        broadcastData("setDice-" + QString::number(rollResult));
        // Trying to walk
        int position = game.MoveToNewPosition(rollResult);
        broadcastData("updatePosition-" + QString::number(game.getCurrentPlayer().getId()) + " -" + QString::number(position));
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

