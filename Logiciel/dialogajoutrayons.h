#ifndef DIALOGAJOUTRAYONS_H
#define DIALOGAJOUTRAYONS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class DialogAjoutRayons;
}

class DialogAjoutRayons : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutRayons(QWidget *parent = nullptr);
    ~DialogAjoutRayons();
    void mettreID();
    QString nomRayon;
    void testFormComplet();

private slots:
    void on_pushButton_clicked();

    void on_ajoutPhotoRayon_clicked();

    void on_lineEditLib_textEdited(const QString &arg1);

    void on_lineEditDesc_textEdited(const QString &arg1);

private:
    Ui::DialogAjoutRayons *ui;
    QString nomFichierImage;
    bool saPhotoBool;
    bool sonLibBool;
    bool saDescBool;
};

#endif // DIALOGAJOUTRAYONS_H
