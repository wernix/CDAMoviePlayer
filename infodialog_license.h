#ifndef INFODIALOG_LICENSE_H
#define INFODIALOG_LICENSE_H

#include <QDialog>
#include <QFile>
#include <QDebug>

namespace Ui {
class InfoDialogLicense;
}

class InfoDialogLicense : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialogLicense(QWidget *parent = 0);
    ~InfoDialogLicense();

private slots:
    void on_ok_button_clicked();

private:
    Ui::InfoDialogLicense *ui;
    void loadLicense();
};

#endif // INFODIALOG_LICENSE_H
