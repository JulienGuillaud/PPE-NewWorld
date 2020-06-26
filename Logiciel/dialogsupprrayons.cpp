#include "dialogsupprrayons.h"
#include "ui_dialogsupprrayons.h"
#include <QtDebug>
#include <QDebug>
#include <ui_dialogsupprrayons.h>

dialogSupprRayons::dialogSupprRayons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSupprRayons)
{
    ui->setupUi(this);
}

dialogSupprRayons::~dialogSupprRayons()
{

    delete ui;
}

void dialogSupprRayons::on_confirmSuppr_clicked()
{
    accept();
}

void dialogSupprRayons::on_cancel_clicked()
{
     reject();
}
