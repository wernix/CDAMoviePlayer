#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "infodialog.h"
#include "ui_infodialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Generate
    ui->setupUi(this);

    settings = new Settings("config.cfg");
    cda = new Cda_Main;

    // Checking player installation. If not installed -> quit;
    if(!settings->mplayer_installed) {
        QMessageBox::critical(this, "MPlayer not installed!", "MPlayer is not installed (required). Try running after insall MPlayer.", QMessageBox::Ok);
        QApplication::quit();
    }
    // Check / Load / Create Config file
    prepareConfig();

    // Check player path and show information if nt installed
    if(!settings->mplayer_installed)
        QMessageBox::critical(this, "Player not found!", "Application require MPlayer to running.\nPlease install MPlayer and try again.\n(Ubuntu ex. sudo apt-get install mplayer)", QMessageBox::Ok);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::prepareConfig()
{
    string config_file_path = settings->file_path;

    if(settings->fileExist(config_file_path)) {
        if(!settings->loadConfig(config_file_path)) {
            QMessageBox::critical(this, "Config file problem!", QString("I found config and cannot read this file :(\nTry delete file "+QString::fromStdString(config_file_path)+" and run application again."), QMessageBox::Ok);
            if(!settings->createConfig(config_file_path)) {
                QMessageBox::critical(this, "Create config problem!", "Cannot create default config file.", QMessageBox::Ok);
            }
        }
    }else {
        QMessageBox::information(this, "Config file not found!", "This is first running application.\nI must create new config file now.", QMessageBox::Ok);
        if(!settings->createConfig(config_file_path))
            QMessageBox::critical(this, "Create config problem!", "Cannot create default config file.", QMessageBox::Ok);
    }
}

void MainWindow::on_play_button_clicked()
{
    QString movie_url = ui->movie_url->text();
    string mplayer_path = settings->mplayer_path;
    bool fullscreen = settings->fullscreen_mode;

    // Check typed information before playing
    if(movie_url.isEmpty()) {
        QMessageBox::warning(this, "Movie URL", "Please enter url from cda.pl.", QMessageBox::Ok);
        return;
    }else if(mplayer_path.empty()) {
        QMessageBox::warning(this, "Player PATH", "Please enter path to your player.", QMessageBox::Ok);
        return;
    }
    // Block application
    ui->centralWidget->setEnabled(false);

    cda->movie_site = movie_url.toStdString();;

    // Prepare information and play movie
    if(cda->prepare()) {
        if(!cda->openPlayer(settings->mplayer_path, fullscreen))
            QMessageBox::critical(this, "Player running...", "Something is wrong :(\n"+QString::fromStdString(cda->error), QMessageBox::Ok);
    }else
        QMessageBox::critical(this, "Error", QString("URL:\n"+movie_url+"\nThis URL is incorrect. Check URL and try again."), QMessageBox::Ok);

    // Unblock application
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
    string config_file_path = settings->file_path;

    SettingsDialog settings_dialog(settings);

    // Block application
    ui->centralWidget->setEnabled(false);

    switch(settings_dialog.exec())
    {
    case QDialog::Accepted:
        if(settings->saveConfig(config_file_path)) {
            if(!settings->loadConfig(config_file_path))
                QMessageBox::critical(this, "Config file problem!", QString("I found config and cannot read this file :(\nTry delete file "+QString::fromStdString(config_file_path)+" and run application again."), QMessageBox::Ok);
        }else
            QMessageBox::critical(this, "Config file problem!", QString("I cannot save config :(\nCheck read-write permission to file "+QString::fromStdString(config_file_path)+" and run application again."), QMessageBox::Ok);

        break;
    }

    // Block application
    ui->centralWidget->setEnabled(true);
}
