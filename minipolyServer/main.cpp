#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    //Applikation erstellen
    QCoreApplication a(argc, argv);

    Server* server = Server::getInstance();

    QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

    //Ausführen
    return a.exec();
}
