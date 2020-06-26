#include "dialogdocumentation.h"
#include "ui_dialogdocumentation.h"
#include <QDesktopServices>

DialogDocumentation::DialogDocumentation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDocumentation)
{
    ui->setupUi(this);

    QUrl urlDoc;

    QString nomDuPays= QLocale::system().name().left(2);
    urlDoc.setUrl("./documentation_"+nomDuPays+".html");
    //ui->textBrowser->setSource(urlDoc);
    QDesktopServices::openUrl(urlDoc);

reject();


}

DialogDocumentation::~DialogDocumentation()
{
    delete ui;
}

void DialogDocumentation::on_pushButton_clicked()
{
    //ui->textBrowser->reload();
}
