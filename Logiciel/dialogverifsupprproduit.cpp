#include "dialogverifsupprproduit.h"
#include "ui_dialogverifsupprproduit.h"

DialogVerifSupprProduit::DialogVerifSupprProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVerifSupprProduit)
{
    ui->setupUi(this);
}

DialogVerifSupprProduit::~DialogVerifSupprProduit()
{
    delete ui;
}

void DialogVerifSupprProduit::on_confirmSuppr_clicked()
{
    accept();
}

void DialogVerifSupprProduit::on_cancel_clicked()
{
    reject();
}
