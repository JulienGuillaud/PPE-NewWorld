#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogajoutrayons.h"
#include <dialogsupprrayons.h>
#include "dialogsupprrayons.h"
#include "dialogchoixdeplacerousupprprod.h"
#include "dialogdeplacerproduitsderayons.h"
#include "dialogajoutproduits.h"
#include "dialogverifsupprproduit.h"
#include "dialogmodifproduits.h"
#include "dialogajoutproducteur.h"
#include "dialogverifsupprproducteur.h"
#include "dialogmodifproducteur.h"
#include "dialogdocumentation.h"

#include <QDesktopServices>
#include <QDebug>
#include <vector>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prodTable->setUpdatesEnabled(true);
    ui->rayonSuppr->setEnabled(false);
    ui->rayonAdd->setEnabled(false);
    ui->prodAnnul->setEnabled(false);
    ui->prodAdd->setEnabled(false);
    ui->prodModif->setEnabled(false);
    ui->prodSuppr->setEnabled(false);
    ui->adminAdd->setEnabled(true);
    ui->adminModif->setEnabled(false);
    ui->adminRemove->setEnabled(false);
    ui->adminAnnul->setEnabled(false);

    remplirProducteurs("");
    remplirProducteursEntreprises("");
    remplirAdmins("");
    checked=false;
    ui->producteurVerif->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::warning(this, "NewWorld" ,tr("Do you really want to leave ?"), QMessageBox::Yes, QMessageBox::No);

    event->ignore();

    switch (res)
    {
    case QMessageBox::Yes:
    {
        QMainWindow::closeEvent(event);
        break;
    }

    default:
        break;
    }
}

void MainWindow::remplirRayons()
{
    ui->prodAnnul->setEnabled(false);
    ui->prodAdd->setEnabled(false);
    ui->prodModif->setEnabled(false);
    ui->prodSuppr->setEnabled(false);
    QSqlQuery reqRayons("SELECT rayID, rayLib, rayPhoto, rayDesc from Rayon where rayActif=1");

    ui->choixRayon->clear();
    ui->choixRayon->addItem(tr("Choose..."));
    int row=0;
    while (reqRayons.next())
    {
        QString rayID=reqRayons.value(0).toString();
        QString rayLib=reqRayons.value(1).toString();
        QString rayPhoto=reqRayons.value(2).toString();
        QString rayDesc=reqRayons.value(3).toString();
        QPixmap resPix(rayPhoto);



        ui->choixRayon->addItem(rayLib, rayID);

        ui->choixRayon->setItemIcon(row+1, QIcon(rayPhoto));


        row++;
    }
}


void MainWindow::setModID(int idMod)
{
    modID=idMod;
}

void MainWindow::updatePagePourAdmin()
{
    QString idString=QString::number(modID);
    ui->tabWidget->setCurrentIndex(0);

    QSqlQuery reqSU("select modSU from Moderateur where modID="+idString);
    reqSU.first();
    lvlAdmin = reqSU.value(0).toBool();

    if (!lvlAdmin)
    {
        ui->tabWidget->removeTab(2);
    }
}



void MainWindow::on_rayonAdd_clicked()
{
    DialogAjoutRayons nvRayon;
    nvRayon.exec();
    remplirRayons();
}


void MainWindow::on_prodRecherche_textEdited(const QString &arg1)
{
    QString libelleRayon=ui->choixRayon->currentText();
    if (ui->prodRecherche->text().length()==0)
    {
        ui->choixRayon->setCurrentIndex(0);
        ui->choixRayon->setItemText(0,tr("Choose..."));
        ui->rayonSuppr->setEnabled(false);
        ui->prodAnnul->setEnabled(false);
        ui->prodAdd->setEnabled(false);
        ui->prodModif->setEnabled(false);
        ui->prodSuppr->setEnabled(false);
        ui->rayonDesc->setText("");
        ui->nbResultatProduits->setText("");

        ui->prodTable->clearContents();
        ui->prodTable->setRowCount(0);
    }

    on_choixRayon_currentIndexChanged(libelleRayon);
}

