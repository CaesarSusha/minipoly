#include "mainwindow.h"
#include "client.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

int main(int argc, char *argv[])
{
    //Deklarieren QApplication
    QApplication a(argc, argv);

    //Deklarieren Main Window
    //MainWindow w;
    //Anzeige Main Window
    //w.show();
    //Favicon Anzeigen
    //a.setWindowIcon(QIcon(":/assets/nc_icon.png"));
    //Application ausführen

    QUrl url;

    url.setScheme("ws");
    url.setHost("localhost");
    url.setPort(3000);
    Client client(url);

    return a.exec();
}
