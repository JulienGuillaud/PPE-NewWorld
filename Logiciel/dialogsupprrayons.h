#ifndef DIALOGSUPPRRAYONS_H
#define DIALOGSUPPRRAYONS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class dialogSupprRayons;
}

class dialogSupprRayons : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSupprRayons(QWidget *parent = nullptr);
    ~dialogSupprRayons();

private slots:
    void on_confirmSuppr_clicked();


    void on_cancel_clicked();

private:
    Ui::dialogSupprRayons *ui;
};

#endif // DIALOGSUPPRRAYONS_H
