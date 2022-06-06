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
    Src/about/about.cpp \
        main.cpp \
    Src/connexion/connexionbdd.cpp \
    Src/pleaseWait/pleasewait.cpp \
    Src/editor/watcheditor.cpp \
    Src/gestionClient/ajouterClient/ajouterclient.cpp \
    Src/gestionClient/supprimerClient/supprimerclient.cpp \
    Src/gestionClient/modifierClient/modifierclient.cpp \
    Src/gestionTech/ajouterTech/ajoutertechnicien.cpp \
    Src/gestionTech/supprimerTech/supprimertech.cpp \
    Src/gestionTech/modifierMdpTech/modifiermdptech.cpp \
    Src/gestionMontre/wifi/modifierwifimontre.cpp \
    Src/gestionMontre/ntp/modifierntpmontre.cpp \
    Src/gestionMontre/mqtt/modifiermqttmontre.cpp \
    Src/gestionMontre/idClient/modifierclientidmontre.cpp

HEADERS += \
    Src/about/about.h \
         Src/connexion/connexionbdd.h \
    Src/pleaseWait/pleasewait.h \
    Src/editor/watcheditor.h \
    Src/gestionClient/ajouterClient/ajouterclient.h \
    Src/gestionClient/supprimerClient/supprimerclient.h \
    Src/gestionClient/modifierClient/modifierclient.h \
    Src/gestionTech/ajouterTech/ajoutertechnicien.h \
    Src/gestionTech/supprimerTech/supprimertech.h \
    Src/gestionTech/modifierMdpTech/modifiermdptech.h \
    Src/gestionMontre/wifi/modifierwifimontre.h \
    Src/gestionMontre/ntp/modifierntpmontre.h \
    Src/gestionMontre/mqtt/modifiermqttmontre.h \
    Src/gestionMontre/idClient/modifierclientidmontre.h

FORMS += \
    Src/about/about.ui \
        Src/connexion/connexionbdd.ui \
    Src/pleaseWait/pleasewait.ui \
    Src/editor/watcheditor.ui \
    Src/gestionClient/ajouterClient/ajouterclient.ui \
    Src/gestionClient/supprimerClient/supprimerclient.ui \
    Src/gestionClient/modifierClient/modifierclient.ui \
    Src/gestionTech/ajouterTech/ajoutertechnicien.ui \
    Src/gestionTech/supprimerTech/supprimertech.ui \
    Src/gestionTech/modifierMdpTech/modifiermdptech.ui \
    Src/gestionMontre/wifi/modifierwifimontre.ui \
    Src/gestionMontre/ntp/modifierntpmontre.ui \
    Src/gestionMontre/mqtt/modifiermqttmontre.ui \
    Src/gestionMontre/idClient/modifierclientidmontre.ui

QT += sql
QT += core
QT += serialport

RESOURCES += \
    Src/ressource.qrc \

DISTFILES += \

SUBDIRS += \
    connectbdd.pro

