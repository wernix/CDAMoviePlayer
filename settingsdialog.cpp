#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(Settings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings(settings)
{
    ui->setupUi(this);
    prepareWindow();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::prepareWindow()
{
    QStringList playing_mode;
    playing_mode << "window" << "fullscreen";

    // Add playing option to comboBox
    ui->select_mode->addItems(playing_mode);

    // Set MPlayer path
    ui->mplayer_path->setText(QString::fromStdString(settings->mplayer_path));

    // Set playing option
    if(settings->fullscreen_mode)
        ui->select_mode->setCurrentText("fullscreen");
    else
        ui->select_mode->setCurrentText("window");

}

void SettingsDialog::on_buttonBox_accepted()
{
    QString set_mode = ui->select_mode->currentText();
    if(set_mode == "fullscreen")
        settings->fullscreen_mode = true;
    else if(set_mode == "window")
        settings->fullscreen_mode = false;

}
