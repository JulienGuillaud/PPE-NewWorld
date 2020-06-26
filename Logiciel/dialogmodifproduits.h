#ifndef DIALOGMODIFPRODUITS_H
#define DIALOGMODIFPRODUITS_H

#include <QDialog>

namespace Ui {
class DialogModifProduits;
}

class DialogModifProduits : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifProduits(QWidget *parent = nullptr,QString noProd="", QString nomRayon="");
    ~DialogModifProduits();
    void setIDProd();

private slots:
    void on_pushButton_clicked();

    void on_boutonAnnuler_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DialogModifProduits *ui;
    QString prodID;
    bool sonLibBool;
    bool saPhotoBool;
    bool saDescBool;
    bool sonPrixBool;
    bool sonUniteBool;
    QString nomFichierImage;
};

#endif // DIALOGMODIFPRODUITS_H
