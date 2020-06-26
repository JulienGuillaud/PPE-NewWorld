#include "dialogajoutproduits.h"
#include "ui_dialogajoutproduits.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
DialogAjoutProduits::DialogAjoutProduits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutProduits)
{
    ui->setupUi(this);
        sonLibBool= false;
        saPhotoBool= false;
        saDescBool= false;
        sonPrixBool= false;
        sonUniteBool= false;
        sonLineEditQTE=false;
        QSqlQuery reqProd("SELECT produID, produNom from Producteur");

        ui->comboBoxProd->clear();
        ui->comboBoxProd->addItem(tr("Choose..."));
        int row=0;
        while (reqProd.next())
        {
            QString rayID=reqProd.value(0).toString();
            QString rayLib=reqProd.value(1).toString();

            ui->comboBoxProd->addItem(rayLib, rayID);


            row++;
        }

        QSqlQuery reqUnite("SELECT umesureID, umesureLib from UniteMesure");

        ui->comboBoxUnite->clear();
        ui->comboBoxUnite->addItem(tr("Choose..."));
        int rowUnite=0;
        while (reqUnite.next())
        {
            QString rayUniteID=reqUnite.value(0).toString();
            QString rayUniteLib=reqUnite.value(1).toString();

            ui->comboBoxUnite->addItem(rayUniteLib, rayUniteID);


            rowUnite++;
        }

}

DialogAjoutProduits::~DialogAjoutProduits()
{
    delete ui;
}

