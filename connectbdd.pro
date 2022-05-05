#-------------------------------------------------
#
# Project created by QtCreator 2022-04-06T15:20:54
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = connectbdd
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    about.cpp \
        main.cpp \
        connexionbdd.cpp \
    pleasewait.cpp \
    watcheditor.cpp \
    ajouterclient.cpp \
    supprimerclient.cpp \
    modifierclient.cpp \
    ajoutertechnicien.cpp \
    supprimertech.cpp \
    modifiermdptech.cpp \
    modifierwifimontre.cpp \
    modifierntpmontre.cpp

HEADERS += \
    about.h \
        connexionbdd.h \
    pleasewait.h \
    watcheditor.h \
    ajouterclient.h \
    supprimerclient.h \
    modifierclient.h \
    ajoutertechnicien.h \
    supprimertech.h \
    modifiermdptech.h \
    modifierwifimontre.h \
    modifierntpmontre.h

FORMS += \
    about.ui \
        connexionbdd.ui \
    pleasewait.ui \
    watcheditor.ui \
    ajouterclient.ui \
    supprimerclient.ui \
    modifierclient.ui \
    ajoutertechnicien.ui \
    supprimertech.ui \
    modifiermdptech.ui \
    modifierwifimontre.ui \
    modifierntpmontre.ui

QT += sql
QT += core
QT += serialport

RESOURCES +=

DISTFILES += \
    deco.png \

