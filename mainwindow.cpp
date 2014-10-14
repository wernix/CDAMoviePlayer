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
    ui->setupUi(this);

    settings = new Settings("config.cfg");
    cda = new Cda_Main;

    if(!settings->mplayer_installed) {
        errorMsg("MPlayer not installed!", "MPlayer is not installed (required). Try running after insall MPlayer.");
        QApplication::quit();
    }

    prepareConfig();
    setupWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

// Check / Load / Create config
void MainWindow::prepareConfig()
{
    string cfg_path = settings->cfg_path;

    if(settings->fileExist(cfg_path)) {
        if(!settings->loadConfig(cfg_path)) {
            errorMsg("Config file problem!", QString("I found config and cannot read this file :(\nTry delete file "+QString::fromStdString(cfg_path)+" and run application again."));
            if(!settings->createConfig(cfg_path)) {
                errorMsg("Create config problem!", "Cannot create default config file.");
            }
        }
    }else {
        infoMsg("Config file not found!", "This is first running application.\nI must create new config file now.");
        if(!settings->createConfig(cfg_path))
            errorMsg("Create config problem!", "Cannot create default config file.");
    }
}

void MainWindow::addActions()
{
    connect(ui->search_result, SIGNAL(clicked(QModelIndex)), this, SLOT(playButtonEnable()));
    connect(ui->search_text, SIGNAL(textChanged(QString)), this, SLOT(searchButtonEnable(QString)));
    ui->search_text->addAction(ui->actionEnterKey);
    ui->search_result->addAction(ui->actionEnterKey);
}

void MainWindow::searchButtonEnable(QString text)
{
    if(!text.isEmpty())
        ui->search_button->setEnabled(true);
    else
        ui->search_button->setEnabled(false);
}

void MainWindow::setupSearchResultTable()
{
    QStringList col_list;
    col_list << "" << "ID" << "Title" << "Url";
    ui->search_result->setColumnCount(4);
    ui->search_result->setRowCount(0);
    ui->search_result->setHorizontalHeaderLabels(col_list);
    ui->search_result->setColumnWidth(0, 30);
    ui->search_result->setColumnWidth(1, 100);
    ui->search_result->setColumnWidth(2, 230);
    ui->search_result->setColumnHidden(3, true);
    addItemResult(new Item(0, "Info", "Search and watching your movie", ""));
}

void MainWindow::setupWindow()
{
    addActions();
    setupSearchResultTable();
}

void MainWindow::playButtonEnable() { ui->play_button->setEnabled(true); }

void MainWindow::playButtonDisable() { ui->play_button->setEnabled(false); }

void MainWindow::on_play_button_clicked()
{
    int select_row = ui->search_result->currentRow();
    string movie_title = ui->search_result->model()->index(select_row, 2).data().toString().toStdString();
    string movie_url = ui->search_result->model()->index(select_row, 3).data().toString().toStdString();
    string mplayer_path = settings->mplayer_path;

    cda->movie_site = movie_url;

    Progress_Bar p_bar(2, ui->statusBar);

    if(movie_title == "(more)") {
        int all_row = ui->search_result->rowCount();
        int next_page = (all_row / 24)+1;

        p_bar.resize(all_row-1);
        removeItemResult(all_row-1);

        if(!addPageResult(QString::fromStdString(movie_url), &p_bar, next_page)) {
            removeItemResult(all_row-1);
            cout << movie_url << endl;
        }
        return;
    }

    // Check typed information before playing
    if(movie_url.empty()) {
        infoMsg("Movie URL", "Please select movie to play from search result.");
        return;
    }
    if(mplayer_path.empty()) {
        infoMsg("Player PATH", "Please enter path to your player.");
        return;
    }

    p_bar.upgrade(1);

    // Block application
    ui->centralWidget->setDisabled(true);

    // Prepare information and play movie
    if(cda->prepare()) {
        p_bar.finish();

        if(!cda->openPlayer(settings->mplayer_path, settings->fullscreen_mode))
            errorMsg("Player running...", "Something is wrong :(\n"+QString::fromStdString(cda->error));
    }else
        errorMsg("Error", QString("URL:\n"+QString::fromStdString(movie_url)+"\nThis URL is incorrect. Check URL and try again."));

    // Unblock application
    ui->centralWidget->setEnabled(true);

    p_bar.finish();
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
    SettingsDialog settings_dialog(settings);

    string cfg_path = settings->cfg_path;

    ui->centralWidget->setEnabled(false);

    switch(settings_dialog.exec())
    {
    case QDialog::Accepted:
        if(settings->saveConfig(cfg_path)) {
            if(!settings->loadConfig(cfg_path))
                errorMsg("Config file problem!", QString("I found config and cannot read this file :(\nTry delete file "+QString::fromStdString(cfg_path)+" and run application again."));
        }else
            errorMsg("Config file problem!", QString("I cannot save config :(\nCheck read-write permission to file "+QString::fromStdString(cfg_path)+" and run application again."));

        break;
    }

    ui->centralWidget->setEnabled(true);
}

