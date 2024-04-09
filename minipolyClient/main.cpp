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
    QFont font("Sans");
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(10);
    font.setWeight(80);
    QApplication::setFont(font);

    QUrl url;

    url.setScheme("ws");
    url.setHost("localhost");
    url.setPort(3000);
    Client client(url);

    return a.exec();
}