void MainWindow::on_choixRayon_currentIndexChanged(const QString &arg1)
{
    nomRayon=arg1;
    ui->rayonDesc->setText("");
    QString textRecherche=ui->prodRecherche->text();
    if ((arg1!="Choose..." && ui->choixRayon->currentIndex() != 0)|| textRecherche.length()>=1)
    {

        ui->rayonAdd->setEnabled(true);
        ui->prodAdd->setEnabled(true);
        QSqlQuery reqProd;

        if (textRecherche.length()>=1)
        {
            ui->choixRayon->setCurrentIndex(0);
            ui->choixRayon->setItemText(0,tr("Choose..."));
            ui->rayonDesc->setText("");
            ui->prodAdd->setEnabled(false);
            ui->rayonSuppr->setEnabled(false);
            qDebug()<<"Recherche de : "+textRecherche;

            reqProd.prepare("select produitLib, prodLib, prodPhoto, prodDesc, produNom, proposeQTE, proposePU, proposeDLC from Producteur inner join Propose on Producteur.produID = Propose.produID inner join Variete on Variete.prodID = Propose.prodID inner join Produit on Variete.produitID = Produit.produitID where produitLib like '%"+textRecherche+"%' or prodLib like '%"+textRecherche+"%' ");
            qDebug()<<reqProd.lastQuery();
        }
        else
        {


            reqProd.prepare("select produitLib, prodLib, prodPhoto, prodDesc, produNom, proposeQTE, proposePU, proposeDLC from Producteur inner join Propose on Producteur.produID = Propose.produID inner join Variete on Variete.prodID = Propose.prodID inner join Produit on Variete.produitID = Produit.produitID inner join Rayon on Produit.rayID = Rayon.rayID where rayLib='"+arg1+"'");
            qDebug()<<reqProd.lastQuery();
        }
        reqProd.exec();
        int nbResultats = reqProd.size();
        qDebug()<<nbResultats;
        if(arg1=="Choose..." || ui->choixRayon->currentIndex()==0)
        {
            ui->rayonSuppr->setEnabled(false);
        }
        else
        {
            ui->rayonSuppr->setEnabled(true);
        }
        QString nbResultatsString = QString::number(nbResultats);
        ui->nbResultatProduits->setText(nbResultatsString+tr(" Product(s)."));


        //int nbProd = reqProd.size();
        ui->prodTable->clearContents();
        QString currentData=ui->choixRayon->currentData().toString();
        QSqlQuery descCurrentRayon("SELECT rayDesc from Rayon where rayID="+currentData);

        if(descCurrentRayon.size()!=-1)
        {
            descCurrentRayon.first();
            ui->rayonDesc->setText(descCurrentRayon.value(0).toString());

        }

        ui->prodTable->setRowCount(0);
        int rowRayon=0;
        while (reqProd.next())
        {

            int rowCount=ui->prodTable->rowCount();
            ui->prodTable->setRowCount(rowCount+1);


            QString prodLib=reqProd.value(0).toString();
            QString prodVariete=reqProd.value(1).toString();
            QString prodPhoto=reqProd.value(2).toString();
            QString prodDesc=reqProd.value(3).toString();
            QString prodProdu=reqProd.value(4).toString();
            QString prodQTE=reqProd.value(5).toString();
            QString prodPrix=reqProd.value(6).toString();
            QString prodDLC=reqProd.value(7).toString();

            QTableWidgetItem* newProdLib = new QTableWidgetItem();
            newProdLib->setText(prodLib);

            QTableWidgetItem* newProdVariete = new QTableWidgetItem();
            newProdVariete->setText(prodVariete);

            QTableWidgetItem* newProdDesc = new QTableWidgetItem();
            newProdDesc->setText(prodDesc);

            QTableWidgetItem* newProdProdu = new QTableWidgetItem();
            newProdProdu->setText(prodProdu);

            QTableWidgetItem* newProdQTE = new QTableWidgetItem();
            newProdQTE->setText(prodQTE);

            QTableWidgetItem* newProdPrix = new QTableWidgetItem();
            newProdPrix->setText(prodPrix);

            QTableWidgetItem* newProdDLC = new QTableWidgetItem();
            newProdDLC->setText(prodDLC);



            ui->prodTable->setItem(rowRayon, 0, newProdLib);
            ui->prodTable->setItem(rowRayon, 1, newProdVariete);

            QPixmap sonimage(prodPhoto);
            QLabel *image = new QLabel("", this);
            image->setParent(ui->prodTable);
            image->setPixmap(sonimage.scaled(50,50,Qt::KeepAspectRatio));
            image->setVisible(true);


            ui->prodTable->setCellWidget(rowRayon, 2, image);


            ui->prodTable->setItem(rowRayon, 3, newProdDLC);
            ui->prodTable->setItem(rowRayon, 4, newProdProdu);
            ui->prodTable->setItem(rowRayon, 5, newProdQTE);
            ui->prodTable->setItem(rowRayon, 6, newProdPrix);
            ui->prodTable->setItem(rowRayon, 7, newProdDesc);


            rowRayon++;
        }

    }
    else {
        ui->rayonSuppr->setEnabled(false);
        ui->prodAnnul->setEnabled(false);
        ui->prodAdd->setEnabled(false);
        ui->prodModif->setEnabled(false);
        ui->prodSuppr->setEnabled(false);
        ui->rayonDesc->setText("");
        ui->nbResultatProduits->setText("");

        ui->prodTable->clearContents();
        ui->prodTable->setRowCount(0);

    }

}


