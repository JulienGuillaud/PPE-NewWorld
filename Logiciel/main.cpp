#include "mainwindow.h"
#include <QApplication>
#include "connectionpage.h"
#include <QDebug>
#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QString nomDuPays= QLocale::system().name().left(2);
    translator.load(":/traductions/newWorld_" + nomDuPays);
    a.installTranslator(&translator);


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("");
    db.setDatabaseName("");
    db.setUserName("");
    db.setPassword("");
    bool ok = db.open();
    qDebug()<<"Base : "<<ok;

    MainWindow w;
    // Connection
    ConnectionPage connection;

//    if(connection.exec())
//    {
        w.setModID(connection.modID);
        //qDebug() << "accepted";
        w.remplirRayons();
        w.updatePagePourAdmin();
        w.show();
//    }
//    else {
//        //qDebug() << "declined";

//    }






    return a.exec();
}
