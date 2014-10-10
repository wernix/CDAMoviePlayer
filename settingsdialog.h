#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QUrl>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(std::string, QWidget *parent = 0);
    ~SettingsDialog();
    Ui::SettingsDialog *ui;
    std::string player_path;

private slots:
    void on_browse_button_clicked();

private:

};

#endif // SETTINGSDIALOG_H
