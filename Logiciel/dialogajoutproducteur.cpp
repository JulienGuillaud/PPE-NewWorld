#include "dialogajoutproducteur.h"
#include "ui_dialogajoutproducteur.h"
#include "QSqlQuery"
#include <QDebug>

DialogAjoutProducteur::DialogAjoutProducteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutProducteur)
{
    ui->setupUi(this);
    nom=false;
    prenom=false;
    login=false;
    email=false;
    mdp=false;
    telPort=false;
    telFix=false;
    adresse=false;
    ville=false;
    cp=false;
    nomEntre=false;
    siret=false;

    ok=false;
}

DialogAjoutProducteur::~DialogAjoutProducteur()
{
    delete ui;
}

void DialogAjoutProducteur::on_pushButton_clicked()
{
    QString prodNom=ui->lineEditNom->text();
    QString prodPrenom=ui->lineEditPrenom->text();
    QString prodLogin=ui->lineEditLogin->text();
    QString prodEmail=ui->lineEditEmail->text();
    QString prodMDP=ui->lineEditMDP->text();
    QString prodTelFix=ui->lineEditTelFix->text();
    QString prodTelPort=ui->lineEditTelPort->text();
    QString prodAdresse=ui->lineEditAdresse->text();
    QString prodVille=ui->lineEditVille->text();
    QString prodCP=ui->lineEditCP->text();

    QString prodEntreprise=ui->lineEditNomEntre->text();
    QString prodSiret=ui->lineEditSIRET->text();

    // Verif si entreprise existe déja dans la BDD
    QSqlQuery verifEntreprise("select count(*) from ENTREPRISE where entreSiret='"+prodSiret+"'");
    verifEntreprise.first();
    qDebug()<<verifEntreprise.value(0).toString();
    qDebug()<<prodSiret;
    if (verifEntreprise.value(0).toInt() <= 0)
    {
        QSqlQuery ajoutEntreprise("insert into ENTREPRISE (entreNom, entreSiret) values ('"+prodEntreprise+"','"+prodSiret+"')");
        QSqlQuery recuperationIDEntreprise("select entreID from ENTREPRISE where entreSiret='"+prodSiret+"' and entreNom='"+prodEntreprise+"'");
        recuperationIDEntreprise.first();
        QString idEntreprise=recuperationIDEntreprise.value(0).toString();

        QSqlQuery ajoutProducteur("insert into PRODUCTEURS (producteurNom, producteurPrenom, producteurLogin, producteurEmail, producteurMDP, producteurEntreprise, prodTelFix, prodTelPort, prodAdresse, prodVille, prodCP, prodConfirmMail, prodConfirm) values ('"+prodNom+"','"+prodPrenom+"','"+prodLogin+"','"+prodEmail+"',password('"+prodMDP+"'),'"+idEntreprise+"','"+prodTelFix+"','"+prodTelPort+"','"+prodAdresse+"','"+prodVille+"','"+prodCP+"',0,0)");
        accept();
    }
    else
    {
        ui->labelErrLongSiret->setText("Attention, SIRET déja utilisé.");
    }

}

void DialogAjoutProducteur::on_pushButton_2_clicked()
{
    reject();
}

void DialogAjoutProducteur::on_lineEditNom_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditPrenom_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditLogin_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditEmail_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditMDP_textEdited(const QString &arg1)
{
    if(ui->lineEditMDP->text().length() >5)
    {
        mdp=true;
        ui->labelErrLongMDP->setText("");

    }
    else
    {
        mdp=false;
        ui->labelErrLongMDP->setText("Attention, Mot de passe faible.");
    }
    verifToutForm();
}

void DialogAjoutProducteur::on_lineEditTelPort_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditTelFix_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditAdresse_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditVille_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditCP_textEdited(const QString &arg1)
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

void DialogAjoutProducteur::on_lineEditNomEntre_textEdited(const QString &arg1)
{
    if(ui->lineEditNomEntre->text().length() >2)
    {
        nomEntre=true;
        ui->labelErrLongNomEntre->setText("");
    }
    else
    {
        nomEntre=false;
        ui->labelErrLongNomEntre->setText("Attention, nom entreprise trop court.");
    }
    verifToutForm();
}

void DialogAjoutProducteur::on_lineEditSIRET_textEdited(const QString &arg1)
{
    if(ui->lineEditSIRET->text().length() ==14)
    {
        siret=true;
        ui->labelErrLongSiret->setText("");
    }
    else
    {
        siret=false;
        ui->labelErrLongSiret->setText("Attention, SIRET Invalide, verifiez la longueur (13).");
    }
    verifToutForm();
}

void DialogAjoutProducteur::verifToutForm()
{
    if(nom && prenom && login && email && mdp && telPort && telFix && adresse && ville && cp && nomEntre && siret)
    {
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}
