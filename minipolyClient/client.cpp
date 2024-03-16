#include "client.h"

QT_USE_NAMESPACE

Client::Client(const QUrl &url, QObject *parent) : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnection);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);


    // Connect button click event to connectToServer slot
    //connect(&m_mainWindow, &MainWindow::passDataButtonClicked, this, [this](const QString &data) { transmitData(data);});
    m_webSocket.open(url);

    // Show the main window when the client is started
    m_mainWindow.show();
}

Client::~Client()
{
    //m_webSocket.close();

    //Client::closed();
}

void Client::onConnection()
{
    qInfo()<<"Connected to server";

    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::handleReceivedData);

    //transmit success
    transmitData("I want to connect to you bro");
}

void Client::onDisconnection()
{
    qInfo()<<"Disconnected from server";
}

void Client::handleReceivedData(QString data)
{
    qInfo()<<"Received data from server: " << data;
    QStringList  splitData = data.split("-");
    if(splitData[0] == "changeOwner")
    {
        int gridcellId = splitData[1].toInt();
        Client::coordinates coords = convertIdToCoordinates(gridcellId);
        int playerId = splitData[2].toInt();
        m_mainWindow.changeOwner(coords.x, coords.y, playerId);
    }
}

void Client::transmitData(QString data)
{
    qInfo()<<"Passing data to server:" << data;
    m_webSocket.sendTextMessage(data);
}

Client::coordinates Client::convertIdToCoordinates(int gridcellId)
{
    coordinates coords;
    switch(gridcellId)
    {
    case 2:
        coords.x = 5;
        coords.y = 0;
        break;
    default:
        coords.x = 0;
        coords.y = 0;
        break;
    }
    return coords;
}
