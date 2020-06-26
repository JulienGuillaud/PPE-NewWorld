#include "dialogverifsupprproducteur.h"
#include "ui_dialogverifsupprproducteur.h"

DialogVerifSupprProducteur::DialogVerifSupprProducteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVerifSupprProducteur)
{
    ui->setupUi(this);
}

DialogVerifSupprProducteur::~DialogVerifSupprProducteur()
{
    delete ui;
}

void DialogVerifSupprProducteur::on_confirmSuppr_clicked()
{
    accept();
}

void DialogVerifSupprProducteur::on_cancel_clicked()
{
    reject();
}
