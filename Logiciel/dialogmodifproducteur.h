#ifndef DIALOGMODIFPRODUCTEUR_H
#define DIALOGMODIFPRODUCTEUR_H

#include <QDialog>

namespace Ui {
class DialogModifProducteur;
}

class DialogModifProducteur : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifProducteur(QString idDuProd, QWidget *parent = nullptr);
    ~DialogModifProducteur();
    QString idProd;



private slots:
    void on_pushButtonUpdate_clicked();

    void on_pushButtonCancel_clicked();

    void on_lineEditNom_textEdited(const QString &arg1);

    void on_lineEditPrenom_textEdited(const QString &arg1);

    void on_lineEditLogin_textEdited(const QString &arg1);

    void on_lineEditEmail_textEdited(const QString &arg1);

    void on_lineEditTelPort_textEdited(const QString &arg1);

    void on_lineEditTelFix_textEdited(const QString &arg1);

    void on_lineEditAdresse_textEdited(const QString &arg1);

    void on_lineEditVille_textEdited(const QString &arg1);

    void on_lineEditCP_textEdited(const QString &arg1);

private:
    Ui::DialogModifProducteur *ui;
    bool nom;
    bool prenom;
    bool login;
    bool email;
    bool mdp;
    bool telPort;
    bool telFix;
    bool adresse;
    bool ville;
    bool cp;
    void verifToutForm();
    bool ok;
};

#endif // DIALOGMODIFPRODUCTEUR_H