void MainWindow::on_rayonSuppr_clicked()
{

    if(ui->choixRayon->currentIndex()==0)
    {

    }
    else
    {

        dialogSupprRayons supprRayon;

        QString idASuppr= ui->choixRayon->currentData().toString();

        QSqlQuery requeteVerifRayon("select count(*) from Produit inner join Variete on Produit.produitID=Variete.produitID where rayID="+idASuppr);


        requeteVerifRayon.first();



        if(requeteVerifRayon.value(0).toInt()==0)
        {
            dialogSupprRayons supprProduit;

            if(supprProduit.exec())
            {
                QSqlQuery requeteSupprRayon("DELETE FROM Rayon where rayID="+idASuppr);
            }
            remplirRayons();
            ui->rayonDesc->setText("");
        }
        else
        {
            if(requeteVerifRayon.value(0).toInt()>0)
            {
                /* Remplissage du tableau d'ID des produits de ce rayon */
                QSqlQuery lesId("select prodID from Produit inner join Variete on Produit.produitID=Variete.produitID where rayID="+idASuppr);

                vector<QString> vectDesProduits;
                vectDesProduits.clear();

                while(lesId.next())
                {
                    vectDesProduits.push_back(lesId.value(0).toString());
                    qDebug()<< "VectProduit id : "+lesId.value(0).toString();
                }



                DialogChoixDeplacerOuSupprProd nvDialogChoixSupprRayon;
                if(nvDialogChoixSupprRayon.exec())
                {
                    QString queFaire = nvDialogChoixSupprRayon.actionSupprRayonPlein;
                    if (queFaire=="deplacer")
                    {
                        DialogDeplacerProduitsDeRayons nvDialogDeplacerProduits;
                        nvDialogDeplacerProduits.setIDRayon(idASuppr);
                        if (nvDialogDeplacerProduits.exec())
                        {

                        }
                    }
                    else
                    {
                        if (queFaire== "suppr")
                        {
                            for(int i=0 ; i < vectDesProduits.size() ; i++)
                            {
                                QSqlQuery requeteSupprRayon("DELETE FROM Variete where prodID="+vectDesProduits[i]);
                                qDebug()<<"Produit "+vectDesProduits[i]+" a été supprimer";
                            }
                            QSqlQuery requeteSupprRayon("DELETE FROM Rayon where rayID="+idASuppr);
                            remplirRayons();


                        }
                        else
                        {

                        }
                    }
                }
                else
                {

                }
                remplirRayons();
                ui->rayonDesc->setText("");

            }

        }

    }

}



void MainWindow::on_prodModif_clicked()
{
    DialogModifProduits modifProd(this,tableSelectedID, nomRayon);

    //modifProd.setIDProd(tableSelectedID);
    if(modifProd.exec())
    {

    }
    int currentIndex=ui->choixRayon->currentIndex();
    remplirRayons();
    ui->choixRayon->setCurrentIndex(currentIndex);

}

void MainWindow::on_prodAdd_clicked()
{
    DialogAjoutProduits nvProduit;
    QString rayon=ui->choixRayon->currentText();

    nvProduit.idRayon=ui->choixRayon->currentData().toString();
    nvProduit.remplirComboBoxProduit();
    nvProduit.exec();
    on_choixRayon_currentIndexChanged(rayon);
    int currentIndex=ui->choixRayon->currentIndex();
    remplirRayons();
    ui->choixRayon->setCurrentIndex(currentIndex);
}


void MainWindow::on_prodTable_itemSelectionChanged()
{
    tableSelectedID= ui->prodTable->model()->data(ui->prodTable->model()->index(ui->prodTable->currentIndex().row(),0)).toString();
    if(ui->prodTable->selectedItems().size()!=0)
    {
        if (!tableSelectedID.isEmpty())
        {
            ui->prodModif->setEnabled(true);
            ui->prodAnnul->setEnabled(true);
            ui->prodSuppr->setEnabled(true);
        }
        else
        {
            ui->prodModif->setEnabled(false);
            ui->prodAnnul->setEnabled(false);
            ui->prodSuppr->setEnabled(false);
        }
    }
    else
    {
        ui->prodModif->setEnabled(false);
        ui->prodAnnul->setEnabled(false);
        ui->prodSuppr->setEnabled(false);
    }
}

void MainWindow::on_prodSuppr_clicked()
{
    DialogVerifSupprProduit supprProduit;
    QString rayon=ui->choixRayon->currentText();
    if(supprProduit.exec())
    {
        QSqlQuery reqSupprProduit("delete from Variete where prodID="+tableSelectedID);
    }

    on_choixRayon_currentIndexChanged(rayon);
}



void MainWindow::on_prodAnnul_clicked()
{
    ui->prodTable->clearSelection();
}


//--------------------------------------------------------------TAB 2-------------------------------------------------------------//


