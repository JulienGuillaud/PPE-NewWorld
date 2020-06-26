#ifndef DIALOGAJOUTPRODUCTEUR_H
#define DIALOGAJOUTPRODUCTEUR_H

#include <QDialog>

namespace Ui {
class DialogAjoutProducteur;
}

class DialogAjoutProducteur : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutProducteur(QWidget *parent = nullptr);
    ~DialogAjoutProducteur();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEditNom_textEdited(const QString &arg1);

    void on_lineEditPrenom_textEdited(const QString &arg1);

    void on_lineEditLogin_textEdited(const QString &arg1);

    void on_lineEditEmail_textEdited(const QString &arg1);

    void on_lineEditMDP_textEdited(const QString &arg1);

    void on_lineEditTelPort_textEdited(const QString &arg1);

    void on_lineEditTelFix_textEdited(const QString &arg1);

    void on_lineEditAdresse_textEdited(const QString &arg1);

    void on_lineEditVille_textEdited(const QString &arg1);

    void on_lineEditCP_textEdited(const QString &arg1);

    void on_lineEditNomEntre_textEdited(const QString &arg1);

    void on_lineEditSIRET_textEdited(const QString &arg1);

private:
    Ui::DialogAjoutProducteur *ui;
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
    bool nomEntre;
    bool siret;
    void verifToutForm();
    bool ok;
};

#endif // DIALOGAJOUTPRODUCTEUR_H
