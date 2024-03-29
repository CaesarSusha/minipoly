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
    qInfo() << "Created Server";
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
    qInfo()<<"New Connection:";

    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::handleReceivedData);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::onDisconnection);

    m_clients << pSocket;
    qInfo() << m_clients.length();
    qInfo()<<"socketConnected:"<< pSocket;

    // neuen Nutzer anlegen
    int playerId = game.addPlayer(pSocket);


    transmitData("setPlayerId-" + QString::number(playerId) , pSocket);

    //Neuen Nutzer anzeigen
    broadcastData("Player" + QString::number(playerId) + " joined.");
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
}


void Server::onDisconnection()
{
    qInfo()<<"Client disconnected";
}

void Server::handleReceivedData(QString data)
{
    qInfo()<<"Received data from client: " << data;
    bool successfulConvert;
    int clientCommand = data.toInt(&successfulConvert);
    if(game.getCurrentPlayer().getId() == -1 || game.getTurn() == -1)
    {
    return;
    }
    if(successfulConvert)
    {
        switch(clientCommand)
        {
            //Kauf ablehnen
            case 0:
            {
                if (game.getPhase() != 0)
                {
                    QString result = game.runGame(false);
                    QStringList  splitResult = result.split("%");
                    for(QString part : splitResult)
                    {
                        if(part != "")
                        {
                            broadcastData(part);
                        }
                    }
                }
                return;
            }
            //Kauf annehmen
            case 1:
            {
                if (game.getPhase() != 0)
                {
                    QString result = game.runGame(true);
                    QStringList  splitResult = result.split("%");
                    for(QString part : splitResult)
                    {
                        if(part != "")
                        {
                            broadcastData(part);
                        }
                    }
                }
                return;
            }
            //Würfeln
            case 2:
            {
                if(game.getPhase() == 0)
                {
                    QString result = game.runGame(false);
                    QStringList  splitResult = result.split("%");
                    for(QString part : splitResult)
                    {
                        if(part != "")
                        {
                            broadcastData(part);
                        }
                    }
                }
                return;
            }
            default:
                break;
        }
    }
    //Chatfunktion
    broadcastData(data);

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

