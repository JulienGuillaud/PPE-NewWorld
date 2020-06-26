#ifndef DIALOGDEPLACERPRODUITSDERAYONS_H
#define DIALOGDEPLACERPRODUITSDERAYONS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class DialogDeplacerProduitsDeRayons;
}

class DialogDeplacerProduitsDeRayons : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDeplacerProduitsDeRayons(QWidget *parent = nullptr);
    ~DialogDeplacerProduitsDeRayons();
    void testFormComplet();
    void setIDRayon(QString idRayon);

private slots:
    void on_ajoutPhotoRayon_clicked();

    void on_lineEditLib_textEdited(const QString &arg1);

    void on_lineEditDesc_textEdited(const QString &arg1);

    void on_pushButtonAjouterEtDeplacer_clicked();

    void on_pushButtonDeplacer_clicked();

    void on_comboBoxRayons_currentIndexChanged(const QString &arg1);

    void on_annuler_clicked();

    void on_radioButtonNvRayon_toggled(bool checked);

    void on_radioButtonDeplacement_toggled(bool checked);

private:
    Ui::DialogDeplacerProduitsDeRayons *ui;
    QString nomFichierImage;
    bool saPhotoBool;
    bool sonLibBool;
    bool saDescBool;
    QString idDuRayon;
};

#endif // DIALOGDEPLACERPRODUITSDERAYONS_H
