#include "dialogmodifproduits.h"
#include "ui_dialogmodifproduits.h"
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>
DialogModifProduits::DialogModifProduits(QWidget *parent, QString noProd, QString nomRayon) :
    QDialog(parent),
    ui(new Ui::DialogModifProduits)
{
    ui->setupUi(this);
    this->prodID=noProd;

    QSqlQuery reqProd("SELECT producteurID, producteurNom from PRODUCTEURS");

    ui->comboBoxProd->clear();
    ui->comboBoxProd->addItem(tr("Choose..."));
    int row=0;
    while (reqProd.next())
    {
        QString prodIDReq=reqProd.value(0).toString();
        QString prodLibReq=reqProd.value(1).toString();
/*
        if(prodIDReq==this->prodID)
        {
            //memorisation de l'index
            index=ui->comboBoxProd->count()-1;
        }*/
        ui->comboBoxProd->addItem(prodLibReq, prodIDReq);
        row++;
    }

    // Selection du producteur courant
    QSqlQuery producteur("select producteurID from PRODUITS where prodID="+prodID);
    producteur.first();
    int index;
    index=ui->comboBoxProd->findData(producteur.value(0).toInt());

    ui->comboBoxProd->setCurrentIndex(index);


    // Remplissage combobox Rayons

    QSqlQuery reqRayon("SELECT rayID, rayLib from RAYONS");

    ui->comboBoxRayon->clear();
    ui->comboBoxRayon->addItem(tr("Choose..."));
    int indexRayon;
    int rowRayon=0;
    while (reqRayon.next())
    {
        QString rayonIDReq=reqRayon.value(0).toString();
        QString rayonLibReq=reqRayon.value(1).toString();

        ui->comboBoxRayon->addItem(rayonLibReq, rayonIDReq);
        rowRayon++;
    }

    QSqlQuery rayonID("select rayID from RAYONS where rayLib='"+nomRayon+"'");
    rayonID.first();

    qDebug()<<nomRayon;
    qDebug()<<rayonID.value(0).toInt();
    indexRayon=ui->comboBoxRayon->findData(rayonID.value(0).toInt());
    qDebug()<<indexRayon;
    ui->comboBoxRayon->setCurrentIndex(indexRayon);

    setIDProd();
}

DialogModifProduits::~DialogModifProduits()
{
    delete ui;
}

void DialogModifProduits::setIDProd()
{

    qDebug()<< prodID;

    QSqlQuery preRemplissageModif("select * from  PRODUITS where prodID ="+prodID);
    preRemplissageModif.first();

    ui->prodLib->setText(preRemplissageModif.value(1).toString());
    nomFichierImage=preRemplissageModif.value(2).toString();
    ui->pushButton_3->setText(nomFichierImage);
    ui->prodDesc->setText(preRemplissageModif.value(3).toString());
    ui->prodUnite->setText(preRemplissageModif.value(5).toString());

    QString prix = preRemplissageModif.value(4).toString().replace('.',',');
    ui->prodPU->setValue(prix.toDouble());
    if (!nomFichierImage.isEmpty())
    {
        ui->labelImageProduits->setText(nomFichierImage);
        QPixmap sonImage(nomFichierImage);
        if (!sonImage.isNull())
        {
            ui->labelImageProduits->setPixmap(sonImage.scaled(400,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

}




void DialogModifProduits::on_pushButton_clicked()
{
    if (ui->prodLib->text().length() != 3 && ui->prodDesc->text().length() != 5 && ui->prodUnite->text().length() != 0 && ui->prodPU->text().length() != 0 && nomFichierImage.length()!=3 && ui->comboBoxProd->currentIndex()!=0)
    {
        QString prodLib=ui->prodLib->text();
        QString prodPhoto=nomFichierImage;
        QString prodDesc=ui->prodDesc->text();
        QString prodPU=ui->prodPU->text().replace(',','.');
        QString prodUnite=ui->prodUnite->text();


        QSqlQuery reqChangementRayon("update PRODUITS set prodLib='"+prodLib+"', prodPhoto='"+prodPhoto+"', prodDesc='"+prodDesc+"', prodPU='"+prodPU+"', prodUnite='"+prodUnite+"', prodRayon="+ui->comboBoxRayon->currentData().toString()+", producteurID="+ui->comboBoxProd->currentData().toString()+" where prodID="+prodID);
        accept();
    }
    else
    {
        ui->labelErreurAjoutProd->setText(tr("Error, check if all fields are filled in."));

    }
}

void DialogModifProduits::on_boutonAnnuler_clicked()
{
    reject();
}

void DialogModifProduits::on_pushButton_3_clicked()
{
    nomFichierImage=QFileDialog::getOpenFileName(this, tr("Select image"), "" , "Images (*.gif *.jpg *.png *.jpeg *.bmp" );

    if (!nomFichierImage.isEmpty())
    {
        ui->labelImageProduits->setText(nomFichierImage);
        QPixmap sonImage(nomFichierImage);
        if (!sonImage.isNull())
        {
            ui->labelImageProduits->setPixmap(sonImage.scaled(400,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}
