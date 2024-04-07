#include "client.h"

QT_USE_NAMESPACE

Client::Client(const QUrl &url, QObject *parent) : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnection);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);

    m_webSocket.open(url);

    //Anzeige des Hauptfensters beim Start des Clients
    m_mainWindow.show();

    //Zum testen: Selbstspielender Modus
    debug = false;
}

Client::~Client()
{

}

void Client::onConnection()
{
    qInfo()<<"Connected to server";

    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::handleReceivedData);

    //Würfel Knopf
    connect(m_mainWindow.grid[2][3], &QPushButton::clicked, this, [=]() {transmitData("2");});
    //Kauf ablehnen Knopf
    connect(m_mainWindow.grid[5][2], &QPushButton::clicked, this, [=]() {transmitData("0");});
    //Kauf vornehmen Knopf
    connect(m_mainWindow.grid[5][5], &QPushButton::clicked, this, [=]() {transmitData("1");});
}

void Client::onDisconnection()
{
    qInfo()<<"Disconnected from server";
}

void Client::handleReceivedData(QString data)
{
    //Hier werden die Commandos vom Server bearbeitet und in der UI dargestellt
    qInfo()<<"Received data from server: " << data;
    QStringList  splitData = data.split("_");

    //Meine Spielfigur und die der bereits hinzugefügten Spieler setzen
    if(splitData[0] == "setPlayerId")
    {
        m_mainWindow.myPlayerId = splitData[1].toInt();
        qInfo() << "myPlayerId: " << m_mainWindow.myPlayerId;
        for (int i = 1; i < m_mainWindow.myPlayerId; i++)
        {
            m_mainWindow.grid[7][0]->addCircle(m_mainWindow.getBrushColorFromPlayerId(i), m_mainWindow.getPenColorFromPlayerId(i), i);
        }
    }

    //Spielfigur der neu dazugekommenen Spieler setzen
    if(data.left(6) == "Player" && data.right(8) == " joined.")
    {
        bool successfulConvert = false;
        int newPlayer = data.mid(6,1).toInt(&successfulConvert);
        if(successfulConvert)
        {
            m_mainWindow.grid[7][0]->addCircle(m_mainWindow.getBrushColorFromPlayerId(newPlayer), m_mainWindow.getPenColorFromPlayerId(newPlayer), newPlayer);
        }
    }

    //Besitz einer Karte darstellen
    if(splitData[0] == "setOwner")
    {
        int gridcellId = splitData[1].toInt();
        Client::coordinates coords = convertIdToCoordinates(gridcellId);
        int playerId = splitData[2].toInt();
        m_mainWindow.setOwner(coords.x, coords.y, playerId);
    }

    //Spieler, der an der Reihe ist, setzen
    if(splitData[0] == "setCurrentPlayer")
    {
        m_mainWindow.setCurrentPlayer(splitData[1].toInt());

        //Zum testen: Selbstspielender Modus
        if(debug && m_mainWindow.currentPlayerId == m_mainWindow.myPlayerId)
        {
            transmitData("2");
        }
    }

    //Augenzahl des Würfels setzen
    if(splitData[0] == "setDice")
    {
        m_mainWindow.displayRolledDice(splitData[1].toInt());

        //Zum testen: Selbstspielender Modus
        debug = false;
    }

    //Spielfigur bewegen
    if (splitData[0] == "moveCurrentPlayerToGridcellId")
    {        
        int gridcellId = splitData[1].toInt();
        Client::coordinates coords = convertIdToCoordinates(gridcellId);
        m_mainWindow.moveCurrentPlayerToGridCoords(coords.x, coords.y);
        m_mainWindow.update();

        //Zum testen: Selbstspielender Modus
        if(debug && m_mainWindow.currentPlayerId == m_mainWindow.myPlayerId)
        {
            transmitData("1");
        }
    }

    //Vermögen setzen
    if (splitData[0] == "setPurse")
    {
        int purse = splitData[1].toInt();
        int playerId = splitData[2].toInt();
        m_mainWindow.setPurse(purse, playerId);
    }

    //Spiel beenden
    if (splitData[0] == "setGameOver")
    {
        m_mainWindow.grid[5][3]->setEnabled(false);
        m_mainWindow.grid[1][1]->setEnabled(false);
        m_mainWindow.grid[1][2]->setEnabled(false);
    }

    //Preis setzen
    if(splitData[0] == "setDisplayedPrice")
    {
        m_mainWindow.setDisplayedPrice(splitData[1].toInt());
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

    //GridcellIds den Koordinaten zuordnen
    static const std::map<int, coordinates> gridcellCoordinates = {
        {0, {7, 0}}, {1, {6, 0}}, {2, {5, 0}}, {3, {4, 0}}, {4, {3, 0}}, {5, {2, 0}}, {6, {1, 0}},
        {7, {0, 0}}, {8, {0, 1}}, {9, {0, 2}}, {10, {0, 3}}, {11, {0, 4}}, {12, {0, 5}}, {13, {0, 6}},
        {14, {0, 7}}, {15, {1, 7}}, {16, {2, 7}}, {17, {3, 7}}, {18, {4, 7}}, {19, {5, 7}}, {20, {6, 7}},
        {21, {7, 7}}, {22, {7, 6}}, {23, {7, 5}}, {24, {7, 4}}, {25, {7, 3}}, {26, {7, 2}}, {27, {7, 1}}
    };

    //Ermittlung der Koordinaten für die angegebene gridcellId

    //GridcellId in der map finden
    auto it = gridcellCoordinates.find(gridcellId);

    //Der GridcellId entsprechende Koordinaten finden
    if (it != gridcellCoordinates.end()) {
        coords = it->second;
    }
    //Ungültige gridcellId behandeln
    else
    {
        coords.x = -1;
        coords.y = -1;
    }
    return coords;
}
