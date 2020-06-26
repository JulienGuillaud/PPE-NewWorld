#ifndef DIALOGDOCUMENTATION_H
#define DIALOGDOCUMENTATION_H

#include <QDialog>

namespace Ui {
class DialogDocumentation;
}

class DialogDocumentation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDocumentation(QWidget *parent = nullptr);
    ~DialogDocumentation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogDocumentation *ui;
};

#endif // DIALOGDOCUMENTATION_H
