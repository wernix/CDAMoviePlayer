#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QStringList>

#include "settings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    Ui::SettingsDialog *ui;
    explicit SettingsDialog(Settings *settings, QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Settings *settings;

    void prepareWindow();
};

#endif // SETTINGSDIALOG_H