void MainWindow::clearSearchResult()
{
    ui->search_result->setRowCount(0);
}

void MainWindow::on_search_button_clicked()
{
    Progress_Bar p_bar(100, ui->statusBar);
    clearSearchResult();

    QString search_text = ui->search_text->text();
    search_text.replace(QChar(32), QChar(95));

    Cda_Search search(search_text.toStdString(), &p_bar, 1);

    int items = search.result.size();

    if(items) {
        clearSearchResult();
        if(addPageResult(search_text, &p_bar)) {
            //
        }
    }else {
        playButtonDisable();
        addItemResult(new Item(0, "Not found", "", ""));
        infoMsg("Search result", QString("Not found result in cda.pl\nTry again using other words"));
        p_bar.finish();
        return;
    }
}

void MainWindow::addItemResult(Item *item)
{
    int row = ui->search_result->rowCount();
    QString i_no = QString::number(row+1);
    QString i_id = QString::fromStdString(item->getId());
    QString i_title = QString::fromStdString(item->getTitle());
    QString i_url;

    // If \no\ is null add empty
    if(i_id == "Info")
        i_no.clear();

    if(!item->getNo() && i_title == "(more)") {
        i_no.clear();
        i_url = QString::fromStdString(item->getUrl());
    }else
        i_url = QString::fromStdString(settings->cda_address)+QString::fromStdString(item->getUrl());

    ui->search_result->setRowCount(row+1);

    ui->search_result->setItem(row, 0, new QTableWidgetItem(i_no));
    ui->search_result->setItem(row, 1, new QTableWidgetItem(i_id));
    ui->search_result->setItem(row, 2, new QTableWidgetItem(i_title));
    ui->search_result->setItem(row, 3, new QTableWidgetItem(i_url));
}

// Function add search items to search result box and return true
// Return true if result is availible
bool MainWindow::addPageResult(QString search_text, Progress_Bar *p_bar, int page)
{
    Cda_Search search(search_text.toStdString(), p_bar, page);
    vector<Item*> *res = &search.result;
    int items = res->size();

    if(items) {
        int add_after = ui->search_result->rowCount();
        p_bar->resize(items);
        addResult(&search.result, p_bar, add_after);
    }else {
        playButtonDisable();
        p_bar->finish();
        return false;
    }

    // When is 24 items found (all results from one page in cda.pl)
    // Add as 25 item \more button\ to load more results
    if(items == 24) {
        addItemResult(new Item(0, "", "(more)", search_text.toStdString()));
    }

    return (items > 0);
}

//void MainWindow::addResult(Cda_Search *search, Progress_Bar *p_bar, int items, int at)
void MainWindow::addResult(vector<Item*> *results, Progress_Bar *p_bar, int at)
{
    int items = results->size();
    int all_rows = items+at;

    for(int i=at , res = 0; all_rows > i; i++ , res++) {
        addItemResult(results->at(res));
        p_bar->upgrade(1);
    }
    p_bar->finish();
}

void MainWindow::removeItemResult(int row)
{
    ui->search_result->removeRow(row);
}

void MainWindow::errorMsg(QString title, QString text)
{
    QMessageBox::critical(this, title, text, QMessageBox::Ok);
}

void MainWindow::infoMsg(QString title, QString text)
{
    QMessageBox::information(this, title, text, QMessageBox::Ok);
}

void MainWindow::on_actionEnterKey_triggered()
{
    if(ui->search_result->hasFocus()) {
        on_play_button_clicked();
    }

    if(ui->search_text->hasFocus()) {
        if(ui->search_button->isEnabled())
            on_search_button_clicked();
    }
}
