#include "dialogajoutrayons.h"
#include "ui_dialogajoutrayons.h"
#include <QDebug>
#include <QFileDialog>

DialogAjoutRayons::DialogAjoutRayons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutRayons)
{
    ui->setupUi(this);
    mettreID();
    sonLibBool=false;
    saPhotoBool=false;
    saDescBool=false;
    ui->pushButton->setEnabled(false);
}

DialogAjoutRayons::~DialogAjoutRayons()
{
    delete ui;
}

void DialogAjoutRayons::mettreID()
{
    QSqlQuery reqIdFuturRayon("SELECT max(rayID+1) as idRayFutur from RAYONS");
    reqIdFuturRayon.first();
    QString idRayFutur = reqIdFuturRayon.value(0).toString();

    ui->lineEditID->setText(idRayFutur);
}

void DialogAjoutRayons::testFormComplet()
{
    if (sonLibBool && saPhotoBool && saDescBool)
    {
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}


void DialogAjoutRayons::on_pushButton_clicked()
{

    QString sonLib= ui->lineEditLib->text();
    QString saPhoto=nomFichierImage;
    QString saDesc=ui->lineEditDesc->text();

    if (sonLib!="" && saPhoto!="" && saDesc !="")
    {
        QSqlQuery reqInsertNewRayon("INSERT INTO RAYONS (rayLib, rayPhoto, rayDesc) values ('"+sonLib+"','"+saPhoto+"','"+saDesc+"')");
        nomRayon=sonLib;
        accept();

    }
    else
    {
        ui->labelErreurAjout->setText(tr("Error, check if all fields are filled in."));


    }


}

void DialogAjoutRayons::on_ajoutPhotoRayon_clicked()
{
    nomFichierImage=QFileDialog::getOpenFileName(this, tr("Select image"), "~/Images/" , "Images (*.gif *.jpg *.png *.jpeg *.bmp" );

    if (!nomFichierImage.isEmpty())
    {
        ui->ajoutPhotoRayon->setText(nomFichierImage);
        QPixmap sonImage(nomFichierImage);
        if (!sonImage.isNull())
        {
            ui->labelImageRayon->setPixmap(sonImage.scaled(400,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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


void DialogAjoutRayons::on_lineEditLib_textEdited(const QString &arg1)
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

void DialogAjoutRayons::on_lineEditDesc_textEdited(const QString &arg1)
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
