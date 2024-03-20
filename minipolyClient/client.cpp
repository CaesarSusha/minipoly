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


    connect(m_mainWindow.grid[5][3], &QPushButton::clicked, this, [=]() {transmitData("2");});

}

void Client::onDisconnection()
{
    qInfo()<<"Disconnected from server";
}

void Client::handleReceivedData(QString data)
{
    qInfo()<<"Received data from server: " << data;
    QStringList  splitData = data.split("-");

    if(splitData[0] == "setPlayerId")
    {
        m_mainWindow.myPlayerId = splitData[1].toInt();
        qInfo() << "myPlayerId: " << m_mainWindow.myPlayerId;
    }

    if(splitData[0] == "setOwner")
    {
        int gridcellId = splitData[1].toInt();
        Client::coordinates coords = convertIdToCoordinates(gridcellId);
        int playerId = splitData[2].toInt();
        m_mainWindow.setOwner(coords.x, coords.y, playerId);
    }

    if(splitData[0] == "setCurrentPlayer")
    {
        m_mainWindow.setCurrentPlayer(splitData[1].toInt());
    }

    if(splitData[0] == "setDice")
    {
        m_mainWindow.displayRolledDice(splitData[1].toInt());
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

    // Map gridcellId to coordinates
    static const std::map<int, coordinates> gridcellCoordinates = {
        {0, {7, 0}}, {1, {6, 0}}, {2, {5, 0}}, {3, {4, 0}}, {4, {3, 0}}, {5, {2, 0}}, {6, {1, 0}},
        {7, {0, 0}}, {8, {0, 1}}, {9, {0, 2}}, {10, {0, 3}}, {11, {0, 4}}, {12, {0, 5}}, {13, {0, 6}},
        {14, {0, 7}}, {15, {1, 7}}, {16, {2, 7}}, {17, {3, 7}}, {18, {4, 7}}, {19, {5, 7}}, {20, {6, 7}},
        {21, {7, 7}}, {22, {7, 6}}, {23, {7, 5}}, {24, {7, 4}}, {25, {7, 3}}, {26, {7, 2}}, {27, {7, 1}}
        // Add more mappings as needed
    };

    // Find the coordinates for the given gridcellId
    auto it = gridcellCoordinates.find(gridcellId);
    if (it != gridcellCoordinates.end()) {
        coords = it->second;
    }
    else
    {
        // Handle invalid gridcellId
        coords.x = -1;
        coords.y = -1;
    }
    return coords;
}

Client::coordinates Client::manualConvertIdToCoordinates(int gridcellId)
{
    //see mockup
    coordinates coords;
    switch(gridcellId)
    {
    case 0:
        coords.x = 7;
        coords.y = 0;
        break;
    case 1:
        coords.x = 6;
        coords.y = 0;
        break;
    case 2:
        coords.x = 5;
        coords.y = 0;
        break;
    case 3:
        coords.x = 4;
        coords.y = 0;
        break;
    case 4:
        coords.x = 3;
        coords.y = 0;
        break;
    case 5:
        coords.x = 2;
        coords.y = 0;
        break;
    case 6:
        coords.x = 1;
        coords.y = 0;
        break;
    case 7:
        coords.x = 0;
        coords.y = 0;
        break;

    case 8:
        coords.x = 0;
        coords.y = 1;
        break;
    case 9:
        coords.x = 0;
        coords.y = 2;
        break;
    case 10:
        coords.x = 0;
        coords.y = 3;
        break;
    case 11:
        coords.x = 0;
        coords.y = 4;
        break;
    case 12:
        coords.x = 0;
        coords.y = 5;
        break;
    case 13:
        coords.x = 0;
        coords.y = 6;
        break;
    case 14:
        coords.x = 0;
        coords.y = 7;
        break;

    case 15:
        coords.x = 1;
        coords.y = 7;
        break;
    case 16:
        coords.x = 2;
        coords.y = 7;
        break;
    case 17:
        coords.x = 3;
        coords.y = 7;
        break;
    case 18:
        coords.x = 4;
        coords.y = 7;
        break;
    case 19:
        coords.x = 5;
        coords.y = 7;
        break;
    case 20:
        coords.x = 6;
        coords.y = 7;
        break;
    case 21:
        coords.x = 7;
        coords.y = 7;
        break;

    case 22:
        coords.x = 7;
        coords.y = 6;
        break;
    case 23:
        coords.x = 7;
        coords.y = 5;
        break;
    case 24:
        coords.x = 7;
        coords.y = 4;
        break;
    case 25:
        coords.x = 7;
        coords.y = 3;
        break;
    case 26:
        coords.x = 7;
        coords.y = 2;
        break;
    case 27:
        coords.x = 7;
        coords.y = 1;
        break;

    default:
        coords.x = -1;
        coords.y = -1;
        break;
    }
    return coords;
}
