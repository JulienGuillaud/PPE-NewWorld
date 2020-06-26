#include "dialogchoixdeplacerousupprprod.h"
#include "ui_dialogchoixdeplacerousupprprod.h"

DialogChoixDeplacerOuSupprProd::DialogChoixDeplacerOuSupprProd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoixDeplacerOuSupprProd)
{
    ui->setupUi(this);
    actionSupprRayonPlein="canceled";
}

DialogChoixDeplacerOuSupprProd::~DialogChoixDeplacerOuSupprProd()
{
    delete ui;
}

void DialogChoixDeplacerOuSupprProd::on_boutonSuppr_clicked()
{
    accept();
    actionSupprRayonPlein="suppr";
}

void DialogChoixDeplacerOuSupprProd::on_boutonDeplacer_clicked()
{
    accept();
    actionSupprRayonPlein="deplacer";
}

void DialogChoixDeplacerOuSupprProd::on_pushButton_clicked()
{
    reject();
}
