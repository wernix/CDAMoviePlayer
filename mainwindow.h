#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <infodialog.h>
#include <settingsdialog.h>

#include <QMainWindow>
#include <QMessageBox>

#include <cdamain.h>
#include <settings.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_play_button_clicked();

    void on_actionQuit_triggered();

    void on_actionInfo_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    Cda_Main *cda;
    Settings *settings;
    void prepareConfig();
};

#endif // MAINWINDOW_H