void MainWindow::remplirProducteurs(QString leLib)
{

    QSqlQuery reqproducteur;
    if (leLib.length()>=1)
    {
        ui->rayonDesc->setText("");
        ui->prodAdd->setEnabled(false);
        ui->rayonSuppr->setEnabled(false);
        qDebug()<<"Recherche de : "+leLib;

        reqproducteur.prepare("SELECT * from PRODUCTEURS inner join ENTREPRISE on producteurEntreprise=entreID where producteurNom like '%"+leLib+"%' or producteurPrenom like '%"+leLib+"%' or producteurLogin like '%"+leLib+"%' or producteurEmail like '%"+leLib+"%' or prodTelFix like '%"+leLib+"%' or prodTelPort like '%"+leLib+"%'");
        qDebug()<<"SELECT * from PRODUCTEURS inner join ENTREPRISE on producteurEntreprise=entreID where producteurNom like '%"+leLib+"%' or producteurPrenom like '%"+leLib+"%' or producteurLogin like '%"+leLib+"%' or producteurEmail like '%"+leLib+"%' or prodTelFix like '%"+leLib+"%' or prodTelPort like '%"+leLib+"%'";

    }
    else
    {
        reqproducteur.prepare("SELECT * from PRODUCTEURS inner join ENTREPRISE on producteurEntreprise=entreID");
    }
    reqproducteur.exec();



    ui->producteurAdd->setEnabled(true);
    //QSqlQuery reqproducteur("SELECT * from PRODUCTEURS inner join ENTREPRISE on producteurEntreprise=entreID");

    int nbResultats = reqproducteur.size();
    QString nbResultatsStringProducteur = QString::number(nbResultats);
    ui->nbResultatProducteur->setText(nbResultatsStringProducteur+tr(" Producer(s)."));

    ui->producteurTable->clearContents();


    ui->producteurTable->setRowCount(0);
    int rowProducteur=0;
    while (reqproducteur.next())
    {

        int rowCount=ui->producteurTable->rowCount();
        ui->producteurTable->setRowCount(rowCount+1);


        QString producteurID=reqproducteur.value("producteurID").toString();
        QString producteurNom=reqproducteur.value("producteurNom").toString();
        QString producteurPrenom=reqproducteur.value("producteurPrenom").toString();
        QString producteurLogin=reqproducteur.value("producteurLogin").toString();
        QString producteurEmail=reqproducteur.value("producteurEmail").toString();
        QString producteurEntrepriseID=reqproducteur.value("entreID").toString();
        QString producteurEntreprise=reqproducteur.value("entreNom").toString();
        QString producteurEntrepriseSiret=reqproducteur.value("entreSiret").toString();
        QString producteurTelFix=reqproducteur.value("prodTelFix").toString();
        QString producteurtelPort=reqproducteur.value("prodtelPort").toString();
        QString producteurAdresse=reqproducteur.value("prodAdresse").toString();
        QString producteurVille=reqproducteur.value("prodVille").toString();
        QString producteurCP=reqproducteur.value("prodCP").toString();
        QString producteurConfirmEmail=reqproducteur.value("prodConfirmMail").toString();
        QString producteurConfirm=reqproducteur.value("prodConfirm").toString();




        QTableWidgetItem* newProducteurID = new QTableWidgetItem();
        newProducteurID->setText(producteurID);

        QTableWidgetItem* newProducteurNom = new QTableWidgetItem();
        newProducteurNom->setText(producteurNom);

        QTableWidgetItem* newProducteurPrenom = new QTableWidgetItem();
        newProducteurPrenom->setText(producteurPrenom);

        QTableWidgetItem* newProducteurLogin = new QTableWidgetItem();
        newProducteurLogin->setText(producteurLogin);

        QTableWidgetItem* newProducteurEmail = new QTableWidgetItem();
        newProducteurEmail->setText(producteurEmail);

        QTableWidgetItem* newProducteurEntrepriseID = new QTableWidgetItem();
        newProducteurEntrepriseID->setText(producteurEntrepriseID);

        QTableWidgetItem* newProducteurEntreprise = new QTableWidgetItem();
        newProducteurEntreprise->setText(producteurEntreprise);

        QTableWidgetItem* newProducteurEntrepriseSiret = new QTableWidgetItem();
        newProducteurEntrepriseSiret->setText(producteurEntrepriseSiret);

        QTableWidgetItem* newProducteurTelFix = new QTableWidgetItem();
        newProducteurTelFix->setText(producteurTelFix);

        QTableWidgetItem* newProducteurtelPort = new QTableWidgetItem();
        newProducteurtelPort->setText(producteurtelPort);

        QTableWidgetItem* newProducteurAdresse = new QTableWidgetItem();
        newProducteurAdresse->setText(producteurAdresse);

        QTableWidgetItem* newProducteurVille = new QTableWidgetItem();
        newProducteurVille->setText(producteurVille);

        QTableWidgetItem* newProducteurCP = new QTableWidgetItem();
        newProducteurCP->setText(producteurCP);

        QTableWidgetItem* newProducteurConfirmEmail = new QTableWidgetItem();
        newProducteurConfirmEmail->setText(producteurConfirmEmail);

        QTableWidgetItem* newProducteurConfirm = new QTableWidgetItem();
        newProducteurConfirm->setText(producteurConfirm);



        ui->producteurTable->setItem(rowProducteur, 0, newProducteurID);
        ui->producteurTable->setItem(rowProducteur, 1, newProducteurNom);
        ui->producteurTable->setItem(rowProducteur, 2, newProducteurPrenom);
        ui->producteurTable->setItem(rowProducteur, 3, newProducteurLogin);
        ui->producteurTable->setItem(rowProducteur, 4, newProducteurEmail);
        ui->producteurTable->setItem(rowProducteur, 5, newProducteurEntrepriseID);
        ui->producteurTable->setItem(rowProducteur, 6, newProducteurEntreprise);
        ui->producteurTable->setItem(rowProducteur, 7, newProducteurEntrepriseSiret);
        ui->producteurTable->setItem(rowProducteur, 8, newProducteurTelFix);
        ui->producteurTable->setItem(rowProducteur, 9, newProducteurtelPort);
        ui->producteurTable->setItem(rowProducteur, 10, newProducteurAdresse);
        ui->producteurTable->setItem(rowProducteur, 11, newProducteurVille);
        ui->producteurTable->setItem(rowProducteur, 12, newProducteurCP);
        ui->producteurTable->setItem(rowProducteur, 13, newProducteurConfirmEmail);
        ui->producteurTable->setItem(rowProducteur, 14, newProducteurConfirm);





        rowProducteur++;
    }
    ui->producteurTable->hideColumn(0);
    ui->producteurTable->hideColumn(5);

    /*ui->producteurAdd->setEnabled(false);
    ui->producteurModif->setEnabled(false);
    ui->producteurSuppr->setEnabled(false);
    ui->nbResultatProducteur->setText("");

    ui->producteurTable->clearContents();
    ui->producteurTable->setRowCount(0);
*/
}

