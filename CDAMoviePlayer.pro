QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/CDAMoviePlayer

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    cdamain.cpp \
    infodialog.cpp \
    settingsdialog.cpp \
    settings.cpp \
    cdasearch.cpp \
    progressbar.cpp \
    item.cpp \
    infodialog_license.cpp

HEADERS  += mainwindow.h \
    cdamain.h \
    infodialog.h \
    settingsdialog.h \
    settings.h \
    cdasearch.h \
    progressbar.h \
    item.h \
    infodialog_license.h

FORMS    += mainwindow.ui \
    infodialog.ui \
    settingsdialog.ui \
    infodialog_license.ui

RESOURCES += \
    resource.qrc

LIBS    += -lboost_regex -lcurl
