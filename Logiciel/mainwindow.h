#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void remplirRayons();
    void remplirProducteurs(QString leLib);
    void remplirAdmins(QString leLib);
    void remplirProducteursEntreprises(QString leLibEntre);
    QString selectedEntrepriseID;
    QString tableSelectedID;
    QString tableProdConfirmSelectedID;
    QString tableProdEntreprisesSelectedID;
    QString tableAdminSelectedID;
QString nomRayon;
    void setModID(int idMod);
    void updatePagePourAdmin();



private:
    Ui::MainWindow *ui;
    bool connecte;
    int modID;
    bool lvlAdmin;
    void closeEvent(QCloseEvent *event) override;
    bool checked;

private slots:

    void on_rayonAdd_clicked();
    void on_choixRayon_currentIndexChanged(const QString &arg1);
    void on_rayonSuppr_clicked();

    void on_prodAdd_clicked();
    void on_prodTable_itemSelectionChanged();
    void on_prodSuppr_clicked();
    void on_prodModif_clicked();
    void on_producteurTable_itemSelectionChanged();
    void on_prodAnnul_clicked();
    void on_producteurAnnul_clicked();
    void on_prodRecherche_textEdited(const QString &arg1);
    void on_producteurAdd_clicked();
    void on_producteurSuppr_clicked();
    void on_verifMode_clicked(bool reload);
    void on_producteurRecherche_textEdited(const QString &arg1);
    void on_producteurRechercheEntreprises_textEdited(const QString &arg1);
    void on_producteurModif_clicked();
    void on_producteurVerif_clicked();
    void on_adminRecherche_textEdited(const QString &arg1);
    void on_adminTable_itemSelectionChanged();
    void on_adminRemove_clicked();
    void on_adminAnnul_clicked();
    void on_actionQuitter_triggered();
    void on_actionA_propos_triggered();
    void on_actionDocumentation_triggered();
};

#endif // MAINWINDOW_H
