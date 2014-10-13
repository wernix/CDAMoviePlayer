#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T19:45:05
#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CDAMoviePlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdamain.cpp \
    infodialog.cpp \
    settingsdialog.cpp \
    settings.cpp \
    cdasearch.cpp \
    progressbar.cpp

HEADERS  += mainwindow.h \
    cdamain.h \
    infodialog.h \
    settingsdialog.h \
    settings.h \
    cdasearch.h \
    progressbar.h

FORMS    += mainwindow.ui \
    infodialog.ui \
    settingsdialog.ui

LIBS    += -lboost_regex -L/usr/local/lib -lcurl

RESOURCES += \
    resource.qrc
