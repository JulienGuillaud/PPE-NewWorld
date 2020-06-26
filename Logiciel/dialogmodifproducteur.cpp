#include "dialogmodifproducteur.h"
#include "ui_dialogmodifproducteur.h"
#include <QSqlQuery>
#include <QDebug>

DialogModifProducteur::DialogModifProducteur(QString idDuProd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModifProducteur)
{
    ui->setupUi(this);
    idProd=idDuProd;
    nom=true;
    prenom=true;
    login=true;
    email=true;
    mdp=true;
    telPort=true;
    telFix=true;
    adresse=true;
    ville=true;
    cp=true;

    ok=true;
    ui->pushButtonUpdate->setEnabled(true);

    QSqlQuery remplirChamps("select * from PRODUCTEURS where producteurID="+idDuProd);
    qDebug()<<remplirChamps.lastQuery();
    qDebug()<<"ID = "+idDuProd;
    remplirChamps.first();
    ui->lineEditNom->setText(remplirChamps.value(1).toString());
    ui->lineEditPrenom->setText(remplirChamps.value(2).toString());
    ui->lineEditLogin->setText(remplirChamps.value(3).toString());
    ui->lineEditEmail->setText(remplirChamps.value(4).toString());
    ui->lineEditTelFix->setText(remplirChamps.value(7).toString());
    ui->lineEditTelPort->setText(remplirChamps.value(8).toString());
    ui->lineEditAdresse->setText(remplirChamps.value(9).toString());
    ui->lineEditVille->setText(remplirChamps.value(10).toString());
    ui->lineEditCP->setText(remplirChamps.value(11).toString());
    if(remplirChamps.value(12).toBool())
    {
        ui->comboBoxEmailVerif->setCurrentIndex(1);
    }
    else
    {
        ui->comboBoxEmailVerif->setCurrentIndex(0);
    }
    if(remplirChamps.value(12).toBool())
    {
        ui->comboBoxProdVerif->setCurrentIndex(1);
    }
    else
    {
        ui->comboBoxProdVerif->setCurrentIndex(0);
    }



}

DialogModifProducteur::~DialogModifProducteur()
{
    delete ui;
}

void DialogModifProducteur::on_pushButtonUpdate_clicked()
{
    QString prodNom=ui->lineEditNom->text();
    QString prodPrenom=ui->lineEditPrenom->text();
    QString prodLogin=ui->lineEditLogin->text();
    QString prodEmail=ui->lineEditEmail->text();
    QString prodTelFix=ui->lineEditTelFix->text();
    QString prodTelPort=ui->lineEditTelPort->text();
    QString prodAdresse=ui->lineEditAdresse->text();
    QString prodVille=ui->lineEditVille->text();
    QString prodCP=ui->lineEditCP->text();
    QString prodMailVerif=QString::number(ui->comboBoxEmailVerif->currentIndex());
    QString prodVerif=QString::number(ui->comboBoxProdVerif->currentIndex());
    qDebug()<<ui->comboBoxEmailVerif->currentIndex();

    QSqlQuery updateProducteur("update PRODUCTEURS set producteurNom='"+prodNom+"', producteurPrenom='"+prodPrenom+"', producteurLogin='"+prodLogin+"', producteurEmail='"+prodEmail+"', prodTelFix='"+prodTelFix+"', prodTelPort='"+prodTelPort+"', prodAdresse='"+prodAdresse+"', prodVille='"+prodVille+"', prodCP='"+prodCP+"', prodConfirmMail="+prodMailVerif+", prodConfirm="+prodVerif+" where producteurID="+idProd);
    qDebug()<<updateProducteur.lastQuery();
    accept();

}

void DialogModifProducteur::on_pushButtonCancel_clicked()
{
    reject();
}

void DialogModifProducteur::on_lineEditNom_textEdited(const QString &arg1)
{
    if(ui->lineEditNom->text().length() >2)
    {
        nom=true;
        ui->labelErrLongNom->setText("");
    }
    else
    {
        nom=false;
        ui->labelErrLongNom->setText("Attention, nom trop court.");
    }
    verifToutForm();

}

void DialogModifProducteur::on_lineEditPrenom_textEdited(const QString &arg1)
{
    if(ui->lineEditPrenom->text().length() >2)
    {
        prenom=true;
        ui->labelErrLongPrenom->setText("");
    }
    else
    {
        prenom=true;
        ui->labelErrLongPrenom->setText("Attention, prénom trop court.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditLogin_textEdited(const QString &arg1)
{
    if(ui->lineEditLogin->text().length() >2)
    {
        login=true;
        ui->labelErrLongLogin->setText("");
    }
    else
    {
        login=false;
        ui->labelErrLongLogin->setText("Attention, login trop court.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditEmail_textEdited(const QString &arg1)
{
    if(ui->lineEditEmail->text().length() >4)
    {
        email=true;
        ui->labelErrLongEmail->setText("");
    }
    else
    {
        email=false;
        ui->labelErrLongEmail->setText("Attention, email trop court.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditTelPort_textEdited(const QString &arg1)
{
    if(ui->lineEditTelPort->text().length() >10)
    {
        telPort=true;
        ui->labelErrLongTelPort->setText("");
    }
    else
    {
        telPort=false;
        ui->labelErrLongTelPort->setText("Attention, Tel court.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditTelFix_textEdited(const QString &arg1)
{
    if(ui->lineEditTelFix->text().length() >10)
    {
        telFix=true;
        ui->labelErrLongTelFix->setText("");
    }
    else
    {
        telFix=false;
        ui->labelErrLongTelFix->setText("Attention, Tel trop court.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditAdresse_textEdited(const QString &arg1)
{
    if(ui->lineEditAdresse->text().length() >2)
    {
        adresse=true;
        ui->labelErrLongAdresse->setText("");
    }
    else
    {
        adresse=false;
        ui->labelErrLongAdresse->setText("Attention, adresse trop courte.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditVille_textEdited(const QString &arg1)
{
    if(ui->lineEditVille->text().length() >2)
    {
        ville=true;
        ui->labelErrLongVille->setText("");
    }
    else
    {
        ville=false;
        ui->labelErrLongVille->setText("Attention, ville trop courte.");
    }
    verifToutForm();
}

void DialogModifProducteur::on_lineEditCP_textEdited(const QString &arg1)
{
    if(ui->lineEditCP->text().length() >4)
    {
        cp=true;
        ui->labelErrLongCP->setText("");
    }
    else
    {
        cp=false;
        ui->labelErrLongCP->setText("Attention, Code Postal trop court.");
    }
    verifToutForm();
}


void DialogModifProducteur::verifToutForm()
{
    if(nom && prenom && login && email && mdp && telPort && telFix && adresse && ville && cp)
    {
        ui->pushButtonUpdate->setEnabled(true);
    }
    else
    {
        ui->pushButtonUpdate->setEnabled(false);
    }
}
