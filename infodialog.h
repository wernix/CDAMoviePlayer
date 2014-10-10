#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

private slots:
    void on_ok_button_clicked();

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
