#ifndef DIALOGVERIFSUPPRPRODUCTEUR_H
#define DIALOGVERIFSUPPRPRODUCTEUR_H

#include <QDialog>

namespace Ui {
class DialogVerifSupprProducteur;
}

class DialogVerifSupprProducteur : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVerifSupprProducteur(QWidget *parent = nullptr);
    ~DialogVerifSupprProducteur();

private slots:
    void on_confirmSuppr_clicked();

    void on_cancel_clicked();

private:
    Ui::DialogVerifSupprProducteur *ui;
};

#endif // DIALOGVERIFSUPPRPRODUCTEUR_H
