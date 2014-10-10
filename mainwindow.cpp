#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui_settingsdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Generate
    ui->setupUi(this);

    settings = new Settings("config.cfg");
    cda = new Cda_Main;

    // Checking player installation. If not installed -> quit;
    if(!cda->getPlayerPath()) {
        QMessageBox::critical(this, "MPlayer not installed!", "MPlayer is not installed (required). Try running after insall MPlayer.", QMessageBox::Ok);
        QApplication::quit();
    }
    // Check / Load / Create Config file
    prepareConfig();

    // Check player path and show information
    // if is not valid
    if(!cda->getPlayerPath())
        QMessageBox::critical(this, "Player not found!", "Application require MPlayer to running.\nPlease install MPlayer and try again.\n(ubuntu ex. sudo apt-get install mplayer)", QMessageBox::Ok);

    ui->player_path->setText(QString::fromStdString(settings->default_player_path));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::prepareConfig()
{
    if(settings->configFileExist()) {
        if(!settings->loadConfig()) {
            QMessageBox::critical(this, "Config file problem!", QString("I found config and cannot read this file :(\nTry delete file "+QString::fromStdString(settings->file_name)+" and run application again."), QMessageBox::Ok);
            if(!settings->createConfig()) {
                QMessageBox::critical(this, "Create config problem!", "Cannot create default config file.", QMessageBox::Ok);
            }
        }
    }else {
        QMessageBox::critical(this, "Config file not found!", "This is first running application.\nI must create new config file now.", QMessageBox::Ok);
        if(!settings->createConfig())
            QMessageBox::critical(this, "Create config problem!", "Cannot create default config file.", QMessageBox::Ok);
    }
}

void MainWindow::on_play_button_clicked()
{
    // Check typed information before playing
    if(ui->movie_url->text().isEmpty()) {
        QMessageBox::warning(this, "Movie URL", "Please enter url from cda.pl.", QMessageBox::Ok);
        return;
    }else if(ui->player_path->text().isEmpty()) {
        QMessageBox::warning(this, "Player PATH", "Please enter path to your player.", QMessageBox::Ok);
        return;
    }

    ui->centralWidget->setEnabled(false);

    cda->movie_site = ui->movie_url->text().toStdString();;
    cda->player_path = settings->default_player_path;

    // Prepare information
    // and play movie
    if(cda->prepare()) {
        if(!cda->openPlayer())
            QMessageBox::critical(this, "Player running...", "Something is wrong :(\n"+QString::fromStdString(cda->error), QMessageBox::Ok);
    }else
        QMessageBox::critical(this, "Error", QString("URL:\n"+ui->movie_url->text()+"\nThis URL is incorrect. Check URL and try again."), QMessageBox::Ok);

    ui->centralWidget->setEnabled(true);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionInfo_triggered()
{
    InfoDialog info;
    info.exec();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog settings_dialog(settings->default_player_path);

    switch(settings_dialog.exec())
    {
    case QDialog::Accepted:
        settings->default_player_path = settings_dialog.ui->player_path->text().toStdString();
        if(settings->saveConfig()) {
            ui->player_path->setText(QString::fromStdString(settings->default_player_path));
            cout << "Config Saved!" << endl;
        }else
            cout << "Error not saved." << endl;

        break;
    }

}
