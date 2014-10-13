#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QProgressBar>

#include <cdamain.h>
#include <settings.h>
#include <cdasearch.h>
#include <progressbar.h>

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
    void on_search_button_clicked();
    void on_actionQuit_triggered();
    void on_actionInfo_triggered();
    void on_actionSettings_triggered();
    void on_actionEnterKey_triggered();
    void playButtonEnable();
    void playButtonDisable();
    void searchButtonEnable(QString text);

private:
    Ui::MainWindow *ui;
    Cda_Main *cda;

    Settings *settings;
    QStandardItemModel *search_model;
    QProgressBar *progress_bar;

    string last_search_text;

    void prepareConfig();
    void setupWindow();
    void clearSearchResult();
    void errorMsg(QString title, QString text);
    void infoMsg(QString title, QString text);
    void addResult(Cda_Search *search, Progress_Bar *p_bar, int rows, int at = 0);
    bool addPageResult(QString search_text, Progress_Bar *p_bar, int page = 0);
    void addItemResult(int no, string id, string title, string url);
    void removeItemResult(int row);
    void setupSearchResultTable();
    void addActions();
};

#endif // MAINWINDOW_H