void MainWindow::remplirProducteursEntreprises(QString leLibEntre)
{

    QSqlQuery reqproducteurEntre;
    if (leLibEntre.length()>=1)
    {
        qDebug()<<"Recherche de : "+leLibEntre;

        reqproducteurEntre.prepare("SELECT * from ENTREPRISE where entreNom like '%"+leLibEntre+"%' or entreSiret like '%"+leLibEntre+"%'");
        qDebug()<<"";
    }
    else
    {
        reqproducteurEntre.prepare("SELECT * from ENTREPRISE");
    }
    reqproducteurEntre.exec();


    //QSqlQuery reqproducteurNonConfirm("SELECT * from ENTREPRISE");

    int nbResultatsNonVerif = reqproducteurEntre.size();
    QString nbResultatsNonVerifStringProducteur = QString::number(nbResultatsNonVerif);
    ui->nbResultatEntreprises->setText(nbResultatsNonVerifStringProducteur+tr(" Companies."));

    ui->producteurTableEntreprise->clearContents();


    ui->producteurTableEntreprise->setRowCount(0);
    int rowProducteurNonVerif=0;
    while (reqproducteurEntre.next())
    {

        int rowCount=ui->producteurTableEntreprise->rowCount();
        ui->producteurTableEntreprise->setRowCount(rowCount+1);


        QString entreID=reqproducteurEntre.value("entreID").toString();
        QString entreNom=reqproducteurEntre.value("entreNom").toString();
        QString entreSiret=reqproducteurEntre.value("entreSiret").toString();




        QTableWidgetItem* newEntreID = new QTableWidgetItem();
        newEntreID->setText(entreID);

        QTableWidgetItem* newEntreNom = new QTableWidgetItem();
        newEntreNom->setText(entreNom);

        QTableWidgetItem* newEntreSiret = new QTableWidgetItem();
        newEntreSiret->setText(entreSiret);




        ui->producteurTableEntreprise->setItem(rowProducteurNonVerif, 0, newEntreID);
        ui->producteurTableEntreprise->setItem(rowProducteurNonVerif, 1, newEntreNom);
        ui->producteurTableEntreprise->setItem(rowProducteurNonVerif, 2, newEntreSiret);





        rowProducteurNonVerif++;
    }
    ui->producteurTableEntreprise->hideColumn(0);

}


void MainWindow::on_producteurTable_itemSelectionChanged()
{
    tableProdConfirmSelectedID= ui->producteurTable->model()->data(ui->producteurTable->model()->index(ui->producteurTable->currentIndex().row(),0)).toString();
    if(ui->producteurTable->selectedItems().size()!=0)
    {
        if (!tableProdConfirmSelectedID.isEmpty())
        {
            ui->producteurVerif->setEnabled(true);
            ui->producteurModif->setEnabled(true);
            ui->producteurSuppr->setEnabled(true);
            ui->producteurAnnul->setEnabled(true);
        }
        else
        {
            ui->producteurVerif->setEnabled(false);
            ui->producteurModif->setEnabled(false);
            ui->producteurSuppr->setEnabled(false);
            ui->producteurAnnul->setEnabled(false);
        }
    }
    else
    {
        ui->producteurVerif->setEnabled(false);
        ui->producteurModif->setEnabled(false);
        ui->producteurSuppr->setEnabled(false);
        ui->producteurAnnul->setEnabled(false);
    }
}


void MainWindow::on_producteurAnnul_clicked()
{
    ui->producteurTable->clearSelection();
}


void MainWindow::on_producteurAdd_clicked()
{
    DialogAjoutProducteur nvProducteur;
    nvProducteur.exec();
    remplirProducteurs("");
    remplirProducteursEntreprises("");

}

