#ifndef DIALOGVERIFSUPPRPRODUIT_H
#define DIALOGVERIFSUPPRPRODUIT_H

#include <QDialog>

namespace Ui {
class DialogVerifSupprProduit;
}

class DialogVerifSupprProduit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVerifSupprProduit(QWidget *parent = nullptr);
    ~DialogVerifSupprProduit();

private slots:
    void on_confirmSuppr_clicked();

    void on_cancel_clicked();

private:
    Ui::DialogVerifSupprProduit *ui;
};

#endif // DIALOGVERIFSUPPRPRODUIT_H
