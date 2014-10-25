#include "infodialog_license.h"
#include "ui_infodialog_license.h"

InfoDialogLicense::InfoDialogLicense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialogLicense)
{
    ui->setupUi(this);
    loadLicense();
}

InfoDialogLicense::~InfoDialogLicense()
{
    delete ui;
}

void InfoDialogLicense::loadLicense()
{
    QFile file(":/txt/COPYING");

    if(file.open(QIODevice::ReadOnly)) {
        ui->license_content->setPlainText(file.readAll());
        file.close();
    }
}

void InfoDialogLicense::on_ok_button_clicked()
{
    this->close();
}