void MainWindow::on_producteurModif_clicked()
{
    QString idDuProd=ui->producteurTable->model()->data(ui->producteurTable->model()->index(ui->producteurTable->currentIndex().row(),0)).toString();
    DialogModifProducteur modProducteur(idDuProd);
    modProducteur.exec();
    remplirProducteurs("");
}

void MainWindow::on_producteurSuppr_clicked()
{
    DialogVerifSupprProducteur supprProducteur;
    if(supprProducteur.exec())
    {
        //Verification si le Producteur a des produits
        QSqlQuery verifProd("select count(*) from PRODUITS where producteurID="+tableProdConfirmSelectedID);
        verifProd.first();

        QSqlQuery entrepriseDuProd("select producteurEntreprise from PRODUCTEURS where producteurID="+tableProdConfirmSelectedID);
        entrepriseDuProd.first();
        QString entreID=entrepriseDuProd.value(0).toString();
        qDebug()<<"entreid = "+entreID;

        if(verifProd.value(0).toInt()<1)
        {
            QSqlQuery reqSupprProducteur("delete from PRODUCTEURS where producteurID="+tableProdConfirmSelectedID);
            QSqlQuery reqSupprEntreprise("delete from ENTREPRISE where entreID="+entreID);
        }
        else
        {
            QSqlQuery reqSupprProduits("delete from PRODUITS where producteurID="+tableProdConfirmSelectedID);
            QSqlQuery reqSupprProducteur("delete from PRODUCTEURS where producteurID="+tableProdConfirmSelectedID);
            QSqlQuery reqSupprEntreprise("delete from ENTREPRISE where entreID="+entreID);

        }

    }
    remplirProducteurs("");
    remplirProducteursEntreprises("");
    QString libelleRayon=ui->choixRayon->currentText();
    on_choixRayon_currentIndexChanged(libelleRayon);
}

