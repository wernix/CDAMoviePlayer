#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    ui->app_name->setText(QApplication::applicationName()+" "+QApplication::applicationVersion());
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_ok_button_clicked()
{
    QDialog::close();
}