void DialogAjoutProduits::testFormComplet()
{
qDebug()<<sonLibBool<<" "<<saPhotoBool<<" "<<saDescBool<<" "<<sonPrixBool<<" "<<sonLineEditQTE<<" "<<ui->comboBoxProd->currentIndex()<<""<<ui->comboBoxUnite->currentIndex()<<" "<<ui->comboBoxProduit->currentIndex();
    if (sonLibBool && saPhotoBool && saDescBool && sonPrixBool && ui->comboBoxProd->currentIndex()!=0 && ui->comboBoxUnite->currentIndex()!=0 && ui->comboBoxProduit->currentIndex()!=0)
    {
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}

void DialogAjoutProduits::remplirComboBoxProduit()
{
    QSqlQuery reqProduit("SELECT produitID, produitLib from Produit where rayID="+idRayon);
qDebug()<<reqProduit.lastQuery();
    ui->comboBoxProduit->clear();
    ui->comboBoxProduit->addItem(tr("Choose..."));
    int rowProd=0;
    while (reqProduit.next())
    {
        QString varID=reqProduit.value(0).toString();
        QString varLib=reqProduit.value(1).toString();

        ui->comboBoxProduit->addItem(varLib, varID);


        rowProd++;
    }
    ui->comboBoxProduit->addItem("New...",-999);
}

void DialogAjoutProduits::on_pushButton_clicked()
{

    QString sonLib= ui->prodLib->text();
    QString saPhoto=nomFichierImage;
    QString saDesc=ui->prodDesc->text();
    QString sonPrix=ui->prodPU->text().replace(',','.');
    QString sonUniteID=ui->comboBoxUnite->currentData().toString();
    QString idProducteur=ui->comboBoxProd->currentData().toString();
    QString nomProduit=ui->comboBoxProduit->currentText();

        // Ajout produit
        QSqlQuery nvProduit("insert into Produit (produitLib, rayID) values ('"+nomProduit+"',"+idRayon+")");

        // Selection de l'id du nouveau produit
        QSqlQuery idProduit("select produitID from Produit where produitLib='"+nomProduit+"' and rayID="+idRayon);
        idProduit.first();
        QString idProduitString=idProduit.value(0).toString();

        // Ajout de la variétée
        QSqlQuery reqInsertNewProd("insert into Variete (prodLib, prodPhoto, prodDesc, prodActif, produitID) values ('"+sonLib+"','"+saPhoto+"','"+saDesc+"',1,"+idProduitString+")");
        qDebug()<<reqInsertNewProd.lastQuery();

        // Selection de l'id de la variétée
        QSqlQuery reqIdVariete("select prodID from Variete where prodLib='"+sonLib+"' and prodPhoto='"+saPhoto+"';");
        reqIdVariete.first();
        QString idVariete=reqIdVariete.value(0).toString();
        // Ajout de la variete au catalogue du producteur
       /* QSqlQuery reqAjoutProduitAuProd("insert into Propose (proposeQTE, proposePU, proposeDLC, proposeQTEMin, produID, prodID, umesureID)"
                                        "values"
                                        "(");
        */
        accept();



}

void DialogAjoutProduits::on_prodLib_textEdited(const QString &arg1)
{
    if (ui->prodLib->text().length() >= 3 )
    {
        sonLibBool=true;
    }
    else
    {
        sonLibBool=false;
    }
    testFormComplet();
}

void DialogAjoutProduits::on_prodDesc_textEdited(const QString &arg1)
{
    if (ui->prodDesc->text().length() >= 5 )
    {
        saDescBool=true;
    }
    else
    {
        saDescBool=false;
    }
    testFormComplet();
}

void DialogAjoutProduits::on_prodPU_valueChanged(double arg1)
{
    if (arg1 >0.00 )
    {
        sonPrixBool=true;
    }
    else
    {
        sonPrixBool=false;
    }
    testFormComplet();
}


void DialogAjoutProduits::on_pushButton_3_clicked()
{
    nomFichierImage=QFileDialog::getOpenFileName(this, tr("Select image"), "~/Images/" , "Images (*.gif *.jpg *.png *.jpeg *.bmp" );

    if (!nomFichierImage.isEmpty())
    {
        ui->pushButton_3->setText(nomFichierImage);
        QPixmap sonImage(nomFichierImage);
        if (!sonImage.isNull())
        {
            ui->labelImageProduits->setPixmap(sonImage.scaled(400,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    if (!nomFichierImage.isEmpty())
    {
        saPhotoBool=true;
    }
    else
    {
        saPhotoBool=false;
    }
    testFormComplet();
}

void DialogAjoutProduits::on_boutonAnnuler_clicked()
{
    reject();
}










void DialogAjoutProduits::on_comboBoxProd_currentIndexChanged(int index)
{
    testFormComplet();
}

void DialogAjoutProduits::on_comboBoxProduit_currentIndexChanged(int index)
{
    bool ok=false;
/*
        if(ui->comboBoxProduit->currentData()==-9000)
        {
            this->ui->comboBoxProduit->removeItem(ui->comboBoxProduit->findData(-9000));
        }
*/
    if(ui->comboBoxProduit->currentData()==-999)
    {
        qDebug()<<"New";
        if(ui->comboBoxProduit->findData(-9000) != -1 )
        {
            qDebug()<<"Deja existant";
            remplirComboBoxProduit();
        }
            qDebug()<<"Avant popup : "<<ok;
                QString text = QInputDialog::getText(this, "NewWorld Ajout Produit",
                                                         "Nom Produit", QLineEdit::Normal,
                                                        "", &ok);
                qDebug()<<"Apres popup : "<<ok;

        if(!ok)
        {
            //ui->comboBoxProduit->setCurrentIndex(0);
        }
        else {
            QSqlQuery reqProduit("SELECT produitID, produitLib from Produit where rayID="+idRayon);
        qDebug()<<reqProduit.lastQuery();
            ui->comboBoxProduit->clear();
            ui->comboBoxProduit->addItem(tr("Choose..."));
            int rowProd=0;
            while (reqProduit.next())
            {
                QString varID=reqProduit.value(0).toString();
                QString varLib=reqProduit.value(1).toString();

                ui->comboBoxProduit->addItem(varLib, varID);


                rowProd++;
            }
            ui->comboBoxProduit->addItem(text, -9000);

            ui->comboBoxProduit->addItem("New...",-999);
           ui->comboBoxProduit->setCurrentIndex(ui->comboBoxProduit->findData(-9000));

        }
    }

}


void DialogAjoutProduits::on_comboBoxUnite_currentIndexChanged(int index)
{
    testFormComplet();
}

void DialogAjoutProduits::on_lineEditQTE_textEdited(const QString &arg1)
{
    if (ui->lineEditQTE->text().length() >= 3 )
    {
        sonLineEditQTE=true;
    }
    else
    {
        sonLineEditQTE=false;
    }
    testFormComplet();
}

void DialogAjoutProduits::on_lineEditQTEMin_textEdited(const QString &arg1)
{

}
