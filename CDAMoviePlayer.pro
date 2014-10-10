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
    settings.cpp

HEADERS  += mainwindow.h \
    cdamain.h \
    infodialog.h \
    settingsdialog.h \
    settings.h

FORMS    += mainwindow.ui \
    infodialog.ui \
    settingsdialog.ui

LIBS    += -lboost_thread -lboost_regex -lboost_program_options -L/usr/local/lib -lcurl
#
