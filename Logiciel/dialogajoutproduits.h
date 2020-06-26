#ifndef DIALOGAJOUTPRODUITS_H
#define DIALOGAJOUTPRODUITS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class DialogAjoutProduits;
}

class DialogAjoutProduits : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutProduits(QWidget *parent = nullptr);
    ~DialogAjoutProduits();
    QString idRayon;
    void testFormComplet();
    void remplirComboBoxProduit();

private slots:
    void on_pushButton_clicked();

    void on_prodLib_textEdited(const QString &arg1);

    void on_prodDesc_textEdited(const QString &arg1);

    void on_prodPU_valueChanged(double arg1);

    void on_pushButton_3_clicked();

    void on_boutonAnnuler_clicked();

    void on_comboBoxProd_currentIndexChanged(int index);

    void on_comboBoxProduit_currentIndexChanged(int index);


    void on_comboBoxUnite_currentIndexChanged(int index);

    void on_lineEditQTE_textEdited(const QString &arg1);

    void on_lineEditQTEMin_textEdited(const QString &arg1);

private:
    Ui::DialogAjoutProduits *ui;
    bool sonLibBool;
    bool saPhotoBool;
    bool saDescBool;
    bool sonPrixBool;
    bool sonUniteBool;
    bool sonLineEditQTE;
    QString nomFichierImage;

};

#endif // DIALOGAJOUTPRODUITS_H
