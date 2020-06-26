#ifndef CONNECTIONPAGE_H
#define CONNECTIONPAGE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class ConnectionPage;
}

class ConnectionPage : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionPage(QWidget *parent = nullptr);
    ~ConnectionPage();
    int modID;


private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ConnectionPage *ui;
};

#endif // CONNECTIONPAGE_H
