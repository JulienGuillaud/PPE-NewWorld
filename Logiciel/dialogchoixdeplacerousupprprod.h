#ifndef DIALOGCHOIXDEPLACEROUSUPPRPROD_H
#define DIALOGCHOIXDEPLACEROUSUPPRPROD_H

#include <QDialog>

namespace Ui {
class DialogChoixDeplacerOuSupprProd;
}

class DialogChoixDeplacerOuSupprProd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoixDeplacerOuSupprProd(QWidget *parent = nullptr);
    ~DialogChoixDeplacerOuSupprProd();
    QString actionSupprRayonPlein;


private slots:


    void on_boutonSuppr_clicked();

    void on_boutonDeplacer_clicked();

    void on_pushButton_clicked();

private:
    Ui::DialogChoixDeplacerOuSupprProd *ui;
};

#endif // DIALOGCHOIXDEPLACEROUSUPPRPROD_H
