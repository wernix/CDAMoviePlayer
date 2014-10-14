#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("CDA Movie Player");
    QApplication::setApplicationVersion("0.1 beta");

    MainWindow w;
    w.show();

    return a.exec();
}
