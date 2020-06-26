#include "dialogdeplacerproduitsderayons.h"
#include "ui_dialogdeplacerproduitsderayons.h"
#include <QDebug>
#include <QFileDialog>

DialogDeplacerProduitsDeRayons::DialogDeplacerProduitsDeRayons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDeplacerProduitsDeRayons)
{
    ui->setupUi(this);

    sonLibBool=false;
    saPhotoBool=false;
    saDescBool=false;

    ui->rayonDeplacement->setVisible(false);
    ui->nvRayon->setVisible(false);

    ui->pushButtonDeplacer->setEnabled(false);
    ui->pushButtonAjouterEtDeplacer->setEnabled(false);

    QSqlQuery reqRayons("SELECT rayID, rayLib, rayPhoto from RAYONS");

    ui->comboBoxRayons->clear();
    ui->comboBoxRayons->addItem(tr("Choose..."));
    int row=0;
    while (reqRayons.next())
    {
        QString rayID=reqRayons.value(0).toString();
        QString rayLib=reqRayons.value(1).toString();
        QString rayPhoto=reqRayons.value(2).toString();

        ui->comboBoxRayons->addItem(rayLib, rayID);

        ui->comboBoxRayons->setItemIcon(row+1, QIcon(rayPhoto));

        row++;
    }

}

DialogDeplacerProduitsDeRayons::~DialogDeplacerProduitsDeRayons()
{
    delete ui;
}

void DialogDeplacerProduitsDeRayons::testFormComplet()
{
    if (sonLibBool && saPhotoBool && saDescBool)
    {
        ui->pushButtonAjouterEtDeplacer->setEnabled(true);
    }
    else
    {
        ui->pushButtonAjouterEtDeplacer->setEnabled(false);
    }
    qDebug()<< tr("Shelf ID : ")+idDuRayon;
}

void DialogDeplacerProduitsDeRayons::setIDRayon(QString idRayon)
{
    idDuRayon=idRayon;
}

void DialogDeplacerProduitsDeRayons::on_ajoutPhotoRayon_clicked()
{
    nomFichierImage=QFileDialog::getOpenFileName(this, tr("Select image"), "~/Images/" , "Images (*.gif *.jpg *.png *.jpeg *.bmp" );
    if (!nomFichierImage.isEmpty())
    {
        QPixmap sonImage(nomFichierImage);
        if (!sonImage.isNull())
        {
            ui->labelImageRayon->setPixmap(sonImage.scaled(200,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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


void DialogDeplacerProduitsDeRayons::on_pushButtonAjouterEtDeplacer_clicked()
{
    QString sonLib= ui->lineEditLib->text();
    QString saPhoto=nomFichierImage;
    QString saDesc=ui->lineEditDesc->text();

    if (sonLib!="" && saPhoto!="" && saDesc !="")
    {
        QSqlQuery reqInsertNewRayon("INSERT INTO RAYONS (rayLib, rayPhoto, rayDesc) values ('"+sonLib+"','"+saPhoto+"','"+saDesc+"')");

        QSqlQuery reqIDNvRayon("select rayID from RAYONS where rayLib='"+sonLib+"' and rayDesc='"+saDesc+"';");
        reqIDNvRayon.first();

        QString idNvRayon=reqIDNvRayon.value(0).toString();

        // Deplacement

        QSqlQuery reqProduitsDuRayon("select prodID from PRODUITS where prodRayon="+idDuRayon);

        while(reqProduitsDuRayon.next())
        {

            QString idProd=reqProduitsDuRayon.value(0).toString();
            qDebug()<<"Modif de "+idProd+" set "+idDuRayon+" = "+idNvRayon;
            QSqlQuery reqChangementRayon("update PRODUITS set prodRayon="+idNvRayon+" where prodID="+idProd);
            //qDebug()<<"update PRODUITS set prodRayon="+idNvRayon+" where prodID="+idProd;
        }
        QSqlQuery requeteSupprRayon("DELETE FROM RAYONS where rayID="+idDuRayon);
        accept();
    }
}


void DialogDeplacerProduitsDeRayons::on_lineEditLib_textEdited(const QString &arg1)
{
    if (ui->lineEditLib->text().length() >= 3 )
    {
        sonLibBool=true;
    }
    else
    {
        sonLibBool=false;
    }
    testFormComplet();
}

void DialogDeplacerProduitsDeRayons::on_lineEditDesc_textEdited(const QString &arg1)
{
    if (ui->lineEditDesc->text().length() >= 5 )
    {
        saDescBool=true;
    }
    else
    {
        saDescBool=false;
    }
    testFormComplet();
}

void DialogDeplacerProduitsDeRayons::on_pushButtonDeplacer_clicked()
{
    QString currentRayon=ui->comboBoxRayons->currentData().toString();
    if (ui->comboBoxRayons->currentIndex()!=0)
    {
        QSqlQuery reqProduitsDuRayon("select prodID from PRODUITS where prodRayon="+idDuRayon);

        while(reqProduitsDuRayon.next())
        {

            QString idProd=reqProduitsDuRayon.value(0).toString();
            QSqlQuery reqChangementRayon("update PRODUITS set prodRayon="+currentRayon+" where prodID="+idProd);
            //qDebug()<<"update PRODUITS set prodRayon="+idNvRayon+" where prodID="+idProd;
        }

        QSqlQuery requeteSupprRayon("DELETE FROM RAYONS where rayID="+idDuRayon);
        accept();
    }
}

void DialogDeplacerProduitsDeRayons::on_comboBoxRayons_currentIndexChanged(const QString &arg1)
{
    if (ui->comboBoxRayons->currentIndex()!=0)
    {
        ui->pushButtonDeplacer->setEnabled(true);
    }
    else
    {
        ui->pushButtonDeplacer->setEnabled(false);
    }
}

void DialogDeplacerProduitsDeRayons::on_annuler_clicked()
{
    reject();
}

void DialogDeplacerProduitsDeRayons::on_radioButtonNvRayon_toggled(bool checked)
{
    ui->rayonDeplacement->setVisible(false);
    ui->nvRayon->setVisible(true);
}

void DialogDeplacerProduitsDeRayons::on_radioButtonDeplacement_toggled(bool checked)
{
    ui->rayonDeplacement->setVisible(true);
    ui->nvRayon->setVisible(false);
}