void MainWindow::on_verifMode_clicked(bool reload=false)
{
    qDebug()<<"void MainWindow::on_verifMode_clicked(bool reload=false)";

    qDebug()<<"verif mode";
    if(!checked || reload)
    {
        qDebug()<<"On";
        ui->verifMode->setText(tr("VERIFICATION MODE = On"));
        ui->producteurVerif->setVisible(true);
        ui->producteurAdd->setVisible(false);
        ui->producteurSuppr->setVisible(false);
        ui->producteurModif->setVisible(false);
        ui->producteurAnnul->setVisible(false);

        ui->producteurAdd->setEnabled(true);
        QSqlQuery reqproducteur("SELECT * from PRODUCTEURS inner join ENTREPRISE on producteurEntreprise=entreID where prodConfirm=0");

        int nbResultats = reqproducteur.size();
        QString nbResultatsStringProducteur = QString::number(nbResultats);
        ui->nbResultatProducteur->setText(nbResultatsStringProducteur+tr(" Producer(s)."));

        ui->producteurTable->clearContents();


        ui->producteurTable->setRowCount(0);
        int rowProducteur=0;
        while (reqproducteur.next())
        {

            int rowCount=ui->producteurTable->rowCount();
            ui->producteurTable->setRowCount(rowCount+1);


            QString producteurID=reqproducteur.value("producteurID").toString();
            QString producteurNom=reqproducteur.value("producteurNom").toString();
            QString producteurPrenom=reqproducteur.value("producteurPrenom").toString();
            QString producteurLogin=reqproducteur.value("producteurLogin").toString();
            QString producteurEmail=reqproducteur.value("producteurEmail").toString();
            QString producteurEntrepriseID=reqproducteur.value("entreID").toString();
            QString producteurEntreprise=reqproducteur.value("entreNom").toString();
            QString producteurEntrepriseSiret=reqproducteur.value("entreSiret").toString();
            QString producteurTelFix=reqproducteur.value("prodTelFix").toString();
            QString producteurtelPort=reqproducteur.value("prodtelPort").toString();
            QString producteurAdresse=reqproducteur.value("prodAdresse").toString();
            QString producteurVille=reqproducteur.value("prodVille").toString();
            QString producteurCP=reqproducteur.value("prodCP").toString();
            QString producteurConfirmEmail=reqproducteur.value("prodConfirmMail").toString();
            QString producteurConfirm=reqproducteur.value("prodConfirm").toString();




            QTableWidgetItem* newProducteurID = new QTableWidgetItem();
            newProducteurID->setText(producteurID);

            QTableWidgetItem* newProducteurNom = new QTableWidgetItem();
            newProducteurNom->setText(producteurNom);

            QTableWidgetItem* newProducteurPrenom = new QTableWidgetItem();
            newProducteurPrenom->setText(producteurPrenom);

            QTableWidgetItem* newProducteurLogin = new QTableWidgetItem();
            newProducteurLogin->setText(producteurLogin);

            QTableWidgetItem* newProducteurEmail = new QTableWidgetItem();
            newProducteurEmail->setText(producteurEmail);

            QTableWidgetItem* newProducteurEntrepriseID = new QTableWidgetItem();
            newProducteurEntrepriseID->setText(producteurEntrepriseID);

            QTableWidgetItem* newProducteurEntreprise = new QTableWidgetItem();
            newProducteurEntreprise->setText(producteurEntreprise);

            QTableWidgetItem* newProducteurEntrepriseSiret = new QTableWidgetItem();
            newProducteurEntrepriseSiret->setText(producteurEntrepriseSiret);

            QTableWidgetItem* newProducteurTelFix = new QTableWidgetItem();
            newProducteurTelFix->setText(producteurTelFix);

            QTableWidgetItem* newProducteurtelPort = new QTableWidgetItem();
            newProducteurtelPort->setText(producteurtelPort);

            QTableWidgetItem* newProducteurAdresse = new QTableWidgetItem();
            newProducteurAdresse->setText(producteurAdresse);

            QTableWidgetItem* newProducteurVille = new QTableWidgetItem();
            newProducteurVille->setText(producteurVille);

            QTableWidgetItem* newProducteurCP = new QTableWidgetItem();
            newProducteurCP->setText(producteurCP);

            QTableWidgetItem* newProducteurConfirmEmail = new QTableWidgetItem();
            newProducteurConfirmEmail->setText(producteurConfirmEmail);

            QTableWidgetItem* newProducteurConfirm = new QTableWidgetItem();
            newProducteurConfirm->setText(producteurConfirm);



            ui->producteurTable->setItem(rowProducteur, 0, newProducteurID);
            ui->producteurTable->setItem(rowProducteur, 1, newProducteurNom);
            ui->producteurTable->setItem(rowProducteur, 2, newProducteurPrenom);
            ui->producteurTable->setItem(rowProducteur, 3, newProducteurLogin);
            ui->producteurTable->setItem(rowProducteur, 4, newProducteurEmail);
            ui->producteurTable->setItem(rowProducteur, 5, newProducteurEntrepriseID);
            ui->producteurTable->setItem(rowProducteur, 6, newProducteurEntreprise);
            ui->producteurTable->setItem(rowProducteur, 7, newProducteurEntrepriseSiret);
            ui->producteurTable->setItem(rowProducteur, 8, newProducteurTelFix);
            ui->producteurTable->setItem(rowProducteur, 9, newProducteurtelPort);
            ui->producteurTable->setItem(rowProducteur, 10, newProducteurAdresse);
            ui->producteurTable->setItem(rowProducteur, 11, newProducteurVille);
            ui->producteurTable->setItem(rowProducteur, 12, newProducteurCP);
            ui->producteurTable->setItem(rowProducteur, 13, newProducteurConfirmEmail);
            ui->producteurTable->setItem(rowProducteur, 14, newProducteurConfirm);





            rowProducteur++;
        }
        checked=true;

    }
    else
    {
        ui->producteurVerif->setVisible(false);
        ui->producteurAdd->setVisible(true);
        ui->producteurSuppr->setVisible(true);
        ui->producteurModif->setVisible(true);
        ui->producteurAnnul->setVisible(true);
        ui->verifMode->setText(tr("VERIFICATION MODE = Off"));
        qDebug()<<"Off";
        remplirProducteurs("");
        checked=false;
    }
    ui->producteurTable->hideColumn(0);
    ui->producteurTable->hideColumn(5);
}



void MainWindow::on_producteurRecherche_textEdited(const QString &arg1)
{
    if (ui->producteurRecherche->text().length()==0)
    {
        ui->producteurVerif->setEnabled(false);
        ui->producteurAdd->setEnabled(false);
        ui->producteurSuppr->setEnabled(false);
        ui->producteurModif->setEnabled(false);
        ui->producteurAnnul->setEnabled(false);

        ui->nbResultatProducteur->setText("");

        ui->producteurTable->clearContents();
        ui->producteurTable->setRowCount(0);
    }

    remplirProducteurs(arg1);
}

void MainWindow::on_producteurRechercheEntreprises_textEdited(const QString &arg1)
{
    if (ui->producteurRechercheEntreprises->text().length()==0)
    {

        ui->nbResultatEntreprises->setText("");

        ui->producteurTableEntreprise->clearContents();
        ui->producteurTableEntreprise->setRowCount(0);
    }


    remplirProducteursEntreprises(arg1);
}


void MainWindow::on_producteurVerif_clicked()
{
    QSqlQuery verifProd("update PRODUCTEURS set prodConfirm=1 where producteurID="+tableProdConfirmSelectedID);
    on_verifMode_clicked(true);
    QSqlQuery nbProdNonVerif("select count(*) from PRODUCTEURS where prodConfirm=0");
    nbProdNonVerif.first();
    if(nbProdNonVerif.value(0).toInt()==0)
    {
        ui->producteurVerif->setVisible(false);
        ui->producteurAdd->setVisible(true);
        ui->producteurSuppr->setVisible(true);
        ui->producteurModif->setVisible(true);
        ui->producteurAnnul->setVisible(true);
        ui->verifMode->setText(tr("VERIFICATION MODE = Off"));
        qDebug()<<"Off";
        remplirProducteurs("");
        checked=false;
    }
}


