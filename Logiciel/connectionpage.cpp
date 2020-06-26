#include "connectionpage.h"
#include "ui_connectionpage.h"
#include "mainwindow.h"
#include <QDebug>

ConnectionPage::ConnectionPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionPage)
{
    ui->setupUi(this);
}

ConnectionPage::~ConnectionPage()
{
    delete ui;
}

void ConnectionPage::on_pushButton_2_clicked()
{
    QString login=ui->login->text();
    QString mdp=ui->password->text();

    // Si les champs Texte ne sont pas vide
    if(!login.isEmpty() && !mdp.isEmpty())
    {
        QString textReq="select modID from Moderateur where modLogin='"+login+"' and modMDP=password('"+mdp+"')";
        qDebug()<<textReq;
        //qDebug()<<reqConnection.lastQuery();
        //qDebug()<<reqConnection.first();
        QSqlQuery reqConnection(textReq);
        // Si il y a un résultat à la requète
        if(reqConnection.first())
        {
            // Garder en mémoire l'ID du modérateur
            modID=reqConnection.value(0).toInt();
            accept();
        }
        else
        {
            // Afficher Erreur
            ui->labelErreur->setText(tr("Error, incorrect username or password."));
        }
    }
}
