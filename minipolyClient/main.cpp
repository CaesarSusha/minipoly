#include <QCoreApplication>
#include "Client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;
    client.start("127.0.0.1",8888);

    return a.exec();
}