//--------------------------------------------------------------TAB 2-------------------------------------------------------------//


void MainWindow::remplirAdmins(QString leLib)
{

    QSqlQuery reqAdmin;
    if (leLib.length()>=1)
    {
        /*
        ui->rayonDesc->setText("");
        ui->prodAdd->setEnabled(false);
        ui->rayonSuppr->setEnabled(false);
*/
        qDebug()<<"Recherche de : "+leLib;

        reqAdmin.prepare("SELECT * from MODERATEURS where modLogin like '%"+leLib+"%' or modEmail like '%"+leLib+"%'");
        qDebug()<<reqAdmin.lastQuery();
    }
    else
    {
        reqAdmin.prepare("SELECT * from MODERATEURS");
    }
    reqAdmin.exec();



    ui->adminTable->setEnabled(true);

    int nbResultats = reqAdmin.size();
    QString nbResultatsStringAdmin = QString::number(nbResultats);
    ui->nbResultatAdmin->setText(nbResultatsStringAdmin+tr(" Admin(s)."));

    ui->adminTable->clearContents();


    ui->adminTable->setRowCount(0);
    int rowAdmin=0;
    while (reqAdmin.next())
    {

        int rowCount=ui->adminTable->rowCount();
        ui->adminTable->setRowCount(rowCount+1);


        QString adminID=reqAdmin.value(0).toString();
        QString adminLogin=reqAdmin.value(1).toString();
        QString adminEmail=reqAdmin.value(2).toString();
        int adminSU=reqAdmin.value(4).toInt();
        QString adminSUString;
        if(adminSU==1)
        {
            adminSUString="Yes";
        }
        else
        {
            adminSUString="No";
        }


        QTableWidgetItem* newAdminID = new QTableWidgetItem();
        newAdminID->setText(adminID);

        QTableWidgetItem* newAdminLogin = new QTableWidgetItem();
        newAdminLogin->setText(adminLogin);

        QTableWidgetItem* newAdminEmail = new QTableWidgetItem();
        newAdminEmail->setText(adminEmail);

        QTableWidgetItem* newAdminSU = new QTableWidgetItem();
        newAdminSU->setText(adminSUString);


        ui->adminTable->setItem(rowAdmin, 0, newAdminID);
        ui->adminTable->setItem(rowAdmin, 1, newAdminLogin);
        ui->adminTable->setItem(rowAdmin, 2, newAdminSU);
        ui->adminTable->setItem(rowAdmin, 3, newAdminEmail);

        rowAdmin++;
    }
    ui->adminTable->hideColumn(0);
}

void MainWindow::on_adminRecherche_textEdited(const QString &arg1)
{
    if (ui->adminRecherche->text().length()==0)
    {

        ui->nbResultatEntreprises->setText("");

        ui->adminTable->clearContents();
        ui->adminTable->setRowCount(0);
    }


    remplirAdmins(arg1);
}

void MainWindow::on_adminTable_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_adminTable_itemSelectionChanged()";
    tableAdminSelectedID= ui->producteurTable->model()->data(ui->producteurTable->model()->index(ui->producteurTable->currentIndex().row(),0)).toString();
    qDebug()<<tableAdminSelectedID;
    if(ui->adminTable->selectedItems().size()!=0)
    {

        ui->adminModif->setEnabled(true);
        ui->adminRemove->setEnabled(true);
        ui->adminAnnul->setEnabled(true);
    }
    else
    {

        ui->adminModif->setEnabled(false);
        ui->adminRemove->setEnabled(false);
        ui->adminAnnul->setEnabled(false);
    }

}

void MainWindow::on_adminRemove_clicked()
{
    qDebug()<<"void MainWindow::on_adminRemove_clicked()";
    QString loginAdminSelected=ui->producteurTable->model()->data(ui->producteurTable->model()->index(ui->producteurTable->currentIndex().row(),1)).toString();
    int supprAdmin = QMessageBox::warning(this, "NewWorld" ,tr("Do you really want to delete ?")+loginAdminSelected, QMessageBox::Yes, QMessageBox::No);


    switch (supprAdmin)
    {
    case QMessageBox::Yes:
    {
        QSqlQuery supprAdmin("delete from MODERATEURS where modID="+tableAdminSelectedID);
        break;
    }

    default:
        break;
    }
}

void MainWindow::on_adminAnnul_clicked()
{
    ui->adminTable->clearSelection();
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox::aboutQt(this, "NewWorld");
}

void MainWindow::on_actionDocumentation_triggered()
{
    /*
    DialogDocumentation nvDoc;
    nvDoc.exec();
    */
    QUrl urlDoc;

    QString nomDuPays= QLocale::system().name().left(2);
    urlDoc.setUrl("./documentation_"+nomDuPays+".html");
    //ui->textBrowser->setSource(urlDoc);
    QDesktopServices::openUrl(urlDoc);
}
