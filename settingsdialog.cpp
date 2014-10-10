#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(std::string ppath, QWidget *parent) :
    player_path(ppath),
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->player_path->setText(QString::fromStdString(player_path));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_browse_button_clicked()
{
    QUrl path_to_player = QFileDialog::getOpenFileUrl(this, tr("asd"), QUrl("/"));
    ui->player_path->setText(path_to_player.toLocalFile());
}
